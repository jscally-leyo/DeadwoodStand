// © 2025 Leyodemus. Development Build. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DSCrosshairWidget.generated.h"

UCLASS()
class DEADWOODSTAND_API UDSCrosshairWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Spread value to adjust crosshair layout */
	UPROPERTY(BlueprintReadWrite, Category = "Crosshair")
	float Spread;
	
	/** Override in Blueprint to update color dynamically */
	UFUNCTION(BlueprintImplementableEvent, Category = "Crosshair")	
	void UpdateColor(FLinearColor NewColor);
};
