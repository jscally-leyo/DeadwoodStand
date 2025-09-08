// © 2025 Leyodemus. Development Build. All rights reserved

#include "BaseHUD.h"
#include "DSCrosshairWidget.h"
#include "Blueprint/UserWidget.h"

void ABaseHUD::SetCrosshairWidgetClass(TSubclassOf<UDSCrosshairWidget> NewWidgetClass)
{
	if (CurrentCrosshair)
	{
		CurrentCrosshair->RemoveFromParent();
		CurrentCrosshair = nullptr;
	}
	if (NewWidgetClass)
	{
		CurrentCrosshair = CreateWidget<UDSCrosshairWidget>(GetWorld(), NewWidgetClass);
		if (CurrentCrosshair)
		{
			CurrentCrosshair->AddToViewport();
			CurrentCrosshairClass = NewWidgetClass;
		}
	}
}

void ABaseHUD::SetCrosshairSpread(float SpreadValue)
{
	if (CurrentCrosshair)
	{
		CurrentCrosshair->Spread = SpreadValue;
	}
}

void ABaseHUD::SetCrosshairColor(FLinearColor NewColor)
{
	if (CurrentCrosshair)
	{
		CurrentCrosshair->UpdateColor(NewColor);
	}
}