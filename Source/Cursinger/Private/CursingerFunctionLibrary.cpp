// Fill out your copyright notice in the Description page of Project Settings.


#include "CursingerFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "CursingerSubsystem.h"


FCursorStackHandle UCursingerFunctionLibrary::PushCursor(FGameplayTag Tag, UObject* WorldContextObject)
{
    UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);
    if(!World)
        return FCursorStackHandle::Invalid;

    if (UCursingerSubsystem* CursingerSubSystem = World->GetSubsystem<UCursingerSubsystem>())
    {
        return CursingerSubSystem->PushCursor(Tag);
    }
    else
    {
        UE_LOG(CursingerLog, Error, TEXT("Push Failed, CursingerSubsystem not found"));
        
        return FCursorStackHandle::Invalid;
    }
}

void UCursingerFunctionLibrary::PopCursor(UObject* WorldContextObject)
{
    UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);
    if(!World)
        return;

    if (UCursingerSubsystem* CursingerSubSystem = World->GetSubsystem<UCursingerSubsystem>())
    {
        CursingerSubSystem->PopCursor();
    }
}

void UCursingerFunctionLibrary::SwitchCursor(FGameplayTag Tag, FCursorStackHandle Handle, UObject* WorldContextObject)
{
    UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);
    if(!World)
        return;

    if (UCursingerSubsystem* CursingerSubSystem = World->GetSubsystem<UCursingerSubsystem>())
    {
        CursingerSubSystem->SwitchCursor(Tag, Handle);
    }
}

void UCursingerFunctionLibrary::ResetCursor(EMouseCursor::Type Key, UObject* WorldContextObject)
{
    UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);
    if(!World)
        return;

    if (UCursingerSubsystem* CursingerSubSystem = World->GetSubsystem<UCursingerSubsystem>())
    {
        CursingerSubSystem->ResetCursor(Key);
    }
}


void UCursingerFunctionLibrary::RemoveCursor(FCursorStackHandle Handle, UObject* WorldContextObject)
{
    UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);
    if (!World)
        return;

    if (UCursingerSubsystem* CursingerSubSystem = World->GetSubsystem<UCursingerSubsystem>())
    {
        CursingerSubSystem->RemoveCursor(Handle);
    }
}
