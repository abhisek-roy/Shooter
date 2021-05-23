// Copyright Abhisek Roy. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_PlayerVisible.generated.h"

/**
 * Returns success if Player is visible.
 */
UCLASS()
class SHOOTERGAME_API UBTTask_PlayerVisible : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
	UBTTask_PlayerVisible();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;
};
