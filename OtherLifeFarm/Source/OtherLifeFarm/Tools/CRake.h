// Fill out your copyright notice in the Description page of Project Settings.

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
	// Sets default values for this actor's properties
	ACRake();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void Plowing();
	void SweepSingleByChannel();

public:
	UFUNCTION(BlueprintCallable, Category = "Rake")
	void AttachToOwner(); // 블루프린트에서 호출 가능

	UFUNCTION(BlueprintCallable, Category = "Rake")
	void DetachFromOwner();

public:

	bool bPlayerAnimation;

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UStaticMeshComponent* RakeMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montages");
	UAnimMontage* RakeAssetMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Socket");
	FName HandSocket;



private:
	ACharacter* OwnerCharacter;

	FVector OriginalLocation;
	FRotator OriginalRotation;


};
