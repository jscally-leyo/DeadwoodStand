// © 2025 Leyodemus. Development Build. All rights reserved

#include "Pickup.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

APickup::APickup()
 {
 	PrimaryActorTick.bCanEverTick = false;
 	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
 	RootComponent = Collision;
 	Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
 	Collision->SetSphereRadius(40.f);
 	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
 	Mesh->SetupAttachment(RootComponent);
 }

void APickup::BeginPlay()
{
	Super::BeginPlay();
}

void APickup::Interact_Implementation(AActor* Interactor)
{
}

void APickup::OnFocus_Implementation()
{
	if (Mesh)
	{
		Mesh->SetRenderCustomDepth(true);
		Mesh->SetCustomDepthStencilValue(1);
		// Optional: Use specific stencil for highlight
	}
}

void APickup::OnUnfocus_Implementation()
{
	if (Mesh)
	{
		Mesh->SetRenderCustomDepth(false);
	}
}

bool APickup::CanInteract_Implementation() const
{
	return bCanInteract;
}