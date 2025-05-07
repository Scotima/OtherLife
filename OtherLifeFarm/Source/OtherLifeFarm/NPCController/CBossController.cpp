#include "NPCController/CBossController.h"
#include "CBossController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISense_Sight.h"

ACBossController::ACBossController()
{
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	SetPerceptionComponent(*AIPerception);

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 1000.0f;
	SightConfig->LoseSightRadius = 1200.0f;
	SightConfig->PeripheralVisionAngleDegrees = 90.0f;
	SightConfig->SetMaxAge(5.0f);
}

void ACBossController::BeginPlay()
{

	if (UseBlackboard(BlackboardAsset, BlackboardComp))
	{
		RunBehaviorTree(MyBehaviorTree);

	}
}

void ACBossController::OnTargetDetected(AActor* Actor, FAIStimulus Stimulus)
{
}
