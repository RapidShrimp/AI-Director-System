// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "Components/HealthComponent.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

class UCharacterType;
class UWeaponType;
class AWeaponBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FCharacterHealthChangeSignature,AActor*,DamageCauser,ACharacterBase*,DamagedCharacter, float,CurrentHealth,float,MaxHealth,float,Change);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCharacterDeathSignature, AController*, InstigatorController, ACharacterBase*, DamagedCharacter);

UCLASS()
class DIRECTOR_SYSTEM_API ACharacterBase : public ACharacter ,public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:

	ACharacterBase();

	//Delegates
	
	FCharacterDeathSignature OnDeath;
	FCharacterHealthChangeSignature OnHealthChange;
	
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UHealthComponent> _Health;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly);
	TObjectPtr<AWeaponBase> SelectedWeapon;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly);
	TObjectPtr<AWeaponBase> PrimaryWeapon;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly);
	TObjectPtr<AWeaponBase> SecondaryWeapon;

	
#pragma  region TeamInterface

protected:
	FGenericTeamId _TeamID;
public:
	void SetGenericTeamId(const FGenericTeamId& TeamID) override;
	FGenericTeamId GetGenericTeamId() const override;
#pragma endregion
	
protected:	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bArmed;
	
	virtual void BeginPlay() override;
	
public:

	UFUNCTION(BlueprintCallable)
	void BP_Init(UCharacterType* InCharacter);
	void Init(UCharacterType* InCharacter);

	UFUNCTION(BlueprintCallable) //TODO - Out of Scope
	void PickupWeapon(UWeaponType* Weapon, bool IsPrimary);

	UFUNCTION(BlueprintCallable)
	void StartFire();
	UFUNCTION(BlueprintCallable)
	void StopFire();
	UFUNCTION(BlueprintCallable)
	void Reload();
	UFUNCTION(BlueprintCallable)
	void SwapWeapon();

	UFUNCTION(BlueprintCallable)
	AWeaponBase* GetCurrentWeapon();
	UFUNCTION(BlueprintCallable)
	void StartCrouch();
	UFUNCTION(BlueprintCallable)
	void StopCrouch();
	
	
private:
	UFUNCTION()
	void Handle_Death(AController* InstigatorController);
	UFUNCTION()
	void Handle_HealthChange(AActor* DamageCauser, float CurrentHealth, float MaxHealth, float Change);
};
