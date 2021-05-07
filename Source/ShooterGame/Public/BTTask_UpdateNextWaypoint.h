// Copyright Abhisek Roy. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_UpdateNextWaypoint.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API UBTTask_UpdateNextWaypoint : public UBTTaskNode
{
	GENERATED_BODY()
	UBTTask_UpdateNextWaypoint();

private:
	/** blackboard key selector */
	UPROPERTY(EditAnywhere, Category=Blackboard)
	FBlackboardKeySelector WayPointIndex;

	/** blackboard key selector */
	UPROPERTY(EditAnywhere, Category=Blackboard)
	FBlackboardKeySelector NextWayPoint;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;
};
