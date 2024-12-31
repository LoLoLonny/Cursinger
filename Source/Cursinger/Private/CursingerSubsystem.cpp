// Fill out your copyright notice in the Description page of Project Settings.


#include "CursingerSubsystem.h"
#include "CursingerSettings.h"
#include "Misc/Guid.h"
#include "CursingerDefinitionAsset.h"
#include "Engine/GameViewportClient.h"

const FCursorStackHandle FCursorStackHandle::Invalid;

void UCursingerSubsystem::Initialize(FSubsystemCollectionBase &Collection)
{
    UCursingerSettings* Settings = GetMutableDefault<UCursingerSettings>();
    CursingerDefinitionAsset = Settings->GetDefinitionAsset();
    DefaultCursor = Settings->GetDefaultCursor();
}

void UCursingerSubsystem::OnWorldBeginPlay(UWorld& World)
{
    ViewportClient = World.GetGameViewport();
    PushCursor(DefaultCursor);

    /* This is OK for now cause we use it in a single player game.
    Would be better to create a component to sync controllers and set these settings in editor.*/

	PC = World.GetFirstPlayerController();
    PC->bShowMouseCursor = true;
    PC->bEnableClickEvents = true;
    PC->bEnableMouseOverEvents = true;
    PC->CurrentMouseCursor = EMouseCursor::Default;
}

FCursorStackHandle UCursingerSubsystem::PushCursor(FGameplayTag Tag)
{ 
    if(!IsCursorDefined(Tag))
        return FCursorStackHandle::Invalid;

    FCursorStackHandle Handle = CreateCursorStackHandle(Tag);
    CursorMap.Add(Handle, Tag);
    CursorStack.Add(Handle);

    SetCursor(Tag);
    
    return Handle;
}

void UCursingerSubsystem::PopCursor()
{ 
    if(CursorStack.Num()>1){

        /* Pop the handle stack and remove the cursor from the map */
        FCursorStackHandle Handle = CursorStack.Pop();
        CursorMap.Remove(Handle);

        SetToTopOfStack();
    }
}

void UCursingerSubsystem::SwitchCursor(FGameplayTag Tag, FCursorStackHandle Handle)
{
    if (!Handle.IsValid())
        return;

    CursorMap.Emplace(Handle, Tag);

    SetToTopOfStack();
}

void UCursingerSubsystem::SetCursor(FGameplayTag Tag)
{
    if (!CursingerDefinitionAsset) {
        UE_LOG(CursingerLog, Error, TEXT("Please configure cursinger in the project settings"));
        return;
    }

    if ( ViewportClient )
    {
        FCursingerCursorInfo* CursorInfo = CursingerDefinitionAsset->Cursors.Find(Tag);
        if (CursorInfo) {
            ViewportClient->SetHardwareCursor(EMouseCursor::Default, CursorInfo->CursorPath, CursorInfo->HotSpot);
        }
    }
}

void UCursingerSubsystem::ResetCursor(EMouseCursor::Type Key)
{
    CursorMap.Empty();
    CursorStack.Empty();

    TSharedPtr<ICursor> PlatformCursor = FSlateApplication::Get().GetPlatformCursor();
	if (ICursor* Cursor = PlatformCursor.Get())
	{
		Cursor->SetTypeShape(Key, nullptr);
	}
}

void UCursingerSubsystem::RemoveCursor(FCursorStackHandle Handle)
{

    FGameplayTag* Tag = CursorMap.Find(Handle);
    if (Tag) {
        CursorMap.Remove(Handle);
        CursorStack.Remove(Handle);
    }

    SetToTopOfStack();
}

void UCursingerSubsystem::SetToTopOfStack()
{
    if (CursorStack.Num() > 0) {
        FGameplayTag CursorTag = CursorMap.FindRef(CursorStack.Top());
        SetCursor(CursorTag);
    }
    else {
        PushCursor(DefaultCursor);
    }
}

bool UCursingerSubsystem::IsCursorDefined(FGameplayTag Tag) const
{
    if (!CursingerDefinitionAsset)
        return false;

    if (!CursingerDefinitionAsset->Cursors.Contains(Tag)) {
        return false;
    }      

    return true;
}

FCursorStackHandle UCursingerSubsystem::CreateCursorStackHandle(FGameplayTag Tag)
{

    FCursorStackHandle Handle = FCursorStackHandle();

    /* Every handle needs to be unique. This is ensured by a unique ID.*/
    static std::atomic<uint64> NextId = 0;
    uint64 ID = HashCombine(GetTypeHash(Tag), ++NextId);
    Handle.ID = ID;

    return Handle;
}