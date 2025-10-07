// Copyright (c) 2024 NextGenium

#pragma once

#include "CoreMinimal.h"
#include "Evaluators/UHLAttachmentTargetEvaluator.h"
#include "UHLAttachmentEvaluator_ThisMesh.generated.h"

/**
 * 
 */
UCLASS()
class UNREALHELPERLIBRARY_API UUHLAttachmentEvaluator_ThisMesh : public UUHLAttachmentTargetEvaluator
{
	GENERATED_BODY()
	
	public:
	
	UMeshComponent* GetMeshComponent_Implementation(AActor* OwnerActor) const override;
};
