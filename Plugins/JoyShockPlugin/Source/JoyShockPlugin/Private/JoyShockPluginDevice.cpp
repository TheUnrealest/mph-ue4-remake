#include "JoyShockPluginDevice.h"
#include "JoyShockPlugin.h"
#include "JoyShockLibrary.h"
#include "Runtime/InputCore/Classes/InputCoreTypes.h"
#include "core.h"

const FKey TestKey("TestKey");
const FKey TestAxis("TestAXIS");

FJoyShockPluginDevice::FJoyShockPluginDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler)
	:MessageHandler(InMessageHandler)
{
	EKeys::AddKey(FKeyDetails(TestKey, FText::FromString("TestKey"), FKeyDetails::GamepadKey));
	EKeys::AddKey(FKeyDetails(TestAxis, FText::FromString("TestAXIS"), FKeyDetails::FloatAxis));
} 

FJoyShockPluginDevice::~FJoyShockPluginDevice()
{
}

void FJoyShockPluginDevice::Tick(float DeltaTime)
{
}

void FJoyShockPluginDevice::SendControllerEvents()
{
	//在此触发输入和输出事件
	MessageHandler->OnControllerAnalog(TestAxis.GetFName(), 0, FMath::FRandRange(0, 1));
	
	// if ()
	// {
	// 	MessageHandler->OnControllerButtonPressed(TestKey.GetFName(), 0, false);
	// }
	// else
	// {
	// 	MessageHandler->OnControllerButtonReleased(TestKey.GetFName(), 0, false);
	// }
}

void FJoyShockPluginDevice::SetMessageHandler(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler)
{
	MessageHandler = InMessageHandler;
}

bool FJoyShockPluginDevice::Exec(UWorld * InWorld, const TCHAR * Cmd, FOutputDevice & Ar)
{
	return false;
}

void FJoyShockPluginDevice::SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value)
{
}

void FJoyShockPluginDevice::SetChannelValues(int32 ControllerId, const FForceFeedbackValues & values)
{
}
