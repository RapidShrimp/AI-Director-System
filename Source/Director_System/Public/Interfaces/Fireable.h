// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Types/WeaponType.h"
#include "UObject/Interface.h"
#include "Fireable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UFireable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DIRECTOR_SYSTEM_API IFireable
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent)
	void InitWeapon(UWeaponType* Weapon);
	UFUNCTION(BlueprintNativeEvent)
	void StartFiring();
	UFUNCTION(BlueprintNativeEvent)
	void StopFiring();
	UFUNCTION(BlueprintNativeEvent)
	void Reload();
	UFUNCTION(BlueprintNativeEvent)
	void CancelReload();
};
