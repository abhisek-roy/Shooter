// Copyright Abhisek Roy. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ShooterCharacter.h"
#include "PatrolGuard.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API APatrolGuard : public AShooterCharacter
{
	GENERATED_BODY()

public:

	// Waypoints for patrolling
	UPROPERTY(EditInstanceOnly, Category = "Setup")
	TArray<AActor*> PatrolPoints;
};
