// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/Action/Action.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "RLR.h"

UAction::UAction() :
	bIsActive(false),
	bIsAbilityEnding(false),
	bIsCancelable(false)
{

}

void UAction::TryActivateAction()
{
	PreActivateAction();
	ActivateAction();
}

void UAction::PreActivateAction()
{
	//Action 실행 전 준비
	bIsActive = true;

	//cancel여부 결정
	//bIsCancelable = true;
}

void UAction::ActivateAction()
{
	//Do Someting
}

void UAction::CancelAction()
{
	if (!bIsCancelable) return;

	EndAction();
}

void UAction::EndAction()
{
	//Action을 종료할 수 있는지 
	if (!CanEndAction()) return;

	bIsAbilityEnding = true;
	bIsActive = false;

	//Task 관리

	if (UActionSystemComponent* const ASC = CurrentActorInfo->ActionSystemComponent.Get())
	{
		// Remove tags
		for (auto RemoveTag : ActivationOwnedTags)
		{
			ASC->RemoveGameplayTag(RemoveTag);
		}

		//FX 관리
		
		//ASC에서 제거
		//ASC->NotifyAbilityEnded(Handle, this, bWasCancelled);
	}
}

bool UAction::CanActivateAction()
{
	return true;
}

bool UAction::CanEndAction()
{
	if (bIsActive == false || bIsAbilityEnding == true)
	{
		RLR_LOG(LogRLR, Log, TEXT("EndAction being called multiple times"));
		return false;
	}

	return true;
}