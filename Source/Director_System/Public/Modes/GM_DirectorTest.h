// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GM_DirectorTest.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameStartSignature);
/**
 * 
 */
UCLASS()
class DIRECTOR_SYSTEM_API AGM_DirectorTest : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintAssignable)
	FOnGameStartSignature OnGameStart;
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float StartDelay = 0.5f;
private:
	void OnStartTimerComplete();
	FTimerHandle StartDelayTimer;
	void Handle_HealthChanged();
	void Handle_Death();
	void Handle_WeaponFired();
};
