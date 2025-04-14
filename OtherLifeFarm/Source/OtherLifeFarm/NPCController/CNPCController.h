
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CNPCController.generated.h"

class UBehaviorTreeComponent;

UCLASS()
class OTHERLIFEFARM_API ACNPCController : public AAIController
{
	GENERATED_BODY()

public:
	ACNPCController();
	
protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, Category = "AI")
	UBehaviorTree* MyBehaviorTree;

	UPROPERTY(EditAnywhere, Category = "AI")
	UBlackboardData* BlackboardAsset;

private:
	UPROPERTY()
	UBlackboardComponent* BlackboardComp;

	UPROPERTY()
	UBehaviorTreeComponent* BehaviorComp;

};
