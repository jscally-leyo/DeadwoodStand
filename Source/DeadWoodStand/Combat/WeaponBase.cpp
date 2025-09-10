// © 2025 Leyodemus. Development Build. All rights reserved

#include "WeaponBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "DeadWoodStand/Character/PlayerCharacter.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponType = EWeaponType::EWT_Pistol;
	MaxAmmoInClip = 30;
	TotalAmmo = 50;
	CurrentAmmo = 0;
	
	AttachSocketName = TEXT("Weapon_hand_r_Socket");
	bIsEquipped = false;
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MaxAmmoInClip;
	if (OwnerCharacter)
	{
		PC = Cast<APlayerController>(OwnerCharacter->GetController());
	}
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
	OwnerCharacter->SetCurrentWeapon(this);
	
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

bool AWeaponBase::CanReload() const
{
	return CurrentAmmo < MaxAmmoInClip;
}

void AWeaponBase::Reload()
{
	if (bIsReloading || CurrentAmmo == MaxAmmoInClip || TotalAmmo <= 0)	return;
	
	bIsReloading = true;
	StopFire();
	UE_LOG(LogTemp, Log, TEXT("Reloading..."));

	// Play animation
	float AnimDuration = ReloadTime;
	if (ReloadMontage && OwnerCharacter)
	{
		UAnimInstance* AnimInstance = OwnerCharacter->GetMesh()->GetAnimInstance();
		if (AnimInstance)
		{
			AnimDuration = AnimInstance->Montage_Play(ReloadMontage);
		}
	}
	
	ReloadTime = AnimDuration;
	
	GetWorldTimerManager().SetTimer(ReloadTimerHandle, this, &AWeaponBase::FinishReload, ReloadTime, false);
}

void AWeaponBase::FinishReload()
{
	int32 AmmoNeeded = MaxAmmoInClip - CurrentAmmo;
	int32 AmmoToReload = FMath::Min(AmmoNeeded, TotalAmmo);
	
	CurrentAmmo += AmmoToReload;
	TotalAmmo -= AmmoToReload;
	bIsReloading = false;
	UE_LOG(LogTemp, Log, TEXT("Reloaded. CurrentAmmo: %d, TotalAmmo: %d"), CurrentAmmo, TotalAmmo);
}

void AWeaponBase::Fire()
{
	if (bIsReloading || CurrentAmmo <= 0) return;

	// Play fire animation
	if (FireMontage && OwnerCharacter)
	{
		UAnimInstance* AnimInstance = OwnerCharacter->GetMesh()->GetAnimInstance();
		if (AnimInstance)
		{
			AnimInstance->Montage_Play(FireMontage);
		}
	}
	
	// Child classes (hitscan or projectile) will add more specific functionality here
}

void AWeaponBase::StartFire()
{
	if (bIsAutomatic)
	{
		// Start repeating fire
		Fire(); // Immediate first shot
		GetWorldTimerManager().SetTimer(AutoFireHandle, this, &AWeaponBase::Fire, FireRate, true);
	}
	else
	{
		Fire(); // Single shot
	}
}

void AWeaponBase::StopFire()
{
	if (bIsAutomatic)
	{
		GetWorldTimerManager().ClearTimer(AutoFireHandle);
	}
}



