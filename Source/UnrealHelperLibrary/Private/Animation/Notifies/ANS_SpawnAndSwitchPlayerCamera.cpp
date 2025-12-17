// Pavel Penkov 2025 All Rights Reserved.


#include "Animation/Notifies/ANS_SpawnAndSwitchPlayerCamera.h"

#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

TMap<TWeakObjectPtr<USkeletalMeshComponent>, UANS_SpawnAndSwitchPlayerCamera::FNotifyState> UANS_SpawnAndSwitchPlayerCamera::NotifyStateMap;

void UANS_SpawnAndSwitchPlayerCamera::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

    if (!MeshComp || !CameraToSpawnClass)
    {
        return;
    }

    // 1. Get the owning actor and its PlayerController
    AActor* OwningActor = MeshComp->GetOwner();
    if (!OwningActor)
    {
        return;
    }

    APlayerController* PC = Cast<APlayerController>(OwningActor->GetInstigatorController());
    if (!PC)
    {
        // If the owning actor isn’t possessed by a PC, try another route
        PC = UGameplayStatics::GetPlayerController(OwningActor->GetWorld(), PlayerControllerIndex);
    }
    if (!PC)
    {
        return;
    }

	FNotifyState& State = NotifyStateMap.FindOrAdd(MeshComp);
	State.PreviousViewTarget = PC->GetViewTarget();

	FTransform SpawnTransform = OwningActor->GetActorTransform();
	if (AttachSocketName != NAME_None && MeshComp->DoesSocketExist(AttachSocketName))
	{
		SpawnTransform = MeshComp->GetSocketTransform(AttachSocketName);
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = OwningActor;
	SpawnParams.Instigator = Cast<APawn>(OwningActor);

	ACameraActor* SpawnedCamera = Cast<ACameraActor>(
		OwningActor->GetWorld()->SpawnActor<ACameraActor>(
			CameraToSpawnClass,
			SpawnTransform,
			SpawnParams
		)
	);

	if (!SpawnedCamera)
	{
		NotifyStateMap.Remove(MeshComp);
		return;
	}

	if (AttachSocketName != NAME_None)
	{
		SpawnedCamera->AttachToComponent(
			MeshComp,
			AttachRules.ToEngineRules(),
			AttachSocketName
		);
	}

	State.SpawnedCamera = SpawnedCamera;
	PC->SetViewTargetWithBlend(SpawnedCamera, BlendInTime, BlendInFunction);
}

void UANS_SpawnAndSwitchPlayerCamera::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (!MeshComp)
	{
		return;
	}

	AActor* OwningActor = MeshComp->GetOwner();
	if (!OwningActor)
	{
		NotifyStateMap.Remove(MeshComp);
		return;
	}

    APlayerController* PC = Cast<APlayerController>(OwningActor->GetInstigatorController());
    if (!PC)
    {
        PC = UGameplayStatics::GetPlayerController(OwningActor->GetWorld(), PlayerControllerIndex);
    }
    if (!PC)
    {
        return;
    }

	if (FNotifyState* State = NotifyStateMap.Find(MeshComp))
	{
		if (State->PreviousViewTarget.IsValid())
		{
			PC->SetViewTargetWithBlend(State->PreviousViewTarget.Get(), BlendOutTime, BlendOutFunction);
		}

		if (State->SpawnedCamera.IsValid())
		{
			State->SpawnedCamera->SetLifeSpan(LifeSpanAfterEnd);
		}
	}

	NotifyStateMap.Remove(MeshComp);
}
