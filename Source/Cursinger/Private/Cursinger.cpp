// Copyright Epic Games, Inc. All Rights Reserved.

#include "Cursinger.h"

#define LOCTEXT_NAMESPACE "FCursingerModule"

void FCursingerModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FCursingerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCursingerModule, Cursinger)

DEFINE_LOG_CATEGORY(CursingerLog);