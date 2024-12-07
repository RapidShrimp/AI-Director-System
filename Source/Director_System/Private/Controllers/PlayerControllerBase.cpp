// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/PlayerControllerBase.h"
#include "Characters/CharacterBase.h"

void APlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();
	SetGenericTeamId(FGenericTeamId{DefaultTeamID});
}

void APlayerControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	_ControlledPawn = Cast<ACharacterBase>(InPawn);
	if(!_ControlledPawn)
	{
		UE_LOG(LogTemp,Error,TEXT("No Character Found for %s"),*GetName());
		return;
	}
	_ControlledPawn->SetGenericTeamId(FGenericTeamId(DefaultTeamID));

}
