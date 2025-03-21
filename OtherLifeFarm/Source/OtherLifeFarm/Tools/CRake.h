// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CRake.generated.h"

class UStaticMeshComponent;
class UAnimMontage;
class ACharacter;
class ACCharacter;
class ACRice;


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

	void TurnToMouse();

public:
	UFUNCTION(BlueprintCallable, Category = "Rake")
	void AttachToOwner(); // 블루프린트에서 호출 가능

	UFUNCTION(BlueprintCallable, Category = "Rake")
	void DetachFromOwner();

public:

	UPROPERTY(EditDefaultsOnly, Category = "Montages");
	UAnimMontage* RakeAssetMontage;


private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UStaticMeshComponent* RakeMesh;

	
	UPROPERTY(EditDefaultsOnly, Category = "Socket");
	FName HandSocket;

	UPROPERTY()
	APlayerController* PlayerController;


private:
	ACCharacter* OwnerCharacter;

	FVector OriginalLocation;
	FRotator OriginalRotation;

	ACCharacter* Character;
	ACRice* rice;

};
