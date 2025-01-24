// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/Tests/EnvQueryTest_Distance.h"
#include "EnvQueryTest_DistanceToLeader.generated.h"

/**
 * 
 */
UCLASS()
class DIRECTOR_SYSTEM_API UEnvQueryTest_DistanceToLeader : public UEnvQueryTest_Distance
{
	GENERATED_BODY()

	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
	virtual FText GetDescriptionTitle() const override;
	virtual FText GetDescriptionDetails() const override;
};
