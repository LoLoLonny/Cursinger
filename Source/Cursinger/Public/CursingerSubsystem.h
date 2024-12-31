// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "CursingerDefinitionAsset.h"
#include "CursingerSubsystem.generated.h"

/**
 * 
 */


 /**
  * Handle to a registered smartobject.
  */
USTRUCT(BlueprintType)
struct CURSINGER_API FCursorStackHandle
{
	GENERATED_BODY()

public:

	FCursorStackHandle() {}

	bool IsValid() const { return *this != Invalid; }
	void Invalidate() { *this = Invalid; }

	friend FString LexToString(const FCursorStackHandle Handle)
	{
		return FString::Printf(TEXT("CursorHandle-%i"), Handle.ID);
	}

	bool operator==(const FCursorStackHandle Other) const { return ID == Other.ID; }
	bool operator!=(const FCursorStackHandle Other) const { return !(*this == Other); }

	friend uint32 GetTypeHash(const FCursorStackHandle Handle)
	{
		return CityHash32(reinterpret_cast<const char*>(&Handle.ID), sizeof Handle.ID);
	}

private:

	friend UCursingerSubsystem;

	explicit FCursorStackHandle(const uint64 InID) : ID(InID) {}

	UPROPERTY(VisibleAnywhere, Category = "Cursinger")
	uint64 ID = InvalidID;

	/**
	 * All Ids with this bit set were assigned for dynamic ('D') entries that rely on the component lifetime.
	 * Otherwise their Ids are from persistent collections ('P').
	 */
	static constexpr uint64 DynamicIdsBitMask = 1ULL << 63;
	static constexpr uint64 InvalidID = 0;

public:
	static const FCursorStackHandle Invalid;
};

UCLASS()
class CURSINGER_API UCursingerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void OnWorldBeginPlay(UWorld& World) override;

	UPROPERTY()
	UGameViewportClient* ViewportClient;

	UPROPERTY()
	UCursingerDefinitionAsset* CursingerDefinitionAsset;

	UPROPERTY()
	FGameplayTag DefaultCursor;

	UPROPERTY()
	APlayerController* PC;

	const TMap<FCursorStackHandle, FGameplayTag>& GetCursorStack(){ return CursorMap; }

	UFUNCTION(BlueprintCallable)
	FCursorStackHandle PushCursor(FGameplayTag Tag);

	UFUNCTION(BlueprintCallable)
	void PopCursor();

	UFUNCTION(BlueprintCallable)
	void SwitchCursor(FGameplayTag Tag, FCursorStackHandle Handle);

	UFUNCTION(BlueprintCallable)
	void ResetCursor(EMouseCursor::Type Key);

	UFUNCTION(BlueprintCallable)
	void RemoveCursor(FCursorStackHandle Handle);

	void SetToTopOfStack();

	private:

	UPROPERTY()
	TMap<FCursorStackHandle, FGameplayTag> CursorMap;

	UPROPERTY()
	TArray<FCursorStackHandle> CursorStack;

	bool IsCursorDefined(FGameplayTag Tag) const;

	void SetCursor(FGameplayTag Tag);

	FCursorStackHandle CreateCursorStackHandle(FGameplayTag Tag);
};
