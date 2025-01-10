// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/AIControllerBase.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/CharacterBase.h"
#include "Types/CharacterType.h"
#include "Weapons/WeaponBase.h"

void AAIControllerBase::SpawnAI(UCharacterType* InCharacter, UBehaviorTree* Behaviour, uint8 AssignTeamID, FTransform InTransform)
{
	BehaviourTree = Behaviour;
	FActorSpawnParameters SpawnParameters{};
	SpawnParameters.Owner = this;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	_ControlledPawn = GetWorld()->SpawnActor<ACharacterBase>(InCharacter->CharacterClass,InTransform.GetLocation(),InTransform.Rotator(),SpawnParameters);
	if(!_ControlledPawn) {return;}
	_ControlledPawn->SetGenericTeamId(FGenericTeamId{AssignTeamID});
	_ControlledPawn->OnCharacterWeaponFiredSignature.AddUniqueDynamic(this,&AAIControllerBase::Handle_WeaponFired);
	_ControlledPawn->OnDeath.AddUniqueDynamic(this,&AAIControllerBase::Handle_AIDeath);
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

void AAIControllerBase::SetFireTarget(AActor* Target)
{
	if(!Blackboard || !_ControlledPawn)
	{
		UE_LOG(LogTemp,Error,TEXT("NO PAWN OR BLACKBOARD"))
		return;
	}
	Blackboard->SetValueAsObject("Target",Target);
	AWeaponBase* Gun = _ControlledPawn->GetCurrentWeapon();

	if(Gun != nullptr)
	{
		Gun->SetFireTarget(Target);
	}
}

void AAIControllerBase::SetDirected()
{
	if(!_ControlledPawn)
	{
		UE_LOG(LogTemp,Error,TEXT("MassiveFuckingProblem - No Controlled pawn when setting director defaults"));
		return;
	}
	_ControlledPawn->GetCurrentWeapon()->SetTokenState(false);
	if(_ControlledPawn->GetCurrentWeapon() == nullptr)
	{
		UE_LOG(LogTemp,Error,TEXT("No Weapon"));
		return;
	}
}

TArray<AActor*> AAIControllerBase::GetPercievedActors_Implementation()
{
	TArray<AActor*> Empty;
	return Empty;
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
void AAIControllerBase::Handle_WeaponFired(AWeaponBase* Weapon, ACharacterBase* InCharacter)
{
	OnAICWeaponFired.Broadcast(Weapon,InCharacter);
	BPHandle_WeaponFired(Weapon,InCharacter);
}

void AAIControllerBase::Handle_AIDeath(AController* Controller, ACharacterBase* CharacterBase)
{
	BPHandle_AIDeath(Controller,CharacterBase);
}