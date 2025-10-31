#include "MyPlayerController.h"
#include "EnhancedInputSubsystems.h" // Enhanced Input System�� Local Player Subsystem�� ����ϱ� ���� ����

AMyPlayerController::AMyPlayerController()
    : InputMappingContext(nullptr),
    MoveAction(nullptr),
    JumpAction(nullptr),
    SprintAction(nullptr),
    LookAction(nullptr)
{
}

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // ���� PlayerController�� ����� Local Player ��ü�� ������    
    if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
    {
        // Local Player���� EnhancedInputLocalPlayerSubsystem�� ȹ��
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            if (InputMappingContext)
            {
                // Subsystem�� ���� �츮�� �Ҵ��� IMC�� Ȱ��ȭ
                // �켱����(Priority)�� 0�� ���� ���� �켱����
                Subsystem->AddMappingContext(InputMappingContext, 0);
            }
        }
    }
}
