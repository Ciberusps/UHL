// Copyright (c) 2024 NextGenium

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UHLAttachmentTargetEvaluator.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class UNREALHELPERLIBRARY_API UUHLAttachmentTargetEvaluator : public UObject
{
	GENERATED_BODY()

	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SourceName;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UMeshComponent* GetMeshComponent(AActor* OwnerActor) const;
};
