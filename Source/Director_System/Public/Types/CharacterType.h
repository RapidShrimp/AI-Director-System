// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponType.h"
#include "Engine/DataAsset.h"
#include "CharacterType.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class DIRECTOR_SYSTEM_API UCharacterType : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UWeaponType> PrimaryWeapon;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UWeaponType> SecondaryWeapon;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MaxHealth = 100;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float WalkSpeed = 600;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float SprintSpeed = 800;
	
};
