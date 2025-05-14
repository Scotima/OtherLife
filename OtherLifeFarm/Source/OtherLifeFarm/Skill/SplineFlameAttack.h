
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SplineFlameAttack.generated.h"

class USplineComponent;
class UNiagaraSystem;

UCLASS()
class OTHERLIFEFARM_API ASplineFlameAttack : public AActor
{
	GENERATED_BODY()
	
public:	
	ASplineFlameAttack();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


protected:
	// 생성된 스플라인 경로
	UPROPERTY(VisibleAnywhere)
	USplineComponent* Spline;
	//사용할 나이아가라 이펙트
	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	UNiagaraSystem* FlameEffect;
	
	//생성할 점 개수
	UPROPERTY(VisibleAnywhere)
	int32 NumPoints = 10;
	//간격
	UPROPERTY(EditAnywhere, Category = "VFX")
	float Spacing = 100.0f;
	//데미지 처리용 채널
	UPROPERTY(EditAnywhere, Category = "VFX")
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditAnywhere)
	float Damage = 20.0f;

	UPROPERTY(VisibleDefaultsOnly,Category = "VFX")
	float FlameSpawnInterval = 0.7f;




protected:

	FTimerHandle FlameSpawnTimerHandle;
	int32 CurrentSpawnIndex = 0;





protected:
	UFUNCTION()
	void SpawnFlameAlongSpline();

	UFUNCTION()
	void SpawnNextFlame();



};
