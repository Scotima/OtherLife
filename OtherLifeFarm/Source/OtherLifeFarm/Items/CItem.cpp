#include "Items/CItem.h"
#include "Components/StaticMeshComponent.h"
#include "FarmCharacter/CCharacter.h"

ACItem::ACItem()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	RootComponent = ItemMesh;

	ItemMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ItemMesh->SetCollisionResponseToAllChannels(ECR_Overlap);
}

void ACItem::BeginPlay()
{
	Super::BeginPlay();
	
	ItemMesh->OnComponentBeginOverlap. AddDynamic(this, &ACItem::OnOverlapBegin);
}

void ACItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACCharacter* Player = Cast<ACCharacter>(OtherActor);
	if (Player)
	{
		Player->PickupItem(ItemData);
		Destroy();
	}

}

