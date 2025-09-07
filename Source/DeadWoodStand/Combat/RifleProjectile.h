// © 2025 Leyodemus. Development Build. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RifleProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class UParticleSystem;
class USoundBase;

UCLASS()
class DEADWOODSTAND_API ARifleProjectile : public AActor
{
	GENERATED_BODY()

public:
	ARifleProjectile();
	
protected:
	virtual void BeginPlay() override;
	
	/** Handle hit */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
protected:
	/** Collision */
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* CollisionComp;
	
	/** Projectile movement */
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UProjectileMovementComponent* ProjectileMovement;
	
	/** FX */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon|Effects")
	UParticleSystem* ImpactEffect;
	UPROPERTY(EditDefaultsOnly, Category = "Weapon|Effects")
	USoundBase* ImpactSound;
	
	/** Damage */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon|Combat")
	float Damage = 45.0f;
	
	/** Life span */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon|Combat")
	float LifeSeconds = 3.0f;
};