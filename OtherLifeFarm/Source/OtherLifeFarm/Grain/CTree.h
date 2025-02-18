
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CTree.generated.h"

class UStaticMeshComponent;

UCLASS()
class OTHERLIFEFARM_API ACTree : public AActor
{
	GENERATED_BODY()
	
public:	
	ACTree();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	UStaticMeshComponent* MeshComp;

};
