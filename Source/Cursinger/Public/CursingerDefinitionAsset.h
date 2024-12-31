// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "CursingerDefinitionAsset.generated.h"

/**
 * 
 */
USTRUCT()
struct FCursingerCursorInfo {

    GENERATED_BODY()

    FCursingerCursorInfo(){
        HotSpot = FVector2D::ZeroVector;
        CursorPath = FName("");
    }

    UPROPERTY(EditAnywhere)
    FName CursorPath;

	UPROPERTY(EditAnywhere)
    FVector2D HotSpot;
};


UCLASS()
class CURSINGER_API UCursingerDefinitionAsset : public UDataAsset
{
	GENERATED_BODY()

	public:
    UPROPERTY(EditAnywhere)
    TMap<FGameplayTag, FCursingerCursorInfo> Cursors;	
};
