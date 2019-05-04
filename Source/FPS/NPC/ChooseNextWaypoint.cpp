// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PatrolRoute.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	//UE_LOG(LogTemp, Warning, TEXT("suceeded"));
	//Get patrol route
	auto controlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	auto patrolRoute = controlledPawn->FindComponentByClass<UPatrolRoute>();
	if (!ensure(patrolRoute)) { return EBTNodeResult::Failed; }

	auto patrollPoints = patrolRoute->GetPatrolPoints();
	if (patrollPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("A guard is missing patroll points"));
		return EBTNodeResult::Failed;
	}

	//Set next way point
	auto blackBoardComponet = OwnerComp.GetBlackboardComponent();
	auto index = blackBoardComponet->GetValueAsInt(FName(IndexKey.SelectedKeyName));
	blackBoardComponet->SetValueAsObject(WayPointKey.SelectedKeyName, patrollPoints[index]);

	//Cycle the index
	auto nextIndex = (index + 1) % patrollPoints.Num();
	blackBoardComponet->SetValueAsInt(IndexKey.SelectedKeyName, nextIndex);

	return EBTNodeResult::Succeeded;
}
