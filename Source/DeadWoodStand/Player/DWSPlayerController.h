// © 2025 Leyodemus. Development Build. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DeadWoodStand/Interactables/Interactable.h"
#include "DWSPlayerController.generated.h"

UCLASS()
class DEADWOODSTAND_API ADWSPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	/** Called from player character to interact with focused actor */
	UFUNCTION(BlueprintCallable)
	void Interact();
	
protected:
	// Actor trace function
	void ActorTrace();
	
	// Cached interactable actors
	TScriptInterface<IInteractable> LastActor;
	TScriptInterface<IInteractable> ThisActor;
	
	// Interaction settings
	UPROPERTY(EditAnywhere, Category = "Interaction")
	float TraceDistance = 500.f;
};
