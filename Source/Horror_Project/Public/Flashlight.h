#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Flashlight.generated.h"

UCLASS()
class HORROR_PROJECT_API AFlashlight : public AActor
{
	GENERATED_BODY()
	
public:	
	AFlashlight();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
};
