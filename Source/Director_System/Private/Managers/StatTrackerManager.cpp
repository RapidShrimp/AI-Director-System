// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/StatTrackerManager.h"
#include "Characters/CharacterBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CharacterStatsTracker.h"

// Sets default values for this component's properties
UStatTrackerManager::UStatTrackerManager()
{
	PrimaryComponentTick.bCanEverTick = false;


}

void UStatTrackerManager::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundControllers;
	UGameplayStatics::GetAllActorsOfClass(this,AController::StaticClass(),FoundControllers);

	for (AActor* FoundController : FoundControllers)
	{
		UCharacterStatsTracker* TempStats =  Cast<UCharacterStatsTracker>(FoundController->GetComponentByClass(UCharacterStatsTracker::StaticClass()));
		if(TempStats != nullptr)
		{
			TempStats->OnHealthChanged.AddUniqueDynamic(this,&UStatTrackerManager::Handle_HealthChange);
			TempStats->OnDeath.AddUniqueDynamic(this,&UStatTrackerManager::Handle_Death);
			_CharacterStatTrackers.AddUnique(TempStats);
		}
	}
}





void UStatTrackerManager::Handle_HealthChange(AActor* DamageCauser, ACharacterBase* DamagedCharacter,
	float CurrentHealth, float MaxHealth, float Change)
{
	FString DamageCauserName = *(DamageCauser != nullptr ? DamageCauser->GetName() : "Unknown");
	FString DamagedActorName = *(DamagedCharacter != nullptr ? DamagedCharacter->GetName() : "Unknown");

	UE_LOG(LogTemp,Display,TEXT("%s Damaged %s for %f, New Health: %f"),*DamageCauserName,*DamagedActorName,Change,CurrentHealth)
}

void UStatTrackerManager::Handle_Death(AController* InstigatorController, ACharacterBase* Character)
{
	FString DamageCauserName =  "Unknown";
	if(InstigatorController != nullptr)
	{
		if(InstigatorController->GetPawn() != nullptr)
		{
			DamageCauserName = InstigatorController->GetPawn()->GetName();
		}
	}
	FString DamagedActorName = Character != nullptr ? Character->GetName() : "Unknown";

	UE_LOG(LogTemp,Display,TEXT("%s Killed %s"),*DamageCauserName,*DamagedActorName)
}
