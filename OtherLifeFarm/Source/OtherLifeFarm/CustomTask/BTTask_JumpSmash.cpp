#include "CustomTask/BTTask_JumpSmash.h"
#include "AIController.h"
#include "FarmCharacter/CBoss.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"


UBTTask_JumpSmash::UBTTask_JumpSmash()
{
    NodeName = TEXT("Jump Smash Attack");
    bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_JumpSmash::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    CachedBoss = Cast<ACBoss>(OwnerComp.GetAIOwner()->GetPawn());
    if (!CachedBoss || !CachedBoss->JumpSmashMontage)
    {
        return EBTNodeResult::Failed;
    }

    UAnimInstance* AnimInst = CachedBoss->GetMesh()->GetAnimInstance();

    if (AnimInst)
    {

        CachedBoss->GetController()->StopMovement();
        CachedBoss->GetCharacterMovement()->DisableMovement();

        AnimInst->Montage_Play(CachedBoss->JumpSmashMontage);
        UE_LOG(LogTemp, Warning, TEXT("🧨 점프 찍기 애니메이션 재생 시작"));
        bMontagePlayed = true;

        return EBTNodeResult::InProgress;
    }

    return EBTNodeResult::Failed;
}

void UBTTask_JumpSmash::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

    if (!CachedBoss)
    {
        return;
    }

    UAnimInstance* AnimInst = CachedBoss->GetMesh()->GetAnimInstance();
    if(bMontagePlayed && AnimInst && !AnimInst->Montage_IsPlaying(CachedBoss->JumpSmashMontage))
    {
        UE_LOG(LogTemp, Warning, TEXT("✅ 점프 찍기 애니메이션 종료"));
        CachedBoss->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
}
