#include "HorrorAIController.h"
#include "TimerManager.h"
#include "NavigationSystem.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "HorrorAICharacter.h"
#include "Kismet/GameplayStatics.h"

AHorrorAIController::AHorrorAIController()
{
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	SetPerceptionComponent(*AIPerception);

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 1500.0f;
	SightConfig->LoseSightRadius = 2000.0f;
	SightConfig->PeripheralVisionAngleDegrees = 90.0f;
	SightConfig->SetMaxAge(5.0f);

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	AIPerception->ConfigureSense(*SightConfig);
	AIPerception->SetDominantSense(SightConfig->GetSenseImplementation());
}

void AHorrorAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIPerception)
	{
		AIPerception->OnTargetPerceptionUpdated.AddDynamic(
			this,
			&AHorrorAIController::OnPerceptionUpdated
		);
	}

	GetWorldTimerManager().SetTimer(
		RandomMoveTimer,
		this,
		&AHorrorAIController::MoveToRandomLocation,
		3.0f,
		true,
		1.0f
	);
}

void AHorrorAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (InPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("[Horror] AI Controller is controlling %s."), *InPawn->GetName());
	}
}

void AHorrorAIController::MoveToRandomLocation()
{
	APawn* MyPawn = GetPawn();
	if (!MyPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("[Horror] No Pawn to control."));
	}

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (!NavSystem)
	{
		UE_LOG(LogTemp, Error, TEXT("[Horror] Could not find Navigation System."));
	}

	FNavLocation RandomLocation;
	bool bFoundLocation = NavSystem->GetRandomReachablePointInRadius(
		MyPawn->GetActorLocation(),
		MoveRadius,
		RandomLocation
	);

	if (bFoundLocation)
	{
		MoveToLocation(RandomLocation.Location);

		UE_LOG(LogTemp, Warning, TEXT("[Horror] Move target: %s"), *RandomLocation.Location.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[Horror] Could not find a reachable location."));
	}
}

void AHorrorAIController::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (Actor != PlayerPawn)
	{
		return;
	}

	if (Stimulus.WasSuccessfullySensed())
	{
		StartChasing(Actor);
	}
	else
	{
		StopChasing();
	}
}

void AHorrorAIController::StartChasing(AActor* Target)
{
	if (bIsChasing && CurrentTarget == Target) return;

	CurrentTarget = Target;
	bIsChasing = true;

	// 공격 구현할것

	GetWorldTimerManager().ClearTimer(RandomMoveTimer);

	if (AHorrorAICharacter* AIChar = Cast<AHorrorAICharacter>(GetPawn()))
	{
		AIChar->SetMovementSpeed(AIChar->RunSpeed);
	}

	UpdateChase();
	GetWorldTimerManager().SetTimer(
		ChaseTimer,
		this,
		&AHorrorAIController::UpdateChase,
		0.25f,
		true
	);
}

void AHorrorAIController::StopChasing()
{
	if (!bIsChasing) return;

	CurrentTarget = nullptr;
	bIsChasing = false;

	GetWorldTimerManager().ClearTimer(ChaseTimer);

	StopMovement();

	if (AHorrorAICharacter* AIChar = Cast<AHorrorAICharacter>(GetPawn()))
	{
		AIChar->SetMovementSpeed(AIChar->WalkSpeed);
	}

	GetWorldTimerManager().SetTimer(
		RandomMoveTimer,
		this,
		&AHorrorAIController::MoveToRandomLocation,
		3.0f,
		true,
		2.0f
	);
}

void AHorrorAIController::UpdateChase()
{
	if (CurrentTarget && bIsChasing)
	{
		APawn* MyPawn = GetPawn();
		if (!MyPawn) return;

		// 거리 계산
		float DistanceToTarget = FVector::Dist(MyPawn->GetActorLocation(), CurrentTarget->GetActorLocation());

		// 공격 사거리
		float AttackRange = 150.0f;

		if (DistanceToTarget <= AttackRange)
		{
			// 이동 중지하고 공격
			StopMovement();

			if (AHorrorAICharacter* AIChar = Cast<AHorrorAICharacter>(MyPawn))
			{
				// 공격 중복 방지
				if (!AIChar->IsAttacking())
				{
					AIChar->Attack();
				}
			}
		}
		else
		{
			MoveToActor(CurrentTarget, 100.0f);
		}
	}
}