// Fill out your copyright notice in the Description page of Project Settings.


#include "Director_System/Public/Characters/CharacterBase.h"
#include "Director_System/Public/Weapons/WeaponBase.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
ACharacterBase::ACharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_Health = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComp"));
	_Health->OnDead.AddUniqueDynamic(this,&ACharacterBase::Handle_Death);
	_Health->OnHealthChanged.AddUniqueDynamic(this,&ACharacterBase::Handle_HealthChange);
	
}

void ACharacterBase::SetGenericTeamId(const FGenericTeamId& TeamID)
{
	_TeamID = TeamID;
}

FGenericTeamId ACharacterBase::GetGenericTeamId() const
{
	return _TeamID;
}

ETeamAttitude::Type ACharacterBase::GetTeamAttitudeTowards(const AActor& Other) const
{
	FGenericTeamId OtherTeamID (FGenericTeamId::GetTeamIdentifier(&Other));
	{
		if(_TeamID == FGenericTeamId(255))
		{
			return ETeamAttitude::Neutral;
		}
		if(_TeamID == OtherTeamID)
		{
			return ETeamAttitude::Friendly;
		}
		if(_TeamID != OtherTeamID)
		{
			return ETeamAttitude::Hostile;
		}
		return ETeamAttitude::Neutral;
	}
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	Init(TestType);

}

void ACharacterBase::Init(UCharacterType* Character)
{
	if(Character == nullptr){return;}
	if(bArmed) 
	{
		//Spawn Weapons using type data
		if(Character->PrimaryWeapon != nullptr)
		{
			FActorSpawnParameters Params;
			Params.Owner = this;
			Params.Name = *("PrimaryWeapon_" + this->GetName());
			PrimaryWeapon = GetWorld()->SpawnActor<AWeaponBase>(AWeaponBase::StaticClass(),Params);
			IFireable::Execute_InitWeapon(PrimaryWeapon , Character->PrimaryWeapon);

			FAttachmentTransformRules AttachParams {EAttachmentRule::SnapToTarget,false};
			AttachParams.RotationRule = EAttachmentRule::SnapToTarget;
			PrimaryWeapon->AttachToComponent(GetMesh(),AttachParams,"Weapon_R");
			SelectedWeapon = PrimaryWeapon;
		}

		if(Character->SecondaryWeapon != nullptr)
		{
			FActorSpawnParameters Params;
			Params.Owner = this;
			Params.Name = *("SecondaryWeapon_" + this->GetName());
			SecondaryWeapon = GetWorld()->SpawnActor<AWeaponBase>(AWeaponBase::StaticClass(),Params);
			IFireable::Execute_InitWeapon(SecondaryWeapon , Character->SecondaryWeapon);

			FAttachmentTransformRules AttachParams {EAttachmentRule::SnapToTarget,false};
			AttachParams.RotationRule = EAttachmentRule::SnapToTarget;
			SecondaryWeapon->AttachToComponent(GetMesh(),AttachParams,"Weapon_L");
		}
	}
}

void ACharacterBase::PickupWeapon(UWeaponType* Weapon, bool IsPrimary)
{
	//Out of Scope - AS
}

void ACharacterBase::StartFire()
{
	if(SelectedWeapon == nullptr){return;}
	UE_LOG(LogTemp,Display,TEXT("Firing"));
	IFireable::Execute_StartFiring(SelectedWeapon);

}

void ACharacterBase::StopFire()
{
	if(SelectedWeapon == nullptr){return;}
	IFireable::Execute_StopFiring(SelectedWeapon);
	UE_LOG(LogTemp,Display,TEXT("Stop Firing"));

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

void ACharacterBase::Handle_Death(AController* InstigatorController)
{
	OnDeath.Broadcast(InstigatorController,this);
}

void ACharacterBase::Handle_HealthChange(AActor* DamageCauser, float CurrentHealth, float MaxHealth, float Change)
{
	OnHealthChange.Broadcast(DamageCauser,this,CurrentHealth,MaxHealth,Change);
}
