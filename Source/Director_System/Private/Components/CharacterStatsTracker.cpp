// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CharacterStatsTracker.h"

#include "Characters/CharacterBase.h"

UCharacterStatsTracker::UCharacterStatsTracker()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UCharacterStatsTracker::BeginPlay()
{
	Super::BeginPlay();
	
	const AController* OwningController = Cast<AController>(GetOwner());
	if(OwningController == nullptr)
	{
		UE_LOG(LogTemp,Error,TEXT("Component Not attatched to controller"));
		return;
	}

	TrackedCharacter = Cast<ACharacterBase>(OwningController->GetPawn());
	if(TrackedCharacter)
	{
		TrackedCharacter->OnHealthChange.AddUniqueDynamic(this,&UCharacterStatsTracker::Handle_HealthChange);
		TrackedCharacter->OnDeath.AddUniqueDynamic(this,&UCharacterStatsTracker::Handle_Death);
		UE_LOG(LogTemp,Display,TEXT("Successfully Bound All Stat Track Events %s"),*GetOwner()->GetName());
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Controlled Pawn not of Type 'ACharacterBase'"));
	}
}

void UCharacterStatsTracker::Handle_Death(AController* InstigatorController, ACharacterBase* DamagedCharacter)
{
	OnDeath.Broadcast(InstigatorController,DamagedCharacter);
}

void UCharacterStatsTracker::Handle_HealthChange(AActor* DamageCauser, ACharacterBase* DamagedCharacter,
                                                 float CurrentHealth, float MaxHealth, float Change)
{
	OnHealthChanged.Broadcast(DamageCauser,DamagedCharacter,CurrentHealth,MaxHealth,Change);
}
