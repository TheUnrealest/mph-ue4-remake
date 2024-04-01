// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "JoyShockTest.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
#include "JoyShockLibrary.h"

DEFINE_LOG_CATEGORY(JoyShockPlugin);
#define LOCTEXT_NAMESPACE "FJoyShockTestModule"


void FJoyShockTestModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// Get the base directory of this plugin
	FString BaseDir = IPluginManager::Get().FindPlugin("JoyShockTest")->GetBaseDir();

	// Add on the relative location of the third party dll and load it
	FString LibraryPath;
#if PLATFORM_WINDOWS
	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/JoyShockLibrary.dll"));
#endif // PLATFORM_WINDOWS

	ExampleLibraryHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;

	if (ExampleLibraryHandle)
	{
#if JOYSHOCK_DEBUG
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("HI", "heheheha")); // Mostra solo se debug attivo. Heheheha!
#endif
		
#if JOYSHOCK_STARTUPCONNECT // Vogliamo anche connettere i Joy-Con all'avvio dell'editor?
		int x = JslConnectDevices();
		if (x == 0)
		{
			UE_LOG(JoyShockPlugin, Warning, TEXT("Nessun controller rilevato. Prova a ricontrollare le impostazioni Bluetooth o il codice buggosissimo di questo plugin."));
		}
		else
		{
			UE_LOG(JoyShockPlugin, Display, TEXT("Numero controller: %d"), x);
		}
#endif
		
	}
	else
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Failed to load example third party library"));
	}
}

void FJoyShockTestModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	// Free the dll handle
	FPlatformProcess::FreeDllHandle(ExampleLibraryHandle);
	ExampleLibraryHandle = nullptr;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FJoyShockTestModule, JoyShockTest)
