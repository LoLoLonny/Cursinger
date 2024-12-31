// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CursingerDefinitionAsset.h"
#include "Engine/DeveloperSettings.h"
#include "CursingerSettings.generated.h"

/**
 * 
 */
UCLASS(config = CursingerSettings, defaultconfig, meta = (DisplayName="Cursinger Hardware Cursors"))
class CURSINGER_API UCursingerSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
	UCursingerSettings(const FObjectInitializer& obj);

	UPROPERTY(config, EditAnywhere, meta=(AllowedClasses="/Script/Cursinger.CursingerDefinitionAsset"))
	FSoftObjectPath CursingerDefinitionAsset;

	UPROPERTY(config, EditAnywhere)
	FGameplayTag DefaultCursor;

	public:
	UFUNCTION()
	UCursingerDefinitionAsset* GetDefinitionAsset(){ return Cast<UCursingerDefinitionAsset>(CursingerDefinitionAsset.TryLoad()); }

	UFUNCTION()
	FGameplayTag GetDefaultCursor() const { return DefaultCursor; }
};
