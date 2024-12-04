// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GM_DirectorTest.generated.h"

/**
 * 
 */
UCLASS()
class DIRECTOR_SYSTEM_API AGM_DirectorTest : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	
private:
	void Handle_HealthChanged();
	void Handle_Death();
	void Handle_WeaponFired();
};
