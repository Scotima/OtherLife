#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_GetRandomLocation.generated.h"


UCLASS()
class OTHERLIFEFARM_API UBTTask_GetRandomLocation : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_GetRandomLocation();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
public:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector TargetLocationKey;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector HomeLocationKey;

	UPROPERTY(EditAnywhere, Category = "AI")
	float SearchRadius = 1000.0f;

};
