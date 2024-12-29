// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "JoyShockPlugin.h"
#include "JoyShockPluginDevice.h"

#define LOCTEXT_NAMESPACE "FJoyShockPluginModule"

TSharedPtr<class IInputDevice> FJoyShockPluginModule::CreateInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler)
{
	UE_LOG(LogTemp, Display, TEXT("JoyShockPluginDevice created!"));
	return MakeShareable(new FJoyShockPluginDevice(InMessageHandler));
}

void FJoyShockPluginModule::ShutdownModule()
{
	UE_LOG(LogTemp, Display, TEXT("JoyShockPluginDevice shutdown!"));

	// Unregister our input device module
	IModularFeatures::Get().UnregisterModularFeature(IInputDeviceModule::GetModularFeatureName(), this);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FJoyShockPluginModule, JoyShockPlugin)