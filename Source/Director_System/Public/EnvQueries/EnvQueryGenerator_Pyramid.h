// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EQS_Enums.h"
#include "DataProviders/AIDataProvider.h"
#include "EnvironmentQuery/Generators/EnvQueryGenerator_ProjectedPoints.h"
#include "EnvQueryGenerator_Pyramid.generated.h"

/**
 * 
 */

UCLASS(meta = (DisplayName = "Points: Pyramid"))

class DIRECTOR_SYSTEM_API UEnvQueryGenerator_Pyramid : public UEnvQueryGenerator_ProjectedPoints
{
	GENERATED_BODY()

public:
	UEnvQueryGenerator_Pyramid(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	void BindDataToDataProviders(FEnvQueryInstance& QueryInstance) const;

	virtual void GenerateItems(FEnvQueryInstance& QueryInstance) const override;

	/** Returns the title of the generator on the corresponding node in the EQS Editor window */
	virtual FText GetDescriptionTitle() const override;
	/** Returns the details of the generator on the corresponding node in the EQS Editor window */
	virtual FText GetDescriptionDetails() const override;

protected:
	/** The actor (or actors) that will generate a cone in their facing direction */
	UPROPERTY(EditAnywhere, Category = Generator)
	TSubclassOf<UEnvQueryContext> CenterActor;

	/** Whether to include CenterActors' locations when generating items. */
	UPROPERTY(EditAnywhere, Category = Generator)
	uint8 bIncludeContextLocation : 1;


	/** Generation distance */
	UPROPERTY(EditDefaultsOnly, Category = Generator)
	FAIDataProviderFloatValue Range;
	
	/** Distance between Rows */
	UPROPERTY(EditDefaultsOnly, Category= Generator)
	FAIDataProviderFloatValue RowDistance;

	/** Row Start Width*/
	UPROPERTY(EditDefaultsOnly, Category= Generator)
	FAIDataProviderFloatValue RowLength;
	
	/** Width added per Row*/
	UPROPERTY(EditDefaultsOnly, Category= Generator)
	FAIDataProviderFloatValue RowLengthIncrease;

	/** Distance between points on a given row*/
	UPROPERTY(EditDefaultsOnly, Category= Generator)
	FAIDataProviderFloatValue PointsDistance;
	
	/** Direction of Pyramid Generation*/
	UPROPERTY(EditDefaultsOnly, Category= Generator)
	E_ConeDirection Direction;

	
};
