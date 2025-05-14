
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_JumpSmash.generated.h"

class ACBoss;

UCLASS()
class OTHERLIFEFARM_API UBTTask_JumpSmash : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_JumpSmash();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	bool bMontagePlayed = false;
	FName MontageSection;
	ACBoss* CachedBoss;

};
