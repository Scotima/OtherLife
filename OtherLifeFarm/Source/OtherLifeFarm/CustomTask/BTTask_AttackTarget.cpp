#include "CustomTask/BTTask_AttackTarget.h"
#include "BTTask_AttackTarget.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"


UBTTask_AttackTarget::UBTTask_AttackTarget()
{
	NodeName = TEXT("Attack Target");
}

EBTNodeResult::Type UBTTask_AttackTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (!AIPawn)
	{
		return EBTNodeResult::Failed;
	}

	AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("TargetActor")));

	if (!Target)
	{
		return EBTNodeResult::Failed;

	}

	UE_LOG(LogTemp, Warning, TEXT("try attack: %s"), *Target->GetName());

	return EBTNodeResult::Succeeded;
}
