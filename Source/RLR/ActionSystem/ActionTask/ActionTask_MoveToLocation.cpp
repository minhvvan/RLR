// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/ActionTask/ActionTask_MoveToLocation.h"
#include "RLR.h"
#include "NavigationPath.h"
#include "NavigationData.h"
#include "NavigationSystem.h"
#include "NavMesh/NavMeshPath.h"
#include "AIController.h"

namespace
{
	UPathFollowingComponent* InitNavigationControl(AController& Controller)
	{
		AAIController* AsAIController = Cast<AAIController>(&Controller);
		UPathFollowingComponent* PathFollowingComp = nullptr;

		if (AsAIController)
		{
			PathFollowingComp = AsAIController->GetPathFollowingComponent();
		}
		else
		{
			PathFollowingComp = Controller.FindComponentByClass<UPathFollowingComponent>();
			if (PathFollowingComp == nullptr)
			{
				PathFollowingComp = NewObject<UPathFollowingComponent>(&Controller);
				PathFollowingComp->RegisterComponentWithWorld(Controller.GetWorld());
				PathFollowingComp->Initialize();
			}
		}

		return PathFollowingComp;
	}
}


UActionTask_MoveToLocation* UActionTask_MoveToLocation::CreateMoveTask(UAction* OwningAction, FName TaskInstanceName, APawn* Pawn, FVector Location, bool bStopWhenActionEnds)
{
	UActionTask_MoveToLocation* MyObj = NewActionTask<UActionTask_MoveToLocation>(OwningAction, TaskInstanceName);
	MyObj->Pawn = Pawn;
	MyObj->GoalLocation = Location;
	MyObj->bStopWhenActionEnds = bStopWhenActionEnds;

	return MyObj;
}

void UActionTask_MoveToLocation::Activate()
{
	if (!Action) return;
	if (!Pawn) return;

	TryMove();
}

void UActionTask_MoveToLocation::ExternalCancel()
{
	if (PFollowComp)
	{
		PFollowComp->AbortMove(*Pawn.Get(), FPathFollowingResultFlags::NewRequest);
	}

	Super::ExternalCancel();
}

void UActionTask_MoveToLocation::OnDestroy(bool ActionEnded)
{
	if (Action)
	{
		Action->OnGameplayAbilityCancelled.Remove(InterruptedHandle);
		if (ActionEnded && bStopWhenActionEnds)
		{
			RLR_LOG(LogRLR, Log, TEXT("Stop"));
		}
	}

	Super::OnDestroy(ActionEnded);
}

void UActionTask_MoveToLocation::TryMove()
{
	auto Controller = Pawn->GetController();

	UNavigationSystemV1* NavSys = Controller ? FNavigationSystem::GetCurrent<UNavigationSystemV1>(Controller->GetWorld()) : nullptr;
	if (NavSys == nullptr || Controller == nullptr || Controller->GetPawn() == nullptr)
	{
		RLR_LOG(LogRLR, Log, TEXT("Can't Get NavSys"));
		OnMoveFinish.Broadcast(false);
		return;
	}

	if(!PFollowComp) PFollowComp = InitNavigationControl(*Controller);

	if (PFollowComp == nullptr)
	{
		RLR_LOG(LogRLR, Log, TEXT("PFollowComp is nullptr"));
		OnMoveFinish.Broadcast(false);
		return;
	}

	if (!PFollowComp->IsPathFollowingAllowed())
	{
		RLR_LOG(LogRLR, Log, TEXT("PFollowComp is not IsPathFollowingAllowed"));
		OnMoveFinish.Broadcast(false);
		return;
	}

	const bool bAlreadyAtGoal = PFollowComp->HasReached(GoalLocation, EPathFollowingReachMode::OverlapAgent);

	// script source, keep only one move request at time
	if (PFollowComp->GetStatus() != EPathFollowingStatus::Idle)
	{
		PFollowComp->AbortMove(*NavSys, FPathFollowingResultFlags::ForcedScript | FPathFollowingResultFlags::NewRequest
			, FAIRequestID::AnyRequest, bAlreadyAtGoal ? EPathFollowingVelocityMode::Reset : EPathFollowingVelocityMode::Keep);
	}

	// script source, keep only one move request at time
	if (PFollowComp->GetStatus() != EPathFollowingStatus::Idle)
	{
		PFollowComp->AbortMove(*NavSys, FPathFollowingResultFlags::ForcedScript | FPathFollowingResultFlags::NewRequest);
	}

	if (bAlreadyAtGoal)
	{
		PFollowComp->RequestMoveWithImmediateFinish(EPathFollowingResult::Success);
	}
	else
	{
		const FVector AgentNavLocation = Controller->GetNavAgentLocation();
		const ANavigationData* NavData = NavSys->GetNavDataForProps(Controller->GetNavAgentPropertiesRef(), AgentNavLocation);
		if (NavData)
		{
			FPathFindingQuery Query(Controller, *NavData, AgentNavLocation, GoalLocation);
			FPathFindingResult Result = NavSys->FindPathSync(Query);
			if (Result.IsSuccessful())
			{
				PFollowComp->OnRequestFinished.AddUObject(this, &UActionTask_MoveToLocation::OnMoveFinished);
				PFollowComp->RequestMove(FAIMoveRequest(GoalLocation), Result.Path);
			}
			else if (PFollowComp->GetStatus() != EPathFollowingStatus::Idle)
			{
				PFollowComp->RequestMoveWithImmediateFinish(EPathFollowingResult::Invalid);
			}
		}
	}
}

void UActionTask_MoveToLocation::OnMoveFinished(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	if (Result.IsSuccess())
	{
		OnMoveFinish.Broadcast(true);
	}
	else
	{
		OnMoveFinish.Broadcast(false);
	}
}