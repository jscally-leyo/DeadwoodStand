// © 2025 Leyodemus. Development Build. All rights reserved

#include "DWSPlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "DeadWoodStand/Interactables/Interactable.h"
#include "Engine/World.h"

void ADWSPlayerController::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = true;
}

void ADWSPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ActorTrace();
}

void ADWSPlayerController::ActorTrace()
{
	// Save last actor
	LastActor = ThisActor;
	ThisActor = nullptr;
	// Trace from camera forward
	FVector Start = PlayerCameraManager->GetCameraLocation();
	FVector End = Start + PlayerCameraManager->GetActorForwardVector() * TraceDistance;
	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetPawn());
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params);
	if (bHit && HitResult.GetActor() && HitResult.GetActor()->Implements<UInteractable>())
	{
		ThisActor = TScriptInterface<IInteractable>
		(HitResult.GetActor());
	}
	if (LastActor.GetObject() != ThisActor.GetObject())
	{
		if (LastActor)
		{
			// ✔ Calls OnUnfocus() in BP or C++ cleanly
			IInteractable::Execute_OnUnfocus(LastActor.GetObject());
		}
		if (ThisActor)
		{
			IInteractable::Execute_OnFocus(ThisActor.GetObject());
		}
	}
}

void ADWSPlayerController::Interact()
{
	if (ThisActor)
	{
		IInteractable::Execute_Interact(ThisActor.GetObject(), GetPawn());
	}
}