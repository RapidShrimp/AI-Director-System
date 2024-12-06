// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "Components/HealthComponent.h"
#include "GameFramework/Character.h"
#include "Types/CharacterType.h"
#include "CharacterBase.generated.h"
class UWeaponType;
class AWeaponBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FCharacterHealthChangeSignature,AActor*,DamageCauser,ACharacterBase*,DamagedCharacter, float,CurrentHealth,float,MaxHealth,float,Change);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCharacterDeathSignature, AController*, InstigatorController, ACharacterBase*, DamagedCharacter);

UCLASS()
class DIRECTOR_SYSTEM_API ACharacterBase : public ACharacter , public IGenericTeamAgentInterface
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


	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UCharacterType> TestType;
	
	#pragma region TeamGenerics
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FGenericTeamId _TeamID;
	virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override;
public:
	virtual FGenericTeamId GetGenericTeamId() const override;
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	#pragma  endregion
	 
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bArmed;
	
	virtual void BeginPlay() override;
	
public:
	void Init(UCharacterType* Character);

	UFUNCTION(BlueprintCallable)
	void PickupWeapon(UWeaponType* Weapon, bool IsPrimary);

	UFUNCTION(BlueprintCallable)
	void StartFire();
	UFUNCTION(BlueprintCallable)
	void StopFire();
	UFUNCTION(BlueprintCallable)
	void Reload();
	UFUNCTION(BlueprintCallable)
	void SwapWeapon();

private:
	UFUNCTION()
	void Handle_Death(AController* InstigatorController);
	UFUNCTION()
	void Handle_HealthChange(AActor* DamageCauser, float CurrentHealth, float MaxHealth, float Change);
};
