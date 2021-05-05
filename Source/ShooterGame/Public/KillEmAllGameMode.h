// Copyright Abhisek Roy. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ShooterGameGameModeBase.h"
#include "KillEmAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API AKillEmAllGameMode : public AShooterGameGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void PawnKilled(APawn* PawnKilled) override;

private:
	void EndGame(bool bIsPlayerWinner);
};
