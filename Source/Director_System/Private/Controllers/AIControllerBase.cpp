// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/AIControllerBase.h"

#include "Characters/CharacterBase.h"
#include "Types/CharacterType.h"

void AAIControllerBase::SpawnAI(UCharacterType* InCharacter, UBehaviorTree* Behaviour, uint8 AssignTeamID, FTransform InTransform)
{
	BehaviourTree = Behaviour;
	FActorSpawnParameters SpawnParameters{};
	SpawnParameters.Owner = this;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	_ControlledPawn = GetWorld()->SpawnActor<ACharacterBase>(InCharacter->CharacterClass,InTransform.GetLocation(),InTransform.Rotator(),SpawnParameters);
	if(!_ControlledPawn) {return;}
	_ControlledPawn->SetGenericTeamId(FGenericTeamId{AssignTeamID});
	_ControlledPawn->Init(InCharacter);
}

void AAIControllerBase::StartGame()
{
	if(BehaviourTree == nullptr)
	{
		UE_LOG(LogTemp,Error,TEXT("%s has no assigned behaviour tree, Removing possessed pawn"),*GetName());
		_ControlledPawn->Destroy();
		Destroy();
		return;
	}
	RunBehaviorTree(BehaviourTree);
}

ETeamAttitude::Type AAIControllerBase::GetTeamAttitudeTowards(const AActor& Other) const
{
	const FGenericTeamId MyID  = FGenericTeamId::GetTeamIdentifier(_ControlledPawn);
	const FGenericTeamId OtherTeamID (FGenericTeamId::GetTeamIdentifier(&Other));
	if(MyID.GetId() == 255)
	{
		return ETeamAttitude::Neutral;
	}
	if(MyID == OtherTeamID)
	{
		return ETeamAttitude::Friendly;
	}
	if(MyID != OtherTeamID)
	{
		return ETeamAttitude::Hostile;
	}
	return ETeamAttitude::Neutral;
}
