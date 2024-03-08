// Fill out your copyright notice in the Description page of Project Settings.


#include "JoyShockFunctions.h"

int UJoyShockFunctions::ConnectAndAssignUpdate(int & NumberOfDevices)
{
	// Alla connessione, dobbiamo connettere i dispositivi e trovare i loro handle.
	NumberOfDevices = JslConnectDevices();
	JslGetConnectedDeviceHandles(DevicesArray, NumberOfDevices);
	// DEBUG: scriviamo su console il numero dei dispositivi...
	UE_LOG(LogTemp, Display, TEXT("Numero dispositivi: %d"), NumberOfDevices);
	// DEBUG: ... e i loro rispettivi handle.
	UE_LOG(LogTemp, Display, TEXT("Handle dei dispositivi: %d", DevicesArray));
	// Restituisco i numeri dei dispositivi.
	return NumberOfDevices;
}

bool UJoyShockFunctions::GetIMUValues(int deviceID, FVector & AccelOutput, FVector & GyroOutput)
{
	
}

void UJoyShockFunctions::Disconnect()
{
	JslDisconnectAndDisposeAll();
	
}
