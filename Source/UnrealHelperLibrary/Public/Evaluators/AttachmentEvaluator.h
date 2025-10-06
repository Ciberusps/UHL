// Copyright (c) 2024 NextGenium

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AttachmentEvaluator.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class UNREALHELPERLIBRARY_API UAttachmentEvaluator : public UObject
{
	GENERATED_BODY()

	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SourceName;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	AActor* GetActorWithChild(AActor* OwnerActor) const;
};
