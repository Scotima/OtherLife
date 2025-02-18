#include "Grain/CTree.h"

ACTree::ACTree()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	ConstructorHelpers::FObjectFinder<UStaticMesh> TreeAsset(TEXT("/Game/Simple_forest/Meshes/Trees/SM_tree_01"));

	if (TreeAsset.Succeeded())
	{
		MeshComp->SetStaticMesh(TreeAsset.Object);
	}

}

void ACTree::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACTree::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

