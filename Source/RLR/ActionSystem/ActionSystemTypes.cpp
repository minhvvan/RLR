// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/ActionSystemTypes.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "ActionSystem/Action/Action.h"

void FActionActorInfo::InitFromActor(AActor* Owner, AActor* Avatar, UActionSystemComponent* InASC)
{
	OwnerActor = Owner;
	AvatarActor = Avatar;
	ActionSystemComponent = InASC;
}

void FActionActorInfo::SetAvatarActor(AActor* Avatar)
{
	AvatarActor = Avatar;
}

void FActionActorInfo::ClearActorInfo()
{
	OwnerActor = nullptr;
	AvatarActor = nullptr;
	ActionSystemComponent = nullptr;
}

FActionSpec::FActionSpec(TSubclassOf<UAction> ActionClass, int32 InLevel, int32 InInputID)
	: Action(ActionClass ? ActionClass.GetDefaultObject() : nullptr)
	, Level(InLevel)
	, InputID(InInputID)
{
}
