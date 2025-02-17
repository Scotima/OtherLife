// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/FItemStruct.h"
#include "GameFramework/Actor.h"
#include "CItem.generated.h"



class UStaticMeshComponent;

UCLASS()
class OTHERLIFEFARM_API ACItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable)
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);


public:
	UPROPERTY(EditAnyWhere, Category = "Item")
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditAnyWhere,BlueprintReadWrite, Category = "Item")
	FItemStruct ItemData;
	

};
