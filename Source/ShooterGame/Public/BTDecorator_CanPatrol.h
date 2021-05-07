// Copyright Abhisek Roy. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_CanPatrol.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API UBTDecorator_CanPatrol : public UBTDecorator
{
	GENERATED_BODY()
	UBTDecorator_CanPatrol();

	/** blackboard key selector */
	UPROPERTY(EditAnywhere, Category=Blackboard)
	FBlackboardKeySelector WayPointIndex;

	/** blackboard key selector */
	UPROPERTY(EditAnywhere, Category=Blackboard)
	FBlackboardKeySelector NextWayPoint;

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
