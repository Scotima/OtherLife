#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_DetectPlayer.generated.h"

UCLASS()
class OTHERLIFEFARM_API UBTService_DetectPlayer : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_DetectPlayer();


protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
