#include "HorrorGameModeBase.h"
#include "MyPlayerController.h"
#include "UObject/ConstructorHelpers.h"

AHorrorGameModeBase::AHorrorGameModeBase()
{
    // �� PlayerController ����
    PlayerControllerClass = AMyPlayerController::StaticClass();

    // �� BP_PlayerCharacter ���� (��Ȯ�� ���)
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(
        TEXT("/Game/BluePrints/BP_PlayerCharacter.BP_PlayerCharacter_C")
    );

    if (PlayerPawnBPClass.Succeeded())
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }
}
