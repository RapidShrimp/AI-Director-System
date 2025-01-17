// Fill out your copyright notice in the Description page of Project Settings.


#include "EnvQueries/EnvQueryGenerator_Pyramid.h"

#include "Chaos/ChaosPerfTest.h"
#include "EnvironmentQuery/Contexts/EnvQueryContext_Querier.h"
#include "GenericPlatform/GenericPlatformCrashContext.h"
#define LOCTEXT_NAMESPACE "EnvQueryGenerator"

UEnvQueryGenerator_Pyramid::UEnvQueryGenerator_Pyramid(const FObjectInitializer& ObjectInitializer)
:Super(ObjectInitializer)
{
	CenterActor = UEnvQueryContext_Querier::StaticClass();
	Range.DefaultValue = 1000;
	RowDistance.DefaultValue = 100.f;
	
	RowLength.DefaultValue = 100.f;
	RowLengthIncrease.DefaultValue = 100.f;
	PointsDistance.DefaultValue = 50.f;

	Direction = E_ConeDirection::forward;
	bIncludeContextLocation = false;
	
}

void UEnvQueryGenerator_Pyramid::BindDataToDataProviders(FEnvQueryInstance& QueryInstance) const
{
	UObject* BindOwner = QueryInstance.Owner.Get();
	Range.BindData(BindOwner,QueryInstance.QueryID);
	RowDistance.BindData(BindOwner,QueryInstance.QueryID);
	RowLength.BindData(BindOwner,QueryInstance.QueryID);
	RowLengthIncrease.BindData(BindOwner,QueryInstance.QueryID);
	PointsDistance.BindData(BindOwner,QueryInstance.QueryID);
	Range.BindData(BindOwner,QueryInstance.QueryID);
}

void UEnvQueryGenerator_Pyramid::GenerateItems(FEnvQueryInstance& QueryInstance) const
{
	TArray<AActor*> CenterActors;

	QueryInstance.PrepareContext(CenterActor,CenterActors);
	if(CenterActors.Num() <= 0)
	{
		return;
	}

	BindDataToDataProviders(QueryInstance);

	//Get Values
	const float _Range = FMath::Clamp(Range.GetValue(),1,MAX_flt);
	const float _RowDistance = FMath::Clamp(RowDistance.GetValue(),1,MAX_flt);

	const float _RowLength = FMath::Clamp(RowLength.GetValue(),1,MAX_flt);
	const float _RowIncrease = FMath::Clamp(RowLengthIncrease.GetValue(),0,MAX_flt);
	const float DistanceBetweenPoints = FMath::Clamp(PointsDistance.GetValue(),1,MAX_flt);


	int PointsToReserve = 0;
	for(int i = 0; i<_Range/_RowDistance; i++)
	{
		PointsToReserve += (_RowLength + (i * _RowIncrease))/DistanceBetweenPoints;
	}
	
	TArray<FNavLocation> GeneratedItems;
	GeneratedItems.Reserve(PointsToReserve);


	
	for(int32 CenterIndex = 0; CenterIndex < CenterActors.Num(); CenterIndex++)
	{
		FVector DesiredDirection;
		switch (Direction)
		{
		case E_ConeDirection::forward:
			DesiredDirection = CenterActors[CenterIndex]->GetActorForwardVector();
			break;
		case E_ConeDirection::right:
			DesiredDirection = CenterActors[CenterIndex]->GetActorRightVector();
			break;
		case E_ConeDirection::left:
			DesiredDirection = CenterActors[CenterIndex]->GetActorRightVector()*-1;
			break;
		case E_ConeDirection::back:
			DesiredDirection = CenterActors[CenterIndex]->GetActorForwardVector()*-1;
			break;
		}

		const FVector ActorLocation = CenterActors[CenterIndex]->GetActorLocation();
		
		const int MaxRows = FMath::FloorToInt(_Range/_RowDistance);
		UE_LOG(LogTemp,Display,TEXT("Maximum Rows %d"),MaxRows);
		for(int Rows = 1; Rows < MaxRows; Rows++)
		{
			float TotalLength = (_RowLength + (_RowIncrease * Rows));
			int Points = TotalLength/DistanceBetweenPoints;
			float OverflowLeft = FMath::Modulo(TotalLength,DistanceBetweenPoints);
			FVector StartPoint = (CenterActors[CenterIndex]->GetActorRightVector()*-1) * ((TotalLength/2)-OverflowLeft);
			
			for(int Plottable = 1; Plottable < Points; Plottable++)
			{
				FVector Offset = StartPoint + (CenterActors[CenterIndex]->GetActorRightVector() * (DistanceBetweenPoints * Plottable));
				const FVector GeneratedLocation = ActorLocation + (_RowDistance * DesiredDirection * Rows) + Offset;
				GeneratedItems.Add(FNavLocation(GeneratedLocation));
			}
		}
		
		if (bIncludeContextLocation)
		{
			GeneratedItems.Add(FNavLocation(ActorLocation));
		}
	}

	ProjectAndFilterNavPoints(GeneratedItems, QueryInstance);
	StoreNavPoints(GeneratedItems, QueryInstance);
	
}

FText UEnvQueryGenerator_Pyramid::GetDescriptionTitle() const
{
	return FText::Format(LOCTEXT("PyramidDescriptionGenerateAroundContext", "{0}: generate points in pyramid from {1}, {2}"),
		Super::GetDescriptionTitle(), UEnvQueryTypes::DescribeContext(CenterActor),UEnum::GetDisplayValueAsText(Direction));
}

FText UEnvQueryGenerator_Pyramid::GetDescriptionDetails() const
{
	FText Desc = FText::Format(LOCTEXT("PyramidDescription", "Rows: {0}"),
		FMath::FloorToInt(Range.GetValue()/RowDistance.GetValue()));

	FText ProjDesc = ProjectionData.ToText(FEnvTraceData::Brief);
	if (!ProjDesc.IsEmpty())
	{
		FFormatNamedArguments ProjArgs;
		ProjArgs.Add(TEXT("Description"), Desc);
		ProjArgs.Add(TEXT("ProjectionDescription"), ProjDesc);
		Desc = FText::Format(LOCTEXT("ConeDescriptionWithProjection", "{Description}, {ProjectionDescription}"), ProjArgs);
	}

	return Desc;
}
#undef LOCTEXT_NAMESPACE
