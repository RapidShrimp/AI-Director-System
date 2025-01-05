// Fill out your copyright notice in the Description page of Project Settings.


#include "Director_System/Public/Characters/CharacterBase.h"

#include "Components/ArrowComponent.h"
#include "Director_System/Public/Types/CharacterType.h"
#include "Director_System/Public/Weapons/WeaponBase.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_FireStart = CreateDefaultSubobject<UArrowComponent>(TEXT("WeaponFireStartLocation"));
	_FireStart->SetupAttachment(RootComponent);
	
	_Health = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComp"));
	_Health->OnDead.AddUniqueDynamic(this,&ACharacterBase::Handle_Death);
	_Health->OnHealthChanged.AddUniqueDynamic(this,&ACharacterBase::Handle_HealthChange);
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ACharacterBase::BP_Init(UCharacterType* InCharacter)
{
	Init(InCharacter);
}

void ACharacterBase::Init(UCharacterType* InCharacter)
{
	if(InCharacter == nullptr){return;}

	if(InCharacter->SkeletalMesh)
	{
		GetMesh()->SetSkeletalMesh(InCharacter->SkeletalMesh);
	}
	if(bArmed) 
	{
		//Spawn Weapons using type data
		if(InCharacter->PrimaryWeapon != nullptr)
		{
			FActorSpawnParameters Params;
			Params.Owner = this;
			Params.Name = *("PrimaryWeapon_" + this->GetName());
			PrimaryWeapon = GetWorld()->SpawnActor<AWeaponBase>(AWeaponBase::StaticClass(),Params);
			IFireable::Execute_InitWeapon(PrimaryWeapon , InCharacter->PrimaryWeapon, _FireStart);

			FAttachmentTransformRules AttachParams {EAttachmentRule::SnapToTarget,false};
			AttachParams.RotationRule = EAttachmentRule::SnapToTarget;
			PrimaryWeapon->AttachToComponent(GetMesh(),AttachParams,"Weapon_R");
			SelectedWeapon = PrimaryWeapon;
		}

		/*if(InCharacter->SecondaryWeapon != nullptr)
		{
			FActorSpawnParameters Params;
			Params.Owner = this;
			Params.Name = *("SecondaryWeapon_" + this->GetName());
			SecondaryWeapon = GetWorld()->SpawnActor<AWeaponBase>(AWeaponBase::StaticClass(),Params);
			IFireable::Execute_InitWeapon(SecondaryWeapon , InCharacter->SecondaryWeapon);

			FAttachmentTransformRules AttachParams {EAttachmentRule::SnapToTarget,false};
			AttachParams.RotationRule = EAttachmentRule::SnapToTarget;
			SecondaryWeapon->AttachToComponent(GetMesh(),AttachParams,"Weapon_L");
		}*/
	}
}


void ACharacterBase::SetGenericTeamId(const FGenericTeamId& TeamID)
{
	_TeamID = TeamID; 
}

FGenericTeamId ACharacterBase::GetGenericTeamId() const
{
	return _TeamID;
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

AWeaponBase* ACharacterBase::GetCurrentWeapon()
{
	return SelectedWeapon;
}

void ACharacterBase::StartCrouch()
{
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Cyan,TEXT("Crouched"));
	Crouch();
}

void ACharacterBase::StopCrouch()
{
	UnCrouch();
}

void ACharacterBase::Handle_Death(AController* InstigatorController)
{
	OnDeath.Broadcast(InstigatorController,this);
}

void ACharacterBase::Handle_HealthChange(AActor* DamageCauser, float CurrentHealth, float MaxHealth, float Change)
{
	OnHealthChange.Broadcast(DamageCauser,this,CurrentHealth,MaxHealth,Change);
}
