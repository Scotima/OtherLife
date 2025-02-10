
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CRake.generated.h"

class UStaticMeshComponent;
class UAnimMontage;
class ACharacter;
UCLASS()
class OTHERLIFEFARM_API ACRake : public AActor
{
	GENERATED_BODY()
	
public:	
	ACRake();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable, Category = " Rake")
	void AttachToOwner();


private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UStaticMeshComponent* RakeMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* RakeMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = "Socket")
	FName RakeSocketName;



private:
	void Plowing();
	void SweepSingleByChannel();


private:
	ACharacter* OwnerCharacter;
	

};
