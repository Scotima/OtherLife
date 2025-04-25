
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CGhostRice.generated.h"

class UStaticMeshComponent;
class ACRice;

class ACRake;
class ACCharacter;


UCLASS()
class OTHERLIFEFARM_API ACGhostRice : public AActor
{
	GENERATED_BODY()
	
public:	
	ACGhostRice();

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

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


	void Cancel();
	
public:
	UFUNCTION(BlueprintCallable, Category = "Rice") //블루프린트에서 호출
	void RealSpawnRice();


	bool isActive;
private:
	UPROPERTY()
	APlayerController* PlayerController;


private:
	ACCharacter* character;

	

	


};
