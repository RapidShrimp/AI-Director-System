// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Director_System/Public/Interfaces/Fireable.h"
#include "UObject/Object.h"
#include "WeaponBase.generated.h"

/**
 * 
 */
UCLASS()
class DIRECTOR_SYSTEM_API AWeaponBase : public AActor, public IFireable
{
	GENERATED_BODY()

	AWeaponBase();
protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> _Mesh;
public:
	virtual void InitWeapon_Implementation(UWeaponType* Weapon) override;
	virtual void StartFiring_Implementation() override;
	virtual void StopFiring_Implementation() override;
	virtual void Reload_Implementation() override;
	virtual void CancelReload_Implementation() override;
protected:
	virtual void OnFire();

	FVector MuzzleLoc;
	float FiringTime;
	float BulletSpread;
	int CurrentAmmo;
	int MaxAmmo;
	int AmmoHeld;
	int MagSize;
	float ReloadTime;
	float Damage;
	
	bool bCanFire;
	bool bReloading;

	FTimerHandle FiringTimer;
	FTimerHandle ReloadTimer;

private:
	void OnReloadComplete();
};
