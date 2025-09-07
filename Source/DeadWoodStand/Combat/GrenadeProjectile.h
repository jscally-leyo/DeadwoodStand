// © 2025 Leyodemus. Development Build. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GrenadeProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystem;
class USoundBase;

UCLASS()
class DEADWOODSTAND_API AGrenadeProjectile : public AActor
{
	GENERATED_BODY()

public:    
	AGrenadeProjectile();
	
protected:
	virtual void BeginPlay() override;
	
	/** Called when hitting something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	/** Called when grenade explodes */
	void Explode();

protected:
	/** Collision component */
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* CollisionComp;
	
	/** Movement component */
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UProjectileMovementComponent* ProjectileMovement;

	/** Explosion delay */
	UPROPERTY(EditDefaultsOnly, Category = "Grenade")
	float ExplosionDelay = 5.0f;

	/** Explosion radius */
	UPROPERTY(EditDefaultsOnly, Category = "Grenade")
	float ExplosionRadius = 300.f;

	/** Explosion damage */
	UPROPERTY(EditDefaultsOnly, Category = "Grenade")
	float ExplosionDamage = 60.f;

	/** FX */
	UPROPERTY(EditDefaultsOnly, Category = "Grenade|Effects")
	UParticleSystem* ExplosionEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Grenade|Effects")
	USoundBase* BounceSound;
	
	UPROPERTY(EditDefaultsOnly, Category = "Grenade|Effects")
	USoundBase* ExplosionSound;
	
	FTimerHandle ExplosionTimerHandle;
	
};