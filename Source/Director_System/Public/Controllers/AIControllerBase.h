// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIControllerBase.generated.h"

class UCharacterType;
class ACharacterBase;
UCLASS()
class DIRECTOR_SYSTEM_API AAIControllerBase : public AAIController
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBehaviorTree> BehaviourTree;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	uint8 DefaultTeamID = 255; //No Team ID Default
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<ACharacterBase> _ControlledPawn;
	ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
public:
	UFUNCTION(BlueprintCallable)
	void SpawnAI(UCharacterType* InCharacter, UBehaviorTree* Behaviour, uint8 AssignTeamID, FTransform InTransform);
	UFUNCTION(BlueprintCallable)
	void StartGame();
};
