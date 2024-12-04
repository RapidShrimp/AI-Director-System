// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeadSignature,AController*,Instigator);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthUpdatedSignature,AActor*,DamageCauser,float,CurrentHealth,float,MaxHealth,float,Change);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DIRECTOR_SYSTEM_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();

#pragma region Editor Call Functions
	UFUNCTION(CallInEditor)
	void SetHealthMax();
	UFUNCTION(CallInEditor)
	void KillActor();
#pragma endregion
	
	UFUNCTION(BlueprintCallable)
	void SetImmunities(TArray<TSubclassOf<UDamageType>> DamageTypes);

	UPROPERTY(BlueprintAssignable)
	FOnDeadSignature OnDead;
	
	UPROPERTY(BlueprintAssignable)
	FOnHealthUpdatedSignature OnHealthChanged;
protected:

	UFUNCTION()
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bCanTakeDamage = true;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MaxHealth = 100.0f;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	float CurrentHealth;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<TSubclassOf<UDamageType>> Immunities;
private:
	UFUNCTION()
	void HandleDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
};
