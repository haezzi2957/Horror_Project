#include "HorrorAICharacter.h"
#include "HorrorAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

AHorrorAICharacter::AHorrorAICharacter()
{
	AIControllerClass = AHorrorAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->MaxWalkSpeed = WalkSpeed;
	Movement->bOrientRotationToMovement = true;
	Movement->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
}

void AHorrorAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("[Horror] AI character has been spawned."));
}

void AHorrorAICharacter::SetMovementSpeed(float NewSpeed)
{
	if (UCharacterMovementComponent* Movement = GetCharacterMovement())
	{
		Movement->MaxWalkSpeed = NewSpeed;
		UE_LOG(LogTemp, Warning, TEXT("[Horror] Speed changed: %.1f"), NewSpeed);
	}
}

void AHorrorAICharacter::Attack()
{
	if (bIsAttacking)
	{
		return;
	}
	
	bIsAttacking = true;

	if (AttackMontage)
	{
		PlayAnimMontage(AttackMontage);
	}

	GetWorldTimerManager().SetTimer(
		AttackResetTimer,
		this,
		&AHorrorAICharacter::ResetAttackState,
		3.0f,
		false
	);
}

void AHorrorAICharacter::ResetAttackState()
{
	bIsAttacking = false;
	UE_LOG(LogTemp, Warning, TEXT("[HorrorAI] Attack finished. Ready for next attack."));
}

bool AHorrorAICharacter::IsAttacking() const
{
	return bIsAttacking;
}