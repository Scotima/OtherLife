#include "FarmCharacter/CNpcone.h"
#include "Blueprint/UserWidget.h"   
#include "Kismet/GameplayStatics.h" 
#include "Camera/CameraComponent.h"	
#include "Animation/AnimInstance.h"
#include"AnimInstance/CNpconeAnimInstance.h"

ACNpcone::ACNpcone()
{
	//PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Game/FarmGame/BPCharacter/CharacterAsset/Girl/Girl"));

	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}

	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(RootComponent);
}

UUserWidget* ACNpcone::ShowWidget_Implementation()
{
	if (WidgetClass)
	{
		return CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
	}
	return nullptr;
}

void ACNpcone::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACNpcone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACNpcone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACNpcone::SetTalking(bool bTalking)
{
	if (UCNpconeAnimInstance* AnimBP = Cast<UCNpconeAnimInstance>(GetMesh()->GetAnimInstance()))
	{
		AnimBP->SetTalking(bTalking);
	}
}



