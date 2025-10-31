#include "SurvuvalCharacter.h"
#include "MyPlayerController.h"
#include "EnhancedInputComponent.h"
#include "Perception/AISense_Sight.h"
#include "GameFramework/CharacterMovementComponent.h"


ASurvuvalCharacter::ASurvuvalCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	NormalSpeed = 200.0f;
	SprintSpeedMultiplier = 2.0f;
	SprintSpeed = NormalSpeed * SprintSpeedMultiplier;
	//LookSensitive = 0.3f;
	
	GetCharacterMovement()->JumpZVelocity = 350.f;
	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;

	StimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("StimuliSource"));
}

void ASurvuvalCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (StimuliSource)
	{
		StimuliSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
		StimuliSource->RegisterWithPerceptionSystem();
	}
}

void ASurvuvalCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&ASurvuvalCharacter::Move
				);
			}

			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&ASurvuvalCharacter::Look
				);
			}

			if (PlayerController->JumpAction)
			{
				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Triggered,
					this,
					&ASurvuvalCharacter::StartJump
				);

				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Completed,
					this,
					&ASurvuvalCharacter::StopJump
				);
			}

			if (PlayerController->SprintAction)
			{
				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					ETriggerEvent::Triggered,
					this,
					&ASurvuvalCharacter::StartSprint
				);

				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					ETriggerEvent::Completed,
					this,
					&ASurvuvalCharacter::StopSprint
				);
			}

			if (PlayerController->FlashlightAction)
			{
				EnhancedInput->BindAction(
					PlayerController->FlashlightAction,
					ETriggerEvent::Started,
					this,
					&ASurvuvalCharacter::FlashlightToggle
				);
			}
		}
	}

}

void ASurvuvalCharacter::Move(const FInputActionValue& value)
{
	if (!Controller) return;

	const FVector2D MoveInput = value.Get<FVector2D>();
	// 체크해볼것
	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		AddMovementInput(GetActorForwardVector(), MoveInput.Y);
	}

	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		AddMovementInput(GetActorRightVector(), MoveInput.X);
	}
}

void ASurvuvalCharacter::Look(const FInputActionValue& value)
{
	FVector2D LookInput = value.Get<FVector2D>();

	AddControllerYawInput(LookInput.X);
	//AddControllerYawInput(LookInput.X * LookSensitive);
	AddControllerPitchInput(LookInput.Y);
	//AddControllerPitchInput(LookInput.Y * LookSensitive);
}

void ASurvuvalCharacter::StartJump(const FInputActionValue& value)
{
	if (value.Get<bool>())
	{
		Jump();
	}
}
void ASurvuvalCharacter::StopJump(const FInputActionValue& value)
{
	if (!value.Get<bool>())
	{
		StopJumping();
	}
}
void ASurvuvalCharacter::StartSprint(const FInputActionValue& value)
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
}
void ASurvuvalCharacter::StopSprint(const FInputActionValue& value)
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	}
}

void ASurvuvalCharacter::FlashlightToggle()
{

}

void ASurvuvalCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
