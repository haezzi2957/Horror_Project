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

	UFUNCTION() // 언리얼 엔진의 함수 리플렉션 매크로 !
	void Move(const FInputActionValue& value);          // 이동구현 앞뒤좌우
	UFUNCTION()
	void StartJump(const FInputActionValue& value);     // 점프 시작
	UFUNCTION()
	void StopJump(const FInputActionValue& value);      // 점프 종료
	UFUNCTION()
	void Look(const FInputActionValue& value);          // 마우스 시야회전
	UFUNCTION()
	void StartSprint(const FInputActionValue& value);   // 달리기 시작
	UFUNCTION()
	void StopSprint(const FInputActionValue& value);    // 달리기 끝

private:
	float NormalSpeed;                                  // 기본 이동속도
	float SprintSpeedMultiplier;                        // 달리기 속도(곱해줄 값)
	float SprintSpeed;                                  // 실제 달리기 속도 ( 기본 속도 * 계산된 값 )
	float LookSensitive;                                // 마우스 민감도

public:	
	UFUNCTION(BlueprintCallable)
	void FlashlightToggle();  // 손전등

	virtual void Tick(float DeltaTime) override;
};
