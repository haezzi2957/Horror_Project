#include "Flashlight.h"

AFlashlight::AFlashlight()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AFlashlight::BeginPlay()
{
	Super::BeginPlay();
}

void AFlashlight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

