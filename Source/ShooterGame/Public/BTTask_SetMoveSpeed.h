// Copyright Abhisek Roy. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SetMoveSpeed.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API UBTTask_SetMoveSpeed : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_SetMoveSpeed();

	UPROPERTY(EditAnywhere, Category = "Setup", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Speed = 200.0;

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;
};
