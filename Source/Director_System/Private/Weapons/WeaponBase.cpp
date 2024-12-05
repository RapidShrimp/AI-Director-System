// Fill out your copyright notice in the Description page of Project Settings.


#include "Director_System/Public/Weapons/WeaponBase.h"

#include "Camera/CameraComponent.h"
#include "Characters/CharacterBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

AWeaponBase::AWeaponBase()
{
	_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon Mesh");
	_Mesh->SetupAttachment(RootComponent);
}

void AWeaponBase::InitWeapon_Implementation(UWeaponType* Weapon)
{
	if(Weapon == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1,0.5,FColor::Cyan,TEXT("Could not Load Weapon Data Asset!"));
		return;
	}

	//AI vs Player Distinction
	if(GetOwner()!=nullptr)
	{
		ACharacterBase* OwningCharacter = Cast<ACharacterBase>(GetOwner());
		if(!OwningCharacter)
		{
			UE_LOG(LogTemp,Error,TEXT("Weapon %s has no owner"), *GetName());
		}
		OwningPlayerCam = Cast<UCameraComponent>(OwningCharacter->GetComponentByClass(UCameraComponent::StaticClass()));
		if(OwningPlayerCam)
		{
			UE_LOG(LogTemp,Error,TEXT("Weapon Owned by Player"));
		}
		else
		{
			UE_LOG(LogTemp,Error,TEXT("Weapon Owned by AI"));
		}
	}
	//Weapon Stats
	MuzzleLoc = Weapon->MuzzleLocation;
	FiringTime = Weapon->FiringTime;
	BulletSpread = Weapon->BulletSpread;
	CurrentAmmo = Weapon->MagSize;
	MaxAmmo = Weapon->MaxAmmo;
	MagSize = Weapon->MagSize;
	ReloadTime = Weapon->ReloadTime;
	Damage = Weapon->Damage;
	
	if(Weapon->WeaponMesh == nullptr) {return;}
	_Mesh->SetSkeletalMeshAsset(Weapon->WeaponMesh);

	if(_Mesh->DoesSocketExist("Muzzle") == false){return;}
	MuzzleLoc = _Mesh->GetSocketLocation("Muzzle");
}

void AWeaponBase::StartFiring_Implementation()
{
	if(!bCanFire) {return;}

	GetWorld()->GetTimerManager().SetTimer(FiringTimer,this,&AWeaponBase::OnFire,FiringTime,true);
	
}

void AWeaponBase::StopFiring_Implementation()
{
	GetWorld()->GetTimerManager().ClearTimer(FiringTimer);
	FiringTimer.Invalidate();
}

void AWeaponBase::Reload_Implementation()
{
	StopFiring();
	bCanFire = false;
	bReloading = true;
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer,this,&AWeaponBase::OnReloadComplete,ReloadTime,false);
}

void AWeaponBase::CancelReload_Implementation()
{
	bReloading = false;
	GetWorld()->GetTimerManager().ClearTimer(ReloadTimer);
	ReloadTimer.Invalidate();
}

void AWeaponBase::OnFire()
{
	if(CurrentAmmo <= 0)
	{
		StopFiring();
		Reload();
		return;
	}
	
	//Add Firing Override Functionality in Child if wanting to replace hitscan weapon (And remove below code)

	FHitResult Result;
	FVector ForwardDir = Owner != nullptr ? GetActorForwardVector() : Owner->GetActorForwardVector(); 
	bool Hit = UKismetSystemLibrary::LineTraceSingle(this,
		MuzzleLoc,
		ForwardDir,
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false,{},
		EDrawDebugTrace::None,
		Result,
		true,
		FLinearColor::Red,
		FLinearColor::Green);
	if(Hit)
	{
		UGameplayStatics::ApplyDamage(Result.GetActor(),Damage,GetInstigatorController(),GetOwner(),UDamageType::StaticClass());
	}
}

void AWeaponBase::OnReloadComplete()
{
	int RoundsRequired = MagSize - CurrentAmmo;
	CurrentAmmo += RoundsRequired;
	
	bReloading = false;
	bCanFire = true;
	
	//TODO - Mag Ammo Reload Counter Change (LOW)
}
