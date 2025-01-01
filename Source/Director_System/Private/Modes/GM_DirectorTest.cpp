// Fill out your copyright notice in the Description page of Project Settings.


#include "Modes/GM_DirectorTest.h"

void AGM_DirectorTest::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(StartDelayTimer,this,&AGM_DirectorTest::OnStartTimerComplete,StartDelay,false);
}

void AGM_DirectorTest::OnStartTimerComplete()
{
	OnGameStart.Broadcast();
}

void AGM_DirectorTest::Handle_HealthChanged()
{
}

void AGM_DirectorTest::Handle_Death()
{
}

void AGM_DirectorTest::Handle_WeaponFired()
{
}
