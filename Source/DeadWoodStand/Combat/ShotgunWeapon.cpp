// © 2025 Leyodemus. Development Build. All rights reserved

#include "ShotgunWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "DeadWoodStand/Character/PlayerCharacter.h"

AShotgunWeapon::AShotgunWeapon()
{
	NumPellets = 8;
	PelletSpreadAngle = 5.f;
	Damage = 10.f; // Per pellet
	FireRange = 1200.f;
}

void AShotgunWeapon::Fire()
{
	if (bIsReloading || CurrentAmmo <= 0 || !OwnerCharacter) return;
	
	--CurrentAmmo;
	
	FVector EyeLocation;
	FRotator EyeRotation;
	OwnerCharacter->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	
	for (int32 i = 0; i < NumPellets; ++i)
	{
		// Spread
		FRotator SpreadRot = EyeRotation;
		SpreadRot.Yaw += FMath::RandRange(-PelletSpreadAngle, PelletSpreadAngle);
		SpreadRot.Pitch += FMath::RandRange(PelletSpreadAngle, PelletSpreadAngle);
		
		FVector ShotDirection = SpreadRot.Vector();
		FVector TraceEnd = EyeLocation + (ShotDirection * FireRange);
		
		FHitResult Hit;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		Params.AddIgnoredActor(OwnerCharacter);
		
		if (GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, ECC_Visibility, Params))
		{
			// Deal damage
			UGameplayStatics::ApplyPointDamage(
				Hit.GetActor(),
				Damage,
				ShotDirection,
				Hit,
				OwnerCharacter->GetInstigatorController(),
				this,
				nullptr
			);
			
			// Spawn impact effect
			if (ImpactEffect)
			{
                
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), 
				ImpactEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
			}
		}
		// Debug line
		//DrawDebugLine(GetWorld(), EyeLocation, TraceEnd, FColor::Red, false, 1.f, 0, 1.f);
	}
	
	// Fire effects (one time)
	if (MuzzleFlash)
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlash"));
	}
	
	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}
	
	if (APlayerController* PC = Cast<APlayerController>(OwnerCharacter->GetController()))
	{
		PC->ClientStartCameraShake(CameraShake);
	}
	
	// Auto-reload if empty
	if (CurrentAmmo <= 0)
	{
		Reload();
	}
}