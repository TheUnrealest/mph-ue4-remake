// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "JoyShockPlugin.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
#include "JoyShockPluginDevice.h"
#include "JoyShockLibrary.h"

DEFINE_LOG_CATEGORY(JoyShockPlugin);
#define LOCTEXT_NAMESPACE "FJoyShockPluginModule"

TSharedPtr<class IInputDevice> FJoyShockPluginModule::CreateInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler)
{
	UE_LOG(JoyShockPlugin, Display, TEXT("JoyShockPluginDevice created!"));

	// Get the base directory of this plugin
	FString BaseDir = IPluginManager::Get().FindPlugin("JoyShockPlugin")->GetBaseDir();

	// Add on the relative location of the third party dll and load it
	FString LibraryPath;
	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Binaries/JoyShockLibrary.dll"));
	ExampleLibraryHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;

	if (ExampleLibraryHandle)
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("HI", "heheheha👑")); // Mostra solo se debug attivo. Heheheha!
		return MakeShareable(new FJoyShockPluginDevice(InMessageHandler));
	}
	else
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Failed to load example third party library"));
		return nullptr;
	}
}

void FJoyShockPluginModule::ShutdownModule()
{
	UE_LOG(LogTemp, Display, TEXT("JoyShockPluginDevice shutdown!"));

	// Unregister our input device module
	IModularFeatures::Get().UnregisterModularFeature(IInputDeviceModule::GetModularFeatureName(), this);

	FPlatformProcess::FreeDllHandle(ExampleLibraryHandle);
	ExampleLibraryHandle = nullptr;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FJoyShockPluginModule, JoyShockPlugin)