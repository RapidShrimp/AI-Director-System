// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataProviders/AIDataProvider.h"
#include "EQS_Enums.h"
#include "EnvironmentQuery/Generators/EnvQueryGenerator_ProjectedPoints.h"
#include "EnvQueryGenerator_ConeDirectional.generated.h"

/**
 * 
 */




UCLASS(meta = (DisplayName = "Points: Cone(Directional)"))
class DIRECTOR_SYSTEM_API UEnvQueryGenerator_ConeDirectional : public UEnvQueryGenerator_ProjectedPoints
{
	GENERATED_BODY()
public:
	UEnvQueryGenerator_ConeDirectional(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/** Binds data to data providers 
	 *  @param QueryInstance - the instance of the query
	 */
	void BindDataToDataProviders(FEnvQueryInstance& QueryInstance) const;
	
	virtual void GenerateItems(FEnvQueryInstance& QueryInstance) const override;

	/** Returns the title of the generator on the corresponding node in the EQS Editor window */
	virtual FText GetDescriptionTitle() const override;

	/** Returns the details of the generator on the corresponding node in the EQS Editor window */
	virtual FText GetDescriptionDetails() const override;

protected:
	/** Distance between each point of the same angle */
	UPROPERTY(EditDefaultsOnly, Category = Generator)
	FAIDataProviderFloatValue AlignedPointsDistance;

	/** Maximum degrees of the generated cone */
	UPROPERTY(EditDefaultsOnly, Category = Generator)
	FAIDataProviderFloatValue ConeDegrees;

	/** The Direction that the cone will face*/
	UPROPERTY(EditDefaultsOnly, Category = Generator)
	E_ConeDirection ConeDirection;
	
	/** The step of the angle increase. Angle step must be >=1
	 *  Smaller values generate less items
	 */
	UPROPERTY(EditDefaultsOnly, Category = Generator)
	FAIDataProviderFloatValue AngleStep;

	/** Generation distance */
	UPROPERTY(EditDefaultsOnly, Category = Generator)
	FAIDataProviderFloatValue Range;

	/** The actor (or actors) that will generate a cone in their facing direction */
	UPROPERTY(EditAnywhere, Category = Generator)
	TSubclassOf<UEnvQueryContext> CenterActor;

	/** Whether to include CenterActors' locations when generating items. 
	 *	Note that this option skips the MinAngledPointsDistance parameter. */
	UPROPERTY(EditAnywhere, Category = Generator)
	uint8 bIncludeContextLocation : 1;

};
