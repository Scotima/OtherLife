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
	SightConfig->SightRadius = 2000.0f;
	SightConfig->LoseSightRadius = 1200.0f;
	SightConfig->PeripheralVisionAngleDegrees = 360.0f;
	SightConfig->SetMaxAge(5.0f);

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	AIPerception->ConfigureSense(*SightConfig); // 시야 감지 구성.
	AIPerception->SetDominantSense(SightConfig->GetSenseImplementation());

	bStartAILogicOnPossess = true;
}

void ACBossController::BeginPlay()
{
	Super::BeginPlay();
}

void ACBossController::OnPossess(APawn* InPawn)
{

	Super::OnPossess(InPawn);
	UE_LOG(LogTemp, Error, TEXT("🔥🔥 Possess 완료: %s"), *GetNameSafe(InPawn));

	if (UseBlackboard(BlackboardAsset, BlackboardComp))
	{
		RunBehaviorTree(MyBehaviorTree);
	}
}

