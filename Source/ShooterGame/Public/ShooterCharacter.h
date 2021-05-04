// 2021 Copyrighted, Abhisek Roy

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;

UCLASS()
class SHOOTERGAME_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void Shoot();
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure)
	float GetHealth() const { return CurrentHealth;}

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

private:

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);

	UPROPERTY(EditAnywhere, Category = "Camera", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float RotateRate = 50.0f;

	UPROPERTY(EditAnywhere, Category = "Setup", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MaxHealth = 100.0f;

	UPROPERTY(VisibleAnywhere, Category = "Setup", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float CurrentHealth = MaxHealth;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunBlueprint;

	UPROPERTY()
	AGun* Gun = nullptr;
};


