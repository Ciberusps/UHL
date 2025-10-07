// Copyright (c) 2024 NextGenium


#include "Evaluators/UHLAttachmentEvaluator_ThisMesh.h"

UMeshComponent* UUHLAttachmentEvaluator_ThisMesh::GetMeshComponent_Implementation(AActor* OwnerActor) const
{
	if (OwnerActor)
		return Cast<USkeletalMeshComponent>(OwnerActor->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
	else
		return nullptr;
}
