#include "Service/BTService_DetectPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"


UBTService_DetectPlayer::UBTService_DetectPlayer()
{
	NodeName = TEXT("Detect Player");

	//감지 주기 설정(0.5초마다 실행)
	Interval = 0.5;
	RandomDeviation = 0.1f;

}

void UBTService_DetectPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AIcon = OwnerComp.GetAIOwner();
	if (!AIcon)
	{
		return;
	}

	UAIPerceptionComponent* Perception = AIcon->FindComponentByClass<UAIPerceptionComponent>();
	if (!Perception)
	{
		return;
	}

	TArray<AActor*> SeenActors;
	Perception->GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), SeenActors);

	if (SeenActors.Num() > 0)
	{
		AActor* Detected = SeenActors[0];
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), Detected);
	}

	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}

}
