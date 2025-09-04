// © 2025 Leyodemus. Development Build. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "DeadWoodStand/Interactables/Pickups/Pickup.h"
#include "WeaponTypes.h"
#include "WeaponBase.generated.h"

class USkeletalMeshComponent;
class APlayerCharacter;

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
	
	/** Ammo */
	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
	int32 MaxAmmo;
	UPROPERTY(VisibleAnywhere, Category = "Ammo")
	int32 CurrentAmmo;
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName AttachSocketName;

	bool bIsEquipped;
};
