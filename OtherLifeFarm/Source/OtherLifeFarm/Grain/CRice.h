// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CRice.generated.h"

UCLASS()
class OTHERLIFEFARM_API ACRice : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACRice();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	UFUNCTION()
	void GrowRice();

public:
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Rice")
	UStaticMeshComponent* RiceMesh;

	UPROPERTY()
	TArray<UStaticMesh*> RiceMeshs;

private:
	int32 CurrentMeshIndex;
	FTimerHandle ChangeMeshTimerHandle;

};
