// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerBase.generated.h"

class ACharacterBase;

/**
 * 
 */
UCLASS()
class DIRECTOR_SYSTEM_API APlayerControllerBase : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	uint8 DefaultTeamID = 255; //No Team ID Default

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<ACharacterBase> _ControlledPawn;
public:
	virtual void BeginPlay() override;

protected:
	virtual void OnPossess(APawn* InPawn) override;
	
};
