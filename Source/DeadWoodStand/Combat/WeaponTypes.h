#pragma once

#include "WeaponTypes.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
   EWT_NoWeapon  UMETA(DisplayName = "NoWeapon"),
   EWT_Pistol    UMETA(DisplayName = "Pistol"),
   EWT_Rifle     UMETA(DisplayName = "Rifle"),
   EWT_Shotgun   UMETA(DisplayName = "Shotgun"),
   EWT_Grenade   UMETA(DisplayName = "Grenade Launcher"),
   EWT_Melee     UMETA(DisplayName = "Melee"),
   EWT_MAX       UMETA(Hidden)
};





