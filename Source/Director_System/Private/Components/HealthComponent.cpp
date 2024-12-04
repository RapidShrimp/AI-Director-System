// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HealthComponent.h"

#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	CurrentHealth = MaxHealth;
}
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnTakeAnyDamage.AddUniqueDynamic(this,&UHealthComponent::HandleDamage);
}

void UHealthComponent::SetHealthMax()
{

	CurrentHealth = MaxHealth;
	FString Name = "Unknown";
	if(GetOwner() != nullptr)
	{
		Name = GetOwner()->GetName();
	}
	UGameplayStatics::ApplyDamage(GetOwner(),-MaxHealth,nullptr,nullptr,UDamageType::StaticClass());
	UE_LOG(LogTemp,Display,TEXT("Console Set Max health Actor %s"),*Name)
}

void UHealthComponent::KillActor()
{
	if(GetOwner() != nullptr)
	{
		UE_LOG(LogTemp,Display,TEXT("Console Killed Actor %s"),*GetOwner()->GetName())
		UGameplayStatics::ApplyDamage(GetOwner(),MaxHealth,nullptr,nullptr,UDamageType::StaticClass());
	}
}

void UHealthComponent::SetImmunities(TArray<TSubclassOf<UDamageType>> DamageTypes)
{
	Immunities = DamageTypes;
}


void UHealthComponent::HandleDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	if(!bCanTakeDamage)
	{
		UE_LOG(LogTemp,Warning,TEXT("Cannot Damage %s - Can Take Damage is off"),*GetOwner()->GetName())
		return;
	}

	
	/*if(Immunities.Contains(DamageType->GetClass()))
	{
		//Create Some immunity class to return a damage value differently, for now ignore it :) - AS
		return;
	}*/

	UE_LOG(LogTemp,Warning,TEXT("Damage %s %f"),*GetOwner()->GetName(),Damage)
	
	const float change = FMath::Max(FMath::Min(CurrentHealth, Damage), CurrentHealth-MaxHealth);
	CurrentHealth -= change;
	OnHealthChanged.Broadcast(DamageCauser,CurrentHealth, MaxHealth, change);

	if(CurrentHealth == 0.f) { OnDead.Broadcast(InstigatedBy); }
}
