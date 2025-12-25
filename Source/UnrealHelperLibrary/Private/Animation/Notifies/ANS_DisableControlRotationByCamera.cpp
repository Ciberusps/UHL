// Pavel Penkov 2025 All Rights Reserved.


#include "Animation/Notifies/ANS_DisableControlRotationByCamera.h"

#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ANS_DisableControlRotationByCamera)

UANS_DisableControlRotationByCamera::UANS_DisableControlRotationByCamera()
{
}

FLinearColor UANS_DisableControlRotationByCamera::GetEditorColor()
{
	return FLinearColor(0.129f, 0.584f, 0.952f);
}

FString UANS_DisableControlRotationByCamera::GetNotifyName_Implementation() const
{
	return TEXT("Disable ControlRotation by Camera");
}

void UANS_DisableControlRotationByCamera::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	bHasCachedState = false;
	CachedCharacter = nullptr;
	CachedController = nullptr;
	CachedPlayerController = nullptr;
	CachedInitialControlRotation = FRotator::ZeroRotator;
	bCachedIgnoreLookInput = false;
	bCachedUseControllerRotationYaw = false;

	if (!MeshComp)
	{
		return;
	}

	ACharacter* Character = Cast<ACharacter>(MeshComp->GetOwner());
	if (!Character)
	{
		return;
	}

	AController* Controller = Character->GetController();
	if (!Controller)
	{
		return;
	}

	CachedCharacter = Character;
	CachedController = Controller;
	CachedInitialControlRotation = Controller->GetControlRotation();
	bCachedUseControllerRotationYaw = Character->bUseControllerRotationYaw;
	Character->bUseControllerRotationYaw = false;

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		CachedPlayerController = PlayerController;
		bCachedIgnoreLookInput = PlayerController->IsLookInputIgnored();
		PlayerController->SetIgnoreLookInput(true);
	}

	bHasCachedState = true;
	ApplyControlRotationLock();
}

void UANS_DisableControlRotationByCamera::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	ApplyControlRotationLock();
}

void UANS_DisableControlRotationByCamera::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	RestoreControlRotation();

	Super::NotifyEnd(MeshComp, Animation, EventReference);
}

void UANS_DisableControlRotationByCamera::OnMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted)
{
	RestoreControlRotation();

	Super::OnMontageBlendingOut(Montage, bInterrupted);
}

void UANS_DisableControlRotationByCamera::ApplyControlRotationLock()
{
	if (!bHasCachedState)
	{
		return;
	}

	ACharacter* Character = CachedCharacter.Get();
	AController* Controller = CachedController.Get();

	if (!Character || !Controller)
	{
		return;
	}

	Controller->SetControlRotation(Character->GetActorRotation());
}

void UANS_DisableControlRotationByCamera::RestoreControlRotation()
{
	if (!bHasCachedState)
	{
		return;
	}

	AController* Controller = CachedController.Get();
	ACharacter* Character = CachedCharacter.Get();

	if (Controller)
	{
		if (Character)
		{
			Controller->SetControlRotation(Character->GetActorRotation());
		}
		else
		{
			Controller->SetControlRotation(CachedInitialControlRotation);
		}
	}

	if (Character)
	{
		Character->bUseControllerRotationYaw = bCachedUseControllerRotationYaw;
	}

	if (APlayerController* PlayerController = CachedPlayerController.Get())
	{
		PlayerController->SetIgnoreLookInput(bCachedIgnoreLookInput);
	}

	CachedCharacter = nullptr;
	CachedController = nullptr;
	CachedPlayerController = nullptr;
	CachedInitialControlRotation = FRotator::ZeroRotator;
	bHasCachedState = false;
}

