// © 2025 Leyodemus. Development Build. All rights reserved

#include "WeaponBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "DeadWoodStand/Character/PlayerCharacter.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;
	MaxAmmo = 30;
	CurrentAmmo = MaxAmmo;
	AttachSocketName = TEXT("Weapon_hand_r_Socket");
	bIsEquipped = false;
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

void AWeaponBase::Interact_Implementation(AActor* Interactor)
{
	Super::Interact_Implementation(Interactor);

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Interactor);
	Equip(PlayerCharacter);
}

void AWeaponBase::Equip(APlayerCharacter* NewOwner)
{
	if (!NewOwner) return;
	
	OwnerCharacter = NewOwner;
	bIsEquipped = true;
	
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, AttachSocketName);
	SetActorEnableCollision(false);
}

void AWeaponBase::Unequip()
{    
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	bIsEquipped = false;
	OwnerCharacter = nullptr;
	SetActorEnableCollision(true);
}

void AWeaponBase::Reload()
{
	if (!CanReload()) return;
	
	CurrentAmmo = MaxAmmo;
	// Optionally: play reload animation here
}

bool AWeaponBase::CanReload() const
{
	return CurrentAmmo < MaxAmmo;
}

void AWeaponBase::Fire()
{
	// Base class leaves this empty
	// Child (hitscan or projectile) will override
}

