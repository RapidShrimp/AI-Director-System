// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIControllerBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAICWeaponFiredSignature, AWeaponBase*, Weapon, ACharacterBase*, OwnedCharacter);

class UCharacterType;
class ACharacterBase;
class AWeaponBase;

UCLASS()
class DIRECTOR_SYSTEM_API AAIControllerBase : public AAIController
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FAICWeaponFiredSignature OnAICWeaponFired;
	
protected:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBehaviorTree> BehaviourTree;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	uint8 DefaultTeamID = 255; //No Team ID Default
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<ACharacterBase> _ControlledPawn;
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
	void SetDirected();

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
