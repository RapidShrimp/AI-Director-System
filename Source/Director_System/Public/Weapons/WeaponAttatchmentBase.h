// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponAttatchmentBase.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DIRECTOR_SYSTEM_API UWeaponAttatchmentBase : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWeaponAttatchmentBase();

protected:
	virtual void BeginPlay() override;
	virtual void Init();
	
	bool bCanToggle;
public:
	
	bool ToggleAttachment();
	virtual int AttachmentState();
	virtual bool IsToggleable();
	
};
