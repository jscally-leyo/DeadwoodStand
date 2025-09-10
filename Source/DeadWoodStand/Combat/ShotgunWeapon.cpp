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
	if (!PC)
		PC = Cast<APlayerController>(OwnerCharacter->GetController());

	FString DebugString;

	if (!PC)
	{
		DebugString = FString::Printf(TEXT("PC not valid"));
	}
	
	if (bIsReloading)
	{
		DebugString = FString::Printf(TEXT("IsReloading"));
	}

	if (CurrentAmmo <= 0)
	{
		DebugString = FString::Printf(TEXT("CurrentAmmo <= 0"));
	}

	if (!OwnerCharacter)
	{
		DebugString = FString::Printf(TEXT("Owner character not valid"));
	}	
	
	if (!PC || bIsReloading || CurrentAmmo <= 0 || !OwnerCharacter)
	{
		GEngine->AddOnScreenDebugMessage(3, 5.f, FColor::Red, DebugString);
		return;
	}
	
	--CurrentAmmo;

	OwnerCharacter->StartShootingEffect();
	
	// Get viewpoint from camera
	FVector EyeLocation;
	FRotator EyeRotation;
	PC->GetPlayerViewPoint(EyeLocation, EyeRotation);
	FVector MuzzleLocation = Mesh->GetSocketLocation(MuzzleSocketName);
	
	for (int32 i = 0; i < NumPellets; ++i)
	{
		// Add random spread
		FRotator SpreadRot = EyeRotation;
		SpreadRot.Yaw += FMath::RandRange(-PelletSpreadAngle, PelletSpreadAngle);
		SpreadRot.Pitch += FMath::RandRange(-PelletSpreadAngle, PelletSpreadAngle);
		FVector ShotDirection = SpreadRot.Vector();
		
		// Trace from camera to target
		FVector TraceEnd = EyeLocation + (ShotDirection * FireRange);
		FHitResult Hit;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		Params.AddIgnoredActor(OwnerCharacter);
		Params.bReturnPhysicalMaterial = true;
		
		if (GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, ECC_Visibility, Params))
		{
			// Apply damage
			UGameplayStatics::ApplyPointDamage(Hit.GetActor(),Damage,ShotDirection,Hit,OwnerCharacter->GetInstigatorController(),this,nullptr);
			// Impact FX
			if (ImpactEffect)
			{
				UGameplayStatics::SpawnEmitterAtLocation(
				GetWorld(),ImpactEffect,Hit.ImpactPoint,Hit.ImpactNormal.Rotation());
			}
			// Optional: Draw debug line to hit point
			// DrawDebugLine(GetWorld(), MuzzleLocation, Hit.ImpactPoint, FColor::Red, false, 1.0f, 0, 1.0f);
		}
		else
		{
			// Optional: Draw debug line to miss
			// DrawDebugLine(GetWorld(), MuzzleLocation, TraceEnd, FColor::Blue, false, 1.0f, 0, 1.0f);
		}
	}
	
	// Fire FX (only once)
	if (MuzzleFlash)
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, MuzzleSocketName);
	}
	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}
	if (CameraShake && PC)
	{
		PC->ClientStartCameraShake(CameraShake);
	}
	
	// Auto-reload
	if (CurrentAmmo <= 0)
	{
		Reload();
	}
}