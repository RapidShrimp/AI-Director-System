// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/StatTrackerManager.h"

#include "Characters/CharacterBase.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UStatTrackerManager::UStatTrackerManager()
{
	PrimaryComponentTick.bCanEverTick = false;


}

void UStatTrackerManager::BeginPlay()
{
	Super::BeginPlay();

	const AController* OwningController = Cast<AController>(GetOwner());
	if(OwningController == nullptr)
	{
		UE_LOG(LogTemp,Error,TEXT("Component Not attatched to controller"));
		return;
	}

	TrackedCharacter= Cast<ACharacterBase>(OwningController->GetPawn());
	if(TrackedCharacter)
	{
		TrackedCharacter->OnReportHealthChange.AddUniqueDynamic(this,&UStatTrackerManager::Handle_HealthChangeReport);
		TrackedCharacter->OnReportDeath.AddUniqueDynamic(this,&UStatTrackerManager::Handle_DeathReport);
		UE_LOG(LogTemp,Display,TEXT("Successfully Bound All Stat Track Events"));
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("Controlled Pawn not of Type 'ACharacterBase'"));
	}
}


void UStatTrackerManager::Handle_HealthChangeReport(AActor* DamageCauser, ACharacterBase* DamagedCharacter,
	float CurrentHealth, float MaxHealth, float Change)
{
	
}

void UStatTrackerManager::Handle_DeathReport(AController* InstigatorController)
{

}
