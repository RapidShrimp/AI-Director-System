// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/WeaponAttatchmentBase.h"


// Sets default values for this component's properties
UWeaponAttatchmentBase::UWeaponAttatchmentBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UWeaponAttatchmentBase::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UWeaponAttatchmentBase::Init()
{
}

bool UWeaponAttatchmentBase::ToggleAttachment()
{
	return false;
}

int UWeaponAttatchmentBase::AttachmentState()
{
	return 0;
}

bool UWeaponAttatchmentBase::IsToggleable()
{
	return false;
}