// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrollingGuard.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	//UE_LOG(LogTemp, Warning, TEXT("suceeded"));

	//Get patrol points
	auto aiController = OwnerComp.GetAIOwner();
	auto controlledPawn = aiController->GetPawn();
	auto patrollingGuard = Cast<APatrollingGuard>(controlledPawn);
	auto patrollinPoints = patrollingGuard->PatrollPointsCPP;

	//Set next way point
	auto blackBoardComponet = OwnerComp.GetBlackboardComponent();
	auto index = blackBoardComponet->GetValueAsInt(FName(IndexKey.SelectedKeyName));
	blackBoardComponet->SetValueAsObject(WayPointKey.SelectedKeyName, patrollinPoints[index]);

	//Cycle the index
	auto nextIndex = (index + 1) % patrollinPoints.Num();
	blackBoardComponet->SetValueAsInt(IndexKey.SelectedKeyName, nextIndex);

	return EBTNodeResult::Succeeded;
}
