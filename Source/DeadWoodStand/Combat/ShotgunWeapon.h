// © 2025 Leyodemus. Development Build. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "HitScanWeapon.h"
#include "ShotgunWeapon.generated.h"

UCLASS()
class DEADWOODSTAND_API AShotgunWeapon : public AHitScanWeapon
{
	GENERATED_BODY()
	
public:
	AShotgunWeapon();
	
	virtual void Fire() override;
	
protected:
	/** Shotgun specific settings */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon|Shotgun")
	int32 NumPellets = 8;
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon|Shotgun")
	float PelletSpreadAngle = 5.f; // In degrees
};
