// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIControllerBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAICWeaponFiredSignature, AWeaponBase*, Weapon, ACharacterBase*, OwnedCharacter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAICDeathSignature, AAIController*, DeadController, AController*, InstigatorController, ACharacterBase*, DamagedCharacter);

class UCharacterType;
class ACharacterBase;
class AWeaponBase;

UENUM()
enum class EBP_TeamAttitude
{
	Friendly
};

UCLASS()
class DIRECTOR_SYSTEM_API AAIControllerBase : public AAIController
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintAssignable)
	FAICWeaponFiredSignature OnAICWeaponFired;

	UPROPERTY(BlueprintAssignable)
	FAICDeathSignature OnAIDead;

	UFUNCTION(BlueprintCallable)
	int BP_GetTeamAttitudeTowards(const AActor* Other);
protected:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBehaviorTree> BehaviourTree;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	uint8 DefaultTeamID = 255; //No Team ID Default
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<ACharacterBase> _ControlledPawn;

	/**0-Friendly 1-Neutral 2-Hostile*/
	ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool HasDirector = false;
	
public:
	UFUNCTION(BlueprintCallable)
	void SpawnAI(UCharacterType* InCharacter, UBehaviorTree* Behaviour, uint8 AssignTeamID, FTransform InTransform);
	UFUNCTION(BlueprintCallable)
	void StartGame();
	UFUNCTION(BlueprintCallable)
	void SetFireTarget(AActor* Target);
	UFUNCTION(BlueprintCallable)
	void SetDirected(TArray<AActor*> Teammates);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	TArray<AActor*> GetPercievedActors();
protected:
	UFUNCTION()
	void Handle_WeaponFired(AWeaponBase* Weapon, ACharacterBase* InCharacter);
	UFUNCTION(BlueprintImplementableEvent)
	void BPHandle_WeaponFired(AWeaponBase* Weapon, ACharacterBase* InCharacter);
	
	UFUNCTION()
	void Handle_AIDeath(AController* Controller, ACharacterBase* CharacterBase);
	UFUNCTION(BlueprintImplementableEvent)
	void BPHandle_AIDeath(AController* Controller, ACharacterBase* CharacterBase);

};
