// © 2025 Leyodemus. Development Build. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "DeadWoodStand/Interactables/Pickups/Pickup.h"
#include "WeaponTypes.h"
#include "WeaponBase.generated.h"

class USkeletalMeshComponent;
class APlayerCharacter;
class UParticleSystem;
class USoundBase;
class UCameraShakeBase;

UCLASS()
class DEADWOODSTAND_API AWeaponBase : public APickup
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeaponBase();
	
	virtual void BeginPlay() override;
	virtual void Interact_Implementation(AActor* Interactor) override;
	
	/** Equip & attach to hand */
	virtual void Equip(APlayerCharacter* NewOwner);
	virtual void Unequip();
	
	/** Ammo and reload logic */
	virtual void Reload();
	bool CanReload() const;
	
	/** Virtual Shoot (child will override) */
	virtual void Fire();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	EWeaponType WeaponType;

protected:
	/** Owner */
	UPROPERTY()
	TObjectPtr<APlayerCharacter> OwnerCharacter;

	/** Effects */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon|Effects")
	TObjectPtr<UParticleSystem> MuzzleFlash;
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon|Effects")
	TObjectPtr<USoundBase> FireSound;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon|Effects")
	TSubclassOf<UCameraShakeBase> CameraShake;

	/** Stats */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float Damage = 25.f;
	
	/** Ammo */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon|Ammo")
	int32 MaxAmmoInClip;

	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon|Ammo")
	int32 CurrentAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Ammo")
	int32 TotalAmmo;

	/** Reloading */
	UPROPERTY(BlueprintReadOnly, Category = "Weapon|Reload")
	bool bIsReloading = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Reload")
	float ReloadTime = 1.5f;

	FTimerHandle ReloadTimerHandle;
	
	void FinishReload();

	/** Equiping */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName AttachSocketName;

	bool bIsEquipped;

public:
	/** Getters */
	FORCEINLINE int32 GetCurrentAmmo() const { return CurrentAmmo; }
	FORCEINLINE int32 GetTotalAmmo() const { return TotalAmmo; }
		
};
