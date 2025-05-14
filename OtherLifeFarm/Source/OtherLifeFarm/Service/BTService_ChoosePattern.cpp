#include "Service/BTService_ChoosePattern.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Math/UnrealMathUtility.h"

UBTService_ChoosePattern::UBTService_ChoosePattern()
{
	NodeName = TEXT("Choose Random Pattern");
	Interval = 1.0f;
	RandomDeviation = 0.5f;
}

void UBTService_ChoosePattern::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	int32 RandomPattern = FMath::RandRange(0, 3);
	OwnerComp.GetBlackboardComponent()->SetValueAsInt(GetSelectedBlackboardKey(), RandomPattern);
}
