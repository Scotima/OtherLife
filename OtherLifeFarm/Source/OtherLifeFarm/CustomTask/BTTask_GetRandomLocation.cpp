#include "CustomTask/BTTask_GetRandomLocation.h"
#include "BTTask_GetRandomLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"

UBTTask_GetRandomLocation::UBTTask_GetRandomLocation()
{
	NodeName = TEXT("Get Random Location Near Home"); // 비헤이비어 트리에서 노드 이름으로 보여지는 텍스트

	TargetLocationKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_GetRandomLocation, TargetLocationKey)); // 블랙보트 키에서 백터 타입만 허용하도록 설정
	HomeLocationKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_GetRandomLocation, HomeLocationKey)); // 이 위치를 기준으로 주변을 탐색하게 할 키

}

EBTNodeResult::Type UBTTask_GetRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld()); // 네이게이션 시스템 가져오기.

	if (!NavSys)
		return EBTNodeResult::Failed;

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent(); // 블랙보드 컴포넌트 가져오기
	if (!BlackboardComp)
		return EBTNodeResult::Failed;

	const FVector Origin = BlackboardComp->GetValueAsVector(HomeLocationKey.SelectedKeyName);
	FNavLocation RandomLocation;

	if (NavSys->GetRandomReachablePointInRadius(Origin, SearchRadius, RandomLocation))
	{
		BlackboardComp->SetValueAsVector(TargetLocationKey.SelectedKeyName, RandomLocation.Location);
		return EBTNodeResult::Succeeded;
	}



	return EBTNodeResult::Failed;
}
