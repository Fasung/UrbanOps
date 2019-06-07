// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "FE_UserData.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
#include "FE_UserDataLibrary/ExampleLibrary.h"

#define LOCTEXT_NAMESPACE "FFE_UserDataModule"

/** Handle to the test dll we will load */
static void* ExampleLibraryHandle;

void FFE_UserDataModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// Get the base directory of this plugin
	FString BaseDir = IPluginManager::Get().FindPlugin("FE_UserData")->GetBaseDir();
	// Add on the relative location of the third party dll and load it

#if PLATFORM_WINDOWS
	// Use hardcoded path for faster debuging
	FString LibraryPath = "D:/Git/UrbanOps/Plugins/FE_UserData/Source/ThirdParty/FE_UserDataLibrary/x64/Release/ExampleLibrary.dll";
	//FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/FE_UserDataLibrary/Win64/ExampleLibrary.dll"));
#elif PLATFORM_MAC
    LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/FE_UserDataLibrary/Mac/Release/libExampleLibrary.dylib"));
#endif // PLATFORM_WINDOWS

	ExampleLibraryHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;

	if (!ExampleLibraryHandle)
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Failed to load example third party library"));
	}
}

bool FFE_UserDataModule::IsInitializedTest()
{
	if (ExampleLibraryHandle)
	{
		return IsInitialized();
	}
	else
	{
		return false;
	}
}

FString FFE_UserDataModule::GetLibraryPath()
{
	FString BaseDir = IPluginManager::Get().FindPlugin("FE_UserData")->GetBaseDir();
	// Add on the relative location of the third party dll and load it

	FString LibraryPath = FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/FE_UserDataLibrary/Win64/ExampleLibrary.dll"));

	return LibraryPath;
}

void FFE_UserDataModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	// Free the dll handle
	FPlatformProcess::FreeDllHandle(ExampleLibraryHandle);
	ExampleLibraryHandle = nullptr;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FFE_UserDataModule, FE_UserData)
