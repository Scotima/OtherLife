#include "NPCController/CBossController.h"
#include "CBossController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISense_Sight.h"
#include "NavigationSystem.h"              
#include "NavigationPath.h" 
#include "Navigation/PathFollowingComponent.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


ACBossController::ACBossController()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	SetPerceptionComponent(*AIPerception);

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 1000.0f;
	SightConfig->LoseSightRadius = 1200.0f;
	SightConfig->PeripheralVisionAngleDegrees = 90.0f;
	SightConfig->SetMaxAge(5.0f);

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	AIPerception->ConfigureSense(*SightConfig); // 시야 감지 구성.
	AIPerception->SetDominantSense(SightConfig->GetSenseImplementation());

	AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &ACBossController::OnTargetDetected);

	CurrentTarget = nullptr;


}

void ACBossController::BeginPlay()
{

	if (UseBlackboard(BlackboardAsset, BlackboardComp))
	{
		RunBehaviorTree(MyBehaviorTree);

	}
}

void ACBossController::OnTargetDetected(AActor* Actor, FAIStimulus Stimulus)
{




	if (Stimulus.WasSuccessfullySensed())
	{
		if (APawn* ControlledPawn = GetPawn())
		{
			
			
			auto* MoveComp = Cast<ACharacter>(GetPawn())->GetCharacterMovement();
			if (MoveComp)
			{
				EMovementMode Mode = MoveComp->MovementMode;
				UE_LOG(LogTemp, Warning, TEXT("MovementMode: %d"), (int32)Mode);
			}
			


			FVector TargetLocation = Actor->GetActorLocation();
			FVector OriginalLocation = ControlledPawn->GetActorLocation();
			UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
			FNavLocation ProjectedLocation;

			if (NavSys->GetRandomReachablePointInRadius(TargetLocation, 1, ProjectedLocation))
			{

				if (CurrentTarget != Actor)
				{
					GetBlackboardComponent()->SetValueAsObject(FName("TargetActor"), Actor);
					CurrentTarget = Actor;
					UE_LOG(LogTemp, Warning, TEXT("Boss Dected you! : %s"), *Actor->GetName());


					AActor* Target = Cast<AActor>(Blackboard->GetValueAsObject("TargetActor"));

					if (Target)
					{
						EPathFollowingRequestResult::Type MoveResult = MoveToActor(Target);
						FAIMoveRequest MoveRequest;
						MoveRequest.SetGoalActor(Target);
						MoveRequest.SetAcceptanceRadius(200); // ← 여유 있게
						MoveRequest.SetUsePathfinding(true);

						FNavPathSharedPtr OutPath;
						MoveTo(MoveRequest, &OutPath);

						if (OutPath.IsValid() && OutPath->IsValid())
						{
							UE_LOG(LogTemp, Warning, TEXT("✅ 경로 생성됨! 경유 지점 수: %d"), OutPath->GetPathPoints().Num());
						}
						else
						{
							UE_LOG(LogTemp, Warning, TEXT("❌ 경로 없음: AI가 이동할 수 없습니다."));
						}

						UE_LOG(LogTemp, Warning, TEXT("MoveToActor 실행 결과: %d"), (int32)MoveResult);
					}

					else
					{
						UE_LOG(LogTemp, Warning, TEXT("TargetActor is null or invalid"));
					}


				}
			} 
		}


	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Boss lose insight: %s"), *Actor->GetName());
		GetBlackboardComponent()->ClearValue(FName("TargetActor"));
		CurrentTarget = nullptr;
	}
}
