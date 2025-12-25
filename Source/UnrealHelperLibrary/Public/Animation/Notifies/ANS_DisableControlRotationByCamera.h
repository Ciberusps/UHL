// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/Notifies/ANS_UHL_Base.h"
#include "ANS_DisableControlRotationByCamera.generated.h"

class ACharacter;
class AController;
class APlayerController;

UCLASS()
class UNREALHELPERLIBRARY_API UANS_DisableControlRotationByCamera : public UANS_UHL_Base
{
	GENERATED_BODY()

public:
	UANS_DisableControlRotationByCamera();

protected:
#if WITH_EDITOR
	virtual bool ShouldFireInEditor() override { return false; }
#endif

	virtual FLinearColor GetEditorColor() override;
	virtual FString GetNotifyName_Implementation() const override;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	virtual void OnMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted) override;

private:
	void ApplyControlRotationLock();
	void RestoreControlRotation();

	UPROPERTY()
	TWeakObjectPtr<ACharacter> CachedCharacter;

	UPROPERTY()
	TWeakObjectPtr<AController> CachedController;

	UPROPERTY()
	TWeakObjectPtr<APlayerController> CachedPlayerController;

	UPROPERTY()
	FRotator CachedInitialControlRotation = FRotator::ZeroRotator;

	bool bCachedIgnoreLookInput = false;
	bool bCachedUseControllerRotationYaw = false;
	bool bHasCachedState = false;
};

