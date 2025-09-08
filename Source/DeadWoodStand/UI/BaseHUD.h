// © 2025 Leyodemus. Development Build. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BaseHUD.generated.h"

class UDSCrosshairWidget;

UCLASS()
class DEADWOODSTAND_API ABaseHUD : public AHUD
{
	GENERATED_BODY()

public:
	void SetCrosshairWidgetClass(TSubclassOf<UDSCrosshairWidget> NewWidgetClass);
	void SetCrosshairSpread(float SpreadValue);
	void SetCrosshairColor(FLinearColor NewColor);
	
protected:
	UPROPERTY()
	TObjectPtr<UDSCrosshairWidget> CurrentCrosshair;
	
	UPROPERTY()
	TSubclassOf<UDSCrosshairWidget> CurrentCrosshairClass;
};
