// Fill out your copyright notice in the Description page of Project Settings.


#include "Director_System/Public/Characters/CharacterBase.h"
#include "Director_System/Public/Weapons/WeaponBase.h"


// Sets default values
ACharacterBase::ACharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ACharacterBase::SetGenericTeamId(const FGenericTeamId& TeamID)
{
	_TeamID = TeamID;
}

FGenericTeamId ACharacterBase::GetGenericTeamId() const
{
	return _TeamID;
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	Init();

}

void ACharacterBase::Init()
{
	if(bArmed)
	{
		FActorSpawnParameters Params;
		Params.Owner = this;
		Params.Name = *("PrimaryWeapon_" + this->GetName());
		GetWorld()->SpawnActor<AWeaponBase>(AWeaponBase::StaticClass(),Params);
	}
}

void ACharacterBase::PickupWeapon(UWeaponType* Weapon)
{

}

void ACharacterBase::StartFire()
{
	if(SelectedWeapon == nullptr){return;}
	IFireable::Execute_StartFiring(SelectedWeapon);

}

void ACharacterBase::StopFire()
{
	if(SelectedWeapon == nullptr){return;}
	IFireable::Execute_StopFiring(SelectedWeapon);

}

void ACharacterBase::Reload()
{
	if(SelectedWeapon == nullptr){return;}
	IFireable::Execute_Reload(SelectedWeapon);
}

void ACharacterBase::SwapWeapon()
{
	//If the weapon is not held
	if(SelectedWeapon == nullptr)
	{
		if(PrimaryWeapon != nullptr)
		{
			SelectedWeapon = PrimaryWeapon;
		}
		else if(SelectedWeapon != nullptr)
		{
			SelectedWeapon = SecondaryWeapon;
		}
	}

	//Can swap weapons?
	AWeaponBase* OtherWeapon = SelectedWeapon == PrimaryWeapon ? SecondaryWeapon : PrimaryWeapon;
	if(OtherWeapon !=nullptr)
	{
		SelectedWeapon = OtherWeapon;
		GEngine->AddOnScreenDebugMessage(-1,5,FColor::Cyan,TEXT("Swapped Weapon"));
	}
	
}
