// Pavel Penkov 2025 All Rights Reserved.


#include "Animation/Notifies/AN_DetachActorWithUniqueId.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/ActorComponent.h"
#include "TimerManager.h"
#include "Utils/UnrealHelperLibraryBPL.h"

#if WITH_EDITOR
void UAN_DetachActorWithUniqueId::PostEditChangeProperty(
	struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.Property != nullptr && 
		PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UAN_DetachActorWithUniqueId, UniqueId))
	{
		if (UAnimSequenceBase* AnimSeq = Cast<UAnimSequenceBase>(GetOuter()))
		{
			AnimSeq->Modify();
		}
	}
}
#endif

FString UAN_DetachActorWithUniqueId::GetNotifyName_Implementation() const
{
	return FString("Detach With UniqueId->") + UniqueId.ToString();
}

void UAN_DetachActorWithUniqueId::Notify(
	USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (!MeshComp) return;
	
	AActor* OwnerActor = MeshComp->GetOwner();
	if (!OwnerActor) return;

	AActor* AttachedActor = UUnrealHelperLibraryBPL::FindAttachedActorByTag(OwnerActor, UniqueId);
	if (!AttachedActor) return;

	AttachedActor->DetachFromActor(DetachmentRules.ToEngineRules());
	
	// checking that physics enabled before AutoDestroy and it worth to create timer
	if (bEnablePhysicsOnDetach && (!bAutoDestroy || EnablePhysicsDelay < AutoDestroyDelay))
	{
		const TWeakObjectPtr<AActor> WeakActor = AttachedActor;
		const bool bApplyProfile = bOverrideCollisionProfile;
		const FName ProfileName = CollisionProfileOnDetach.Name;
		const bool bApplyImpulse = bAddImpulseOnDetach;
		const FVector LocalImpulse = DetachImpulse;
		const bool bVelChange = bImpulseAsVelocityChange;

		auto EnablePhysics = [WeakActor, bApplyProfile, ProfileName, bApplyImpulse, LocalImpulse, bVelChange]()
		{
			AActor* Actor = WeakActor.Get();
			if (!IsValid(Actor)) return;

			TArray<UActorComponent*> Comps = Actor->K2_GetComponentsByClass(UPrimitiveComponent::StaticClass());
			for (UActorComponent* Comp : Comps)
			{
				UPrimitiveComponent* Prim = Cast<UPrimitiveComponent>(Comp);
				if (!Prim) continue;

				// the profile alone drives CollisionEnabled - forcing QueryAndPhysics here would flip the
				// component to "Custom" and resurrect collision even on a NoCollision profile
				if (bApplyProfile)
				{
					Prim->SetCollisionProfileName(ProfileName);
				}

				Prim->SetSimulatePhysics(true);

				if (bApplyImpulse && !LocalImpulse.IsNearlyZero())
				{
					Prim->AddImpulse(Actor->GetActorRotation().RotateVector(LocalImpulse), NAME_None, bVelChange);
				}
			}
		};

		if (EnablePhysicsDelay <= 0.0f)
		{
			EnablePhysics();
		}
		else
		{
			FTimerHandle LocalTimerHandle;
			MeshComp->GetWorld()->GetTimerManager().SetTimer(
				LocalTimerHandle, FTimerDelegate::CreateLambda(EnablePhysics), EnablePhysicsDelay, false);
		}
	}
	
	if (bAutoDestroy)
	{
		AttachedActor->SetLifeSpan(AutoDestroyDelay);
	}
}