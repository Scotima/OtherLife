#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CBossController.generated.h"

struct FAIStimulus;

UCLASS()
class OTHERLIFEFARM_API ACBossController : public AAIController
{
	GENERATED_BODY()
	


public:
	
	ACBossController();
	

protected:

	virtual void BeginPlay() override;
	
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UAIPerceptionComponent* AIPerception;

	UPROPERTY()
	class UAISenseConfig_Sight* SightConfig;



protected:
	//비헤이비어 트리 자산
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* MyBehaviorTree;

	//블랙보드 자산 (BT와 연동)
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBlackboardData* BlackboardAsset;

private:
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBlackboardComponent* BlackboardComp;
};
