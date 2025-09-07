// © 2025 Leyodemus. Development Build. All rights reserved

#include "GrenadeProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

AGrenadeProjectile::AGrenadeProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	
	// Collision
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(12.f);
	CollisionComp->SetCollisionProfileName("BlockAll");
	CollisionComp->SetNotifyRigidBodyCollision(true);
	CollisionComp->OnComponentHit.AddDynamic(this, &AGrenadeProjectile::OnHit);
	RootComponent = CollisionComp;

	// Movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 1500.f;
	ProjectileMovement->MaxSpeed = 1500.f;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = 0.5f;
	ProjectileMovement->Friction = 0.2f;
	ProjectileMovement->ProjectileGravityScale = 1.0f;
	
	InitialLifeSpan = ExplosionDelay + 1.0f; // Safety cleanup
}

void AGrenadeProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	// Schedule explosion
	GetWorldTimerManager().SetTimer(ExplosionTimerHandle, this, &AGrenadeProjectile::Explode, ExplosionDelay);
}

void AGrenadeProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (BounceSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, BounceSound, GetActorLocation());
	}
}

void AGrenadeProjectile::Explode()
{
	if (ExplosionEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());
	}
	if (ExplosionSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation());
	}

	UGameplayStatics::ApplyRadialDamage(this,	ExplosionDamage,GetActorLocation(),ExplosionRadius,
		nullptr,TArray<AActor*>(),this,GetInstigatorController(),	true);
	
	Destroy();
}