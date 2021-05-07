// Copyright Abhisek Roy. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrolRoute.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTERGAME_API UPatrolRoute : public UActorComponent
{
	GENERATED_BODY()

public:
	// Get patrol waypoints.
	TArray<AActor*> GetPatrolPoints() const {return PatrolPoints;}

private:
	// Waypoints for patrolling
	UPROPERTY(EditInstanceOnly, Category = "Setup")
	TArray<AActor*> PatrolPoints;
		
};
