// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponType.generated.h"

class AWeaponBase;
/**
 * 
 */
UCLASS()
class DIRECTOR_SYSTEM_API UWeaponType : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UStaticMesh> WeaponMesh;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<AWeaponBase> WeaponClass;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector MuzzleLocation;

	//Weapon Stats
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float FiringTime;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float ReloadTime;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float BulletSpread;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int MaxAmmo;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int MagSize;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Damage;
};
