// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatTrackerManager.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFinishGameSignature,bool, Victory);

class UCharacterStatsTracker;
class ACharacterBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DIRECTOR_SYSTEM_API UStatTrackerManager : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UStatTrackerManager();

	FFinishGameSignature OnFinishGame;

	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TArray<TObjectPtr<UCharacterStatsTracker>> _CharacterStatTrackers;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float PlayerDamageTaken;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float PlayerDamageDealt;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float AIDamageTaken;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float AIDamageDealt;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int AIDeaths = 0;
	
private:

	UFUNCTION()
	void Handle_HealthChange(AActor* DamageCauser, ACharacterBase* DamagedCharacter, float CurrentHealth, float MaxHealth, float Change);
	UFUNCTION()
	void Handle_Death(AController* InstigatorController, ACharacterBase* Character);
};
