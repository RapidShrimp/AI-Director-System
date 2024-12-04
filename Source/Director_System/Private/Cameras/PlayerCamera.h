// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "PlayerCamera.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, ClassGroup=Camera, meta=(BlueprintSpawnableComponent))
class DIRECTOR_SYSTEM_API UPlayerCamera : public UCameraComponent
{
	GENERATED_BODY()

protected:
	float WalkFOV;
	float SprintFOV;

public:
	UFUNCTION(BlueprintCallable)
	void SetSprintFOV(bool Sprinting);
	UFUNCTION(BlueprintCallable)
	void ShakeCamera(float ShakeAmount);
};
