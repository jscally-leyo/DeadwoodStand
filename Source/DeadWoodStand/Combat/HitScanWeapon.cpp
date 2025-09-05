// © 2025 Leyodemus. Development Build. All rights reserved

#include "HitScanWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraShakeBase.h"
#include "DeadWoodStand/Character/PlayerCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundBase.h"

AHitScanWeapon::AHitScanWeapon()
{
	WeaponType = EWeaponType::EWT_Pistol;
}

void AHitScanWeapon::Fire()
{
	if (!OwnerCharacter || CurrentAmmo <= 0)
		return;
	
	CurrentAmmo--;
	
	// Line trace
	FHitResult HitResult;
	PerformLineTrace(HitResult);
	
	// Impact
	HandleImpact(HitResult);
	
	// Muzzle effect
	if (MuzzleFlash)
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlash"));
	}

	// Sound
	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}
	
	// Camera shake
	if (APlayerController* PC = Cast<APlayerController>(OwnerCharacter->GetController()))
	{
		PC->ClientStartCameraShake(CameraShake);
	}
}

void AHitScanWeapon::PerformLineTrace(FHitResult& HitOut)
{
	FVector EyeLocation;
	FRotator EyeRotation;
	OwnerCharacter->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	FVector End = EyeLocation + (EyeRotation.Vector() * FireRange);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(OwnerCharacter);
	Params.bReturnPhysicalMaterial = true;
	GetWorld()->LineTraceSingleByChannel(HitOut, EyeLocation, End, ECC_Visibility, Params);
}

void AHitScanWeapon::HandleImpact(const FHitResult& Hit)
{
	if (Hit.bBlockingHit)
	{
		// Deal damage
		UGameplayStatics::ApplyPointDamage(
			Hit.GetActor(),
			Damage,
			Hit.TraceStart - Hit.TraceEnd,
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
}
