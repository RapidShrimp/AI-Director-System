// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatTrackerManager.generated.h"

class UCharacterStatsTracker;
class ACharacterBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DIRECTOR_SYSTEM_API UStatTrackerManager : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UStatTrackerManager();


	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TArray<TObjectPtr<UCharacterStatsTracker>> _CharacterStatTrackers;

	
private:

	UFUNCTION()
	void Handle_HealthChange(AActor* DamageCauser, ACharacterBase* DamagedCharacter, float CurrentHealth, float MaxHealth, float Change);
	UFUNCTION()
	void Handle_Death(AController* InstigatorController, ACharacterBase* Character);
};
