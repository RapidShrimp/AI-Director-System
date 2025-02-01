// Fill out your copyright notice in the Description page of Project Settings.


#include "Director_System/Public/Weapons/WeaponBase.h"

#include "Camera/CameraComponent.h"
#include "Characters/CharacterBase.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

AWeaponBase::AWeaponBase()
{
	_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon Mesh");
	SetRootComponent(_Mesh);

	_Muzzle = CreateDefaultSubobject<UArrowComponent>("MuzzleLocation");
	_Muzzle->SetupAttachment(_Mesh);
}
void AWeaponBase::InitWeapon_Implementation(UWeaponType* Weapon, USceneComponent* Fireloc)
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
		if(UCameraComponent* Camera = Cast<UCameraComponent>(OwningCharacter->GetComponentByClass(UCameraComponent::StaticClass())))
		{
			PlayerCam = Camera;
			FireLocation = Camera;
			UE_LOG(LogTemp,Error,TEXT("Weapon Owned by Player"));
		}
		else
		{
			FireLocation = Fireloc;
			UE_LOG(LogTemp,Error,TEXT("Weapon Owned by AI"));
		}
	}
	//Weapon Stats
	_Muzzle->SetRelativeLocation(Weapon->MuzzleLocation);
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
	_Muzzle->SetRelativeLocation(_Mesh->GetSocketLocation("Muzzle"));
	SetActorRelativeRotation(FRotator {9,186,0});

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
	Execute_StopFiring(this);
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

void AWeaponBase::SetFireTarget(AActor* Target)
{
	FireTarget = Target;
}

void AWeaponBase::SetTokenState(bool TokenReceived)
{
	bHasToken = TokenReceived;
	IsControlled = true;
}

void AWeaponBase::SetFriendlyActors( TArray<AActor*> TeamActors)
{
	if(TeamActors.IsEmpty()){return;} //Saftey Check
	FriendlyActors = TeamActors;
	//UE_LOG(LogTemp,Error,TEXT("Updated Token of %s to %hdd"),*GetOwner()->GetName(),TokenReceived)
}

void AWeaponBase::OnFire()
{
	if(CurrentAmmo <= 0)
	{
		Execute_StopFiring(this);
		Execute_Reload(this);
		return;
	}
	
	//Add Firing Override Functionality in Child if wanting to replace hitscan weapon (And remove below code)
	
	FHitResult Result;
	FVector EndLocation;
	FVector StartLocation = FireLocation->GetComponentLocation();
	if(PlayerCam)
	{
		EndLocation =  PlayerCam->GetComponentLocation() + PlayerCam->GetForwardVector() * FireDistance;
		FHitResult CamHit;
		UKismetSystemLibrary::LineTraceSingle(this,FireLocation->GetComponentLocation(),EndLocation,UEngineTypes::ConvertToTraceType(ECC_Visibility),false,{Owner},EDrawDebugTrace::None,CamHit,true);
		EndLocation = CamHit.bBlockingHit ? EndLocation = CamHit.Location : CamHit.TraceEnd;
	}
	else
	{
		if(FireTarget == nullptr){return;}
		FVector FireDir =  FireTarget->GetActorLocation() - StartLocation;
		
		bool RandomHit = IsControlled  ? false : FMath::RandBool();
		
		if(!bHasToken && FireDir.Length() > GuaranteeHitDistance || RandomHit)
		{
			FireDir.Normalize();
			//DrawDebugLine(GetWorld(),FireTarget->GetActorLocation(),FireTarget->GetActorLocation() + FireDir * 50,FColor::Cyan);
			
			FVector RightDir = FVector::CrossProduct(FVector::UpVector,FireDir);
			//DrawDebugLine(GetWorld(),FireTarget->GetActorLocation(),FireTarget->GetActorLocation() + RightDir * 50,FColor::Green);
			if(FMath::RandBool())
			{
				RightDir *= -1;
			}

			FVector VectorPass = FireTarget->GetActorLocation() + RightDir * FMath::RandRange(50,100);
			FVector FireDirection = VectorPass - StartLocation;
			//DrawDebugLine(GetWorld(),StartLocation,FireDirection * FireDistance ,FColor::Yellow);
		
			float RandomZ = FMath::RandRange(-50,50);
			FireDirection.Z = FireDirection.Z + RandomZ;
			EndLocation = FireDirection * FireDistance;
		}
		else
		{
			EndLocation = FireTarget->GetActorLocation() + FVector(0,0,0);

		}
	}

	
	bool Hit = UKismetSystemLibrary::LineTraceSingle(this,
		StartLocation,
		EndLocation,
		UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1),
		false,FriendlyActors,
		EDrawDebugTrace::ForDuration,
		Result,
		true,
		FLinearColor::Red,
		FLinearColor::Green,1.0f);
	if(Hit && bHasToken)
	{
		//Team Checks
		if(bHasToken && IsControlled) {SetTokenState(false);}
		UGameplayStatics::ApplyDamage(Result.GetActor(),Damage,GetInstigatorController(),GetOwner(),UDamageType::StaticClass());
	}
	OnWeaponFired.Broadcast(this);
	CurrentAmmo--;
	BP_OnWeaponFiredVFX();
}

void AWeaponBase::OnReloadComplete()
{
	int RoundsRequired = MagSize - CurrentAmmo;
	CurrentAmmo += RoundsRequired;
	
	bReloading = false;
	bCanFire = true;
	
	//TODO - Mag Ammo Reload Counter Change (LOW)
}
