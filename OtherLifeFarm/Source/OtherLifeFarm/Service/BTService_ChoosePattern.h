#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_ChoosePattern.generated.h"

UCLASS()
class OTHERLIFEFARM_API UBTService_ChoosePattern : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:

	UBTService_ChoosePattern();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;


};
