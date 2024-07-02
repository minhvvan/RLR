// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/ActionSystemTypes.h"
#include "ActionSystem/ActionSystemComponent.h"

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