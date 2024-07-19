// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/ActionTask/ActionTask_PlayMontage.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "GameFramework/Character.h"
#include "RLR.h"

void UActionTask_PlayMontage::OnMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted)
{
	const bool bPlayingThisMontage = (Montage == MontageToPlay) && Action && Action->GetCurrentMontage() == MontageToPlay;

	if (bPlayingThisMontage && (bInterrupted || !bAllowInterruptAfterBlendOut))
	{
		if (UActionSystemComponent* ASC = ActionSystemComponent.Get())
		{
			ASC->ClearAnimatingAction(Action);
		}
	}

	if (bInterrupted) OnInterrupted.Broadcast();
	else OnBlendOut.Broadcast();
}

void UActionTask_PlayMontage::OnActionCancelled()
{
	EndTask();
}

void UActionTask_PlayMontage::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (bInterrupted) OnInterrupted.Broadcast();
	else OnCompleted.Broadcast();

	EndTask();
}

UActionTask_PlayMontage* UActionTask_PlayMontage::CreatePlayMontageTask(UAction* OwningAction, FName TaskInstanceName, UAnimMontage* MontageToPlay, float Rate, FName StartSection, bool bStopWhenAbilityEnds, float AnimRootMotionTranslationScale, float StartTimeSeconds, bool bAllowInterruptAfterBlendOut)
{
	UActionTask_PlayMontage* MyObj = NewActionTask<UActionTask_PlayMontage>(OwningAction, TaskInstanceName);
	MyObj->MontageToPlay = MontageToPlay;
	MyObj->Rate = Rate;
	MyObj->StartSection = StartSection;
	MyObj->AnimRootMotionTranslationScale = AnimRootMotionTranslationScale;
	MyObj->bStopWhenAbilityEnds = bStopWhenAbilityEnds;
	MyObj->bAllowInterruptAfterBlendOut = bAllowInterruptAfterBlendOut;
	MyObj->StartTimeSeconds = StartTimeSeconds;

	return MyObj;
}

void UActionTask_PlayMontage::Activate()
{
	if (Action == nullptr) return;

	bool bPlayedMontage = false;

	if (UActionSystemComponent* ASC = ActionSystemComponent.Get())
	{
		const FActionActorInfo* ActorInfo = Action->GetCurrentActorInfo();
		UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			if (ASC->PlayMontage(Action, MontageToPlay, Rate, StartSection, StartTimeSeconds) > 0.f)
			{
				InterruptedHandle = Action->OnGameplayAbilityCancelled.AddUObject(this, &UActionTask_PlayMontage::OnActionCancelled);

				BlendingOutDelegate.BindUObject(this, &UActionTask_PlayMontage::OnMontageBlendingOut);
				AnimInstance->Montage_SetBlendingOutDelegate(BlendingOutDelegate, MontageToPlay);

				MontageEndedDelegate.BindUObject(this, &UActionTask_PlayMontage::OnMontageEnded);
				AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, MontageToPlay);

				//TODO: CharacterRole Check

				bPlayedMontage = true;
			}
		}
	}

	//TODO: Avatar 관련 처리
	//SetWaitingOnAvatar();
}

void UActionTask_PlayMontage::ExternalCancel()
{
	Super::ExternalCancel();
}

void UActionTask_PlayMontage::OnDestroy(bool ActionEnded)
{
	if (Action)
	{
		Action->OnGameplayAbilityCancelled.Remove(InterruptedHandle);
		if (ActionEnded && bStopWhenAbilityEnds)
		{
			StopPlayingMontage();
			RLR_LOG(LogRLR, Log, TEXT("Stop"));
		}
	}

	Super::OnDestroy(ActionEnded);
}

bool UActionTask_PlayMontage::StopPlayingMontage()
{
	if (Action == nullptr) return false;

	const FActionActorInfo* ActorInfo = Action->GetCurrentActorInfo();
	if (ActorInfo == nullptr) return false;

	UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();
	if (AnimInstance == nullptr) return false;


	UActionSystemComponent* ASC = ActionSystemComponent.Get();
	if (ASC && Action)
	{
		if (ASC->GetAnimatingAction() == Action && ASC->GetCurrentMontage() == MontageToPlay)
		{
			FAnimMontageInstance* MontageInstance = AnimInstance->GetActiveInstanceForMontage(MontageToPlay);
			if (MontageInstance)
			{
				MontageInstance->OnMontageBlendingOutStarted.Unbind();
				MontageInstance->OnMontageEnded.Unbind();
			}

			ASC->CurrentMontageStop();
			return true;
		}
	}

	return false;
}
