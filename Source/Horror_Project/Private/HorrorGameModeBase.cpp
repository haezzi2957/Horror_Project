#include "HorrorGameModeBase.h"
#include "MyPlayerController.h"
#include "UObject/ConstructorHelpers.h"

AHorrorGameModeBase::AHorrorGameModeBase()
{
    // ① PlayerController 지정
    PlayerControllerClass = AMyPlayerController::StaticClass();

    // ② BP_PlayerCharacter 지정 (정확한 경로)
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(
        TEXT("/Game/BluePrints/BP_PlayerCharacter.BP_PlayerCharacter_C")
    );

    if (PlayerPawnBPClass.Succeeded())
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }
}
