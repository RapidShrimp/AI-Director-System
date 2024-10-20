// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"
class UWeaponType;
class AWeaponBase;

UCLASS()
class DIRECTOR_SYSTEM_API ACharacterBase : public ACharacter , public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

#pragma region TeamGenerics
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FGenericTeamId _TeamID;
	virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override;
	virtual FGenericTeamId GetGenericTeamId() const override;
#pragma  endregion
	 
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bArmed;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly);
	TObjectPtr<AWeaponBase> SelectedWeapon;
	TObjectPtr<AWeaponBase> PrimaryWeapon;
	TObjectPtr<AWeaponBase> SecondaryWeapon;
	
public:

	void Init();
	//Weapons
	void PickupWeapon(UWeaponType* Weapon);
	void StartFire();
	void StopFire();
	void Reload();
	void SwapWeapon();
};
