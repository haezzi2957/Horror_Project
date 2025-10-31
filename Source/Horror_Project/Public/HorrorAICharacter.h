#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HorrorAICharacter.generated.h"

UCLASS()
class HORROR_PROJECT_API AHorrorAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AHorrorAICharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	UAnimMontage* AttackMontage;
	UFUNCTION(BlueprintCallable, Category = "Attack")
	void Attack();
	UFUNCTION(BlueprintPure, Category = "Attack")
	bool IsAttacking() const;

	void SetMovementSpeed(float NewSpeed);

	UPROPERTY(EditAnywhere, Category = "AI")
	float WalkSpeed = 150.0f;

	UPROPERTY(EditAnywhere, Category = "AI")
	float RunSpeed = 480.0f;

protected:
	virtual void BeginPlay() override;
	void ResetAttackState();

	bool bIsAttacking = false;
	FTimerHandle AttackResetTimer;
};
