#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "SurvuvalCharacter.generated.h"

struct FInputActionValue;

UCLASS()
class HORROR_PROJECT_API ASurvuvalCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASurvuvalCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UAIPerceptionStimuliSourceComponent* StimuliSource;

	UFUNCTION() // �𸮾� ������ �Լ� ���÷��� ��ũ�� !
	void Move(const FInputActionValue& value);          // �̵����� �յ��¿�
	UFUNCTION()
	void StartJump(const FInputActionValue& value);     // ���� ����
	UFUNCTION()
	void StopJump(const FInputActionValue& value);      // ���� ����
	UFUNCTION()
	void Look(const FInputActionValue& value);          // ���콺 �þ�ȸ��
	UFUNCTION()
	void StartSprint(const FInputActionValue& value);   // �޸��� ����
	UFUNCTION()
	void StopSprint(const FInputActionValue& value);    // �޸��� ��

private:
	float NormalSpeed;                                  // �⺻ �̵��ӵ�
	float SprintSpeedMultiplier;                        // �޸��� �ӵ�(������ ��)
	float SprintSpeed;                                  // ���� �޸��� �ӵ� ( �⺻ �ӵ� * ���� �� )
	float LookSensitive;                                // ���콺 �ΰ���

public:	
	UFUNCTION(BlueprintCallable)
	void FlashlightToggle();  // ������

	virtual void Tick(float DeltaTime) override;
};
