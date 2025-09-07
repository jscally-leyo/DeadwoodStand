// © 2025 Leyodemus. Development Build. All rights reserved

#include "ProjectileWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DeadWoodStand/Character/PlayerCharacter.h"

 AProjectileWeapon::AProjectileWeapon()
 {
 	MuzzleSocketName = TEXT("MuzzleFlash");
 	MuzzleVelocity = 2000.f;
 }

void AProjectileWeapon::Fire()
 {
	 if (bIsReloading || CurrentAmmo <= 0 || !OwnerCharacter || 	!ProjectileClass)
	 	return;
 	
 	--CurrentAmmo;
 	
 	FVector EyeLocation;
 	FRotator EyeRotation; 	
 	OwnerCharacter->GetActorEyesViewPoint(EyeLocation,  EyeRotation);
 	
 	FVector MuzzleLocation = Mesh->GetSocketLocation(MuzzleSocketName);
 	FRotator MuzzleRotation = EyeRotation;
 	
 	FActorSpawnParameters SpawnParams;
 	SpawnParams.Instigator = OwnerCharacter;
 	SpawnParams.Owner = this;
 	
 	// Spawn projectile
 	AActor* Projectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
    
 	// Optional: Give it initial velocity
 	if (UProjectileMovementComponent* ProjMove = Projectile->FindComponentByClass<UProjectileMovementComponent>())
 	{
 		ProjMove->Velocity = MuzzleRotation.Vector() *  MuzzleVelocity;
 	}
 	
 	// Optional fire FX
 	if (FireSound)
 	{
 		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
 	}
 	
 	if (MuzzleFlash)
 	{
 		UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, MuzzleSocketName);
 	}
 
 	if (APlayerController* PC = Cast<APlayerController>(OwnerCharacter->GetController()))
 	{
 		PC->ClientStartCameraShake(CameraShake);
 	}
 	
 	if (CurrentAmmo <= 0)
 	{
 		Reload();
 	}
 }