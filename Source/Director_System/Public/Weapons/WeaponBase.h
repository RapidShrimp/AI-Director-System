// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Director_System/Public/Interfaces/Fireable.h"
#include "UObject/Object.h"
#include "WeaponBase.generated.h"

class UArrowComponent;
class UCameraComponent;
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
	TObjectPtr<USkeletalMeshComponent> _Mesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<UArrowComponent> _Muzzle;
public:
	virtual void InitWeapon_Implementation(UWeaponType* Weapon, USceneComponent* Fireloc) override;
	virtual void StartFiring_Implementation() override;
	virtual void StopFiring_Implementation() override;
	virtual void Reload_Implementation() override;
	virtual void CancelReload_Implementation() override;

	void SetFireTarget(AActor* Target);

	void SetTokenState(bool TokenReceived);
protected:

	bool bHasToken = false;
	virtual void OnFire();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<USceneComponent> FireLocation; 

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<AActor> FireTarget;

	UPROPERTY()
	UCameraComponent* PlayerCam;
	
	UPROPERTY(VisibleAnywhere)
	float FiringTime;
	float BulletSpread;
	int CurrentAmmo;
	int MaxAmmo;
	int AmmoHeld;
	int MagSize;
	float ReloadTime;
	float Damage;
	
	bool bCanFire = true;
	bool bReloading;
	float FireDistance = 4000.0f;
	FTimerHandle FiringTimer;
	FTimerHandle ReloadTimer;

private:
	void OnReloadComplete();
};
