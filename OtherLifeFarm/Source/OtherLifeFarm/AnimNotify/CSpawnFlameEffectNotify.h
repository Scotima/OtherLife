
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CSpawnFlameEffectNotify.generated.h"


UCLASS()
class OTHERLIFEFARM_API UCSpawnFlameEffectNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animmation) override;
	
};
