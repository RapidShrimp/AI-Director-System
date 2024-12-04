// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "Components/ActorComponent.h"
#include "CharacterStatsTracker.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FCharacterStatsHealthChangedSignature,AActor*,DamageCauser,ACharacterBase*,DamagedCharacter, float,CurrentHealth,float,MaxHealth,float,Change);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCharacterStatsDeathSignature, AController*, InstigatorController, ACharacterBase*, Character);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCharacterStatsWeaponUseSignature, AController*,Controller,float,AmmoDispatchValue);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DIRECTOR_SYSTEM_API UCharacterStatsTracker : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCharacterStatsTracker();

	UPROPERTY(BlueprintAssignable)
	FCharacterStatsHealthChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable)
	FCharacterStatsDeathSignature OnDeath;
	UPROPERTY(BlueprintAssignable)
	FCharacterStatsWeaponUseSignature OnWeaponUsed;
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<ACharacterBase> TrackedCharacter;

private:
	UFUNCTION()
	void Handle_Death(AController* InstigatorController, ACharacterBase* DamagedCharacter);
	UFUNCTION()
	void Handle_HealthChange(AActor* DamageCauser, ACharacterBase* DamagedCharacter, float CurrentHealth, float MaxHealth, float Change);
};
