// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CursingerFunctionLibrary.generated.h"

/**
 * 
 */
struct FGamePlayTag;
struct FCursorStackHandle;
class UCursingerSubsystem;



UCLASS()
class CURSINGER_API UCursingerFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	public:

	UFUNCTION(BlueprintCallable, Category = "Cursinger")
	static FCursorStackHandle PushCursor(FGameplayTag Tag, UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Cursinger")
	static void PopCursor(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Cursinger")
	static void SwitchCursor(FGameplayTag Tag, FCursorStackHandle Handle, UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Cursinger")
	static void ResetCursor(EMouseCursor::Type Key, UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Cursinger")
	static void RemoveCursor(FCursorStackHandle Handle, UObject* WorldContextObject);
};
