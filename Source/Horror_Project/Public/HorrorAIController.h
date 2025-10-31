#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "HorrorAIController.generated.h"


class UAIPerceptionComponent;
class UAISenseConfig_Sight;

UCLASS()
class HORROR_PROJECT_API AHorrorAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AHorrorAIController();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UAIPerceptionComponent* AIPerception;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UAISenseConfig_Sight* SightConfig;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	UAnimMontage* AttackMontage;

	// 유포로포티 해서 변수 선언
	UPROPERTY()
	AActor* CurrentTarget = nullptr;
	UFUNCTION()
	void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	bool bIsChasing = false;
	FTimerHandle ChaseTimer;

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

	void StartChasing(AActor* Target);
	void StopChasing();
	void UpdateChase();

private:
	void MoveToRandomLocation();

	FTimerHandle RandomMoveTimer;

	UPROPERTY(EditAnywhere, Category = "AI")
	float MoveRadius = 1000.0f;

};
