// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Particles/ParticleEmitter.h"
#include "WeaponType.generated.h"

class AWeaponBase;
/**
 * 
 */

UENUM()
enum EWeaponType : uint8
{
	Primary,
	Secondary,
	Melee
};


UCLASS(BlueprintType)
class DIRECTOR_SYSTEM_API UWeaponType : public UDataAsset
{
	GENERATED_BODY()

public:

	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<USkeletalMesh> WeaponMesh;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<AWeaponBase> WeaponClass;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector MuzzleLocation;

	//Weapon Stats
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float FiringTime = 0.10f;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float ReloadTime = 2.5f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float BulletSpread = 0.5f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int MaxAmmo = 150;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int MagSize = 30;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Damage = 25;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UParticleEmitter> MuzzleParticleSystem;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<FVector> RailLocations;

};
