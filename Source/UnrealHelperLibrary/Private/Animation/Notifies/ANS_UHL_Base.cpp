// Pavel Penkov 2025 All Rights Reserved.


#include "Animation/Notifies/ANS_UHL_Base.h"
#include "Runtime/Engine/Classes/Animation/AnimMontage.h"
#include "Engine/World.h"
#include "Components/SkeletalMeshComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ANS_UHL_Base)

void UANS_UHL_Base::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	CurrentAnimMontage = EventReference.GetNotify()->GetLinkedMontage();

	if (CurrentAnimMontage.IsValid())
	{
		if (bUseOnMontageBlendingOut)
		{
			MeshComp->AnimScriptInstance->OnMontageBlendingOut.AddUniqueDynamic(this, &UANS_UHL_Base::_OnMontageBlendOut);
		}
	}
}

void UANS_UHL_Base::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (ShouldUseExperimentalUHLFeatures())
	{
		NotifyEndOrBlendOut(MeshComp);
	}

	if (bUseOnMontageBlendingOut)
	{
		MeshComp->AnimScriptInstance->OnMontageBlendingOut.RemoveDynamic(this, &UANS_UHL_Base::_OnMontageBlendOut);
	}
}

/** Experimental **/ 
void UANS_UHL_Base::NotifyEndOrBlendOut(USkeletalMeshComponent* MeshComp)
{
	if (!ShouldUseExperimentalUHLFeatures()) return;
}
/** ~Experimental **/ 

void UANS_UHL_Base::OnMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted)
{
	if (!Montage)
	{
		return;
	}

	if (ShouldUseExperimentalUHLFeatures())
	{
		UObject* Outer = Montage->GetOuter();
		USkeletalMeshComponent* SkeletalMeshComponent = Cast<USkeletalMeshComponent>(Outer);
		if (SkeletalMeshComponent)
		{
			NotifyEndOrBlendOut(SkeletalMeshComponent);
		}
	}
}

void UANS_UHL_Base::_OnMontageBlendOut(UAnimMontage* Montage, bool bInterrupted)
{
	if (!Montage) return;
	
	if (Montage == CurrentAnimMontage)
	{
		OnMontageBlendingOut(Montage, bInterrupted);
	}
}
