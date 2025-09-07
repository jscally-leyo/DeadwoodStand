// © 2025 Leyodemus. Development Build. All rights reserved


#include "RifleProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

ARifleProjectile::ARifleProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	
	// Collision
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.f);
	CollisionComp->SetCollisionProfileName("BlockAll");
	CollisionComp->OnComponentHit.AddDynamic(this, &ARifleProjectile::OnHit);
	RootComponent = CollisionComp;

	// Movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 8000.f;
	ProjectileMovement->MaxSpeed = 8000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.f; // No gravity
	
	InitialLifeSpan = LifeSeconds;
}

void ARifleProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void ARifleProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this && OtherComp)
	{
		// Apply damage
		UGameplayStatics::ApplyPointDamage(
			OtherActor,
			Damage,
			GetVelocity().GetSafeNormal(),
			Hit,
			GetInstigatorController(),
			this,
			nullptr
		);
		
		// Impact FX
		if (ImpactEffect)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), 
		   ImpactEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
		}
	
		if (ImpactSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, 
		   ImpactSound, Hit.ImpactPoint);
		}
	}
	Destroy();
}
