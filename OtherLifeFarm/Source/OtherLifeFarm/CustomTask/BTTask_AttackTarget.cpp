#include "CustomTask/BTTask_AttackTarget.h"
#include "BTTask_AttackTarget.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"
#include "Animation/AnimInstance.h"
#include "FarmCharacter/CBoss.h"


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

	ACBoss* boss = Cast<ACBoss>(AIPawn);
	if (!boss || !boss->AttackMontage)
	{
		return EBTNodeResult::Failed;
	}

	UAnimInstance* AnimInst = boss->GetMesh()->GetAnimInstance();
	if (AnimInst)
	{
		AnimInst->Montage_Play(boss->AttackMontage);
		UE_LOG(LogTemp, Warning, TEXT("🔥 공격 애니메이션 재생 중: %s"), *Target->GetName());
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Succeeded;
}
