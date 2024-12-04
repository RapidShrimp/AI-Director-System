// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatTrackerManager.generated.h"

class ACharacterBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FReportHealthSignature, float, Change, int, TeamID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FReportDeathSignature, int, TeamID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FReportWeaponUseSignature, AController*,Controller,float,AmmoDispatchValue);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DIRECTOR_SYSTEM_API UStatTrackerManager : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UStatTrackerManager();
	
	virtual void BeginPlay() override;
	
	FReportHealthSignature OnReportHealth;
	FReportDeathSignature OnReportDeath;
	FReportWeaponUseSignature OnReportWeaponUsed;

protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<ACharacterBase> TrackedCharacter;
private:
	UFUNCTION()
	void Handle_HealthChangeReport(AActor* DamageCauser, ACharacterBase* DamagedCharacter, float CurrentHealth, float MaxHealth, float Change);
	UFUNCTION()
	void Handle_DeathReport(AController* InstigatorController);
};
