
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CGhostRice.generated.h"

class UStaticMeshComponent;
class ACRice;


UCLASS()
class OTHERLIFEFARM_API ACGhostRice : public AActor
{
	GENERATED_BODY()
	
public:	
	ACGhostRice();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, Category = "Rice")
	TSubclassOf<ACRice> RiceClass;

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	UStaticMeshComponent* GhostRice;


public:
	void SetGhostLocation();
	void RealSpawnRice();

private:
	UPROPERTY()
	APlayerController* PlayerController;


};
