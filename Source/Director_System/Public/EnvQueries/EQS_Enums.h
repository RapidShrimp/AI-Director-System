// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EQS_Enums.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class E_ConeDirection : uint8
{
	forward = 0 UMETA(DisplayName="Forward"),
	right = 1 UMETA(DisplayName="Right"),
	left = 2 UMETA(DisplayName="Left"),
	back = 3 UMETA(DisplayName="Backwards")
};