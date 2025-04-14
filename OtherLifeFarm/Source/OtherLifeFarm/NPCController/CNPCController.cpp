#include "NPCController/CNPCController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

ACNPCController::ACNPCController()
{
}

void ACNPCController::BeginPlay()
{
	Super::BeginPlay();

	if (UseBlackboard(BlackboardAsset, BlackboardComp))
	{
		APawn* MyPawn = GetPawn();

		if (MyPawn)
		{
			BlackboardComp->SetValueAsVector("HomeLocation", MyPawn->GetActorLocation());
		}
	}

	RunBehaviorTree(MyBehaviorTree);
}
