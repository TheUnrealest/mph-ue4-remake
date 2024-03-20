// Fill out your copyright notice in the Description page of Project Settings.


#include "JoyShockFunctions.h"


int UJoyShockFunctions::ConnectAndAssignUpdate(TArray<int>& Handles)
{
	// Alla connessione, dobbiamo connettere i dispositivi e trovare i loro handle.
	NumberOfDevices = JslConnectDevices();
	int h[MaxDevices];
	JslGetConnectedDeviceHandles(h, NumberOfDevices);

#if JOYSHOCK_DEBUG // Guarda l'header principale: JoyShockFunctions.h
	// DEBUG: scriviamo su console il numero dei dispositivi...
	UE_LOG(JoyShockPlugin, Display, TEXT("Numero dispositivi (chiamata in PIE/Gioco): %d"), NumberOfDevices);
	// DEBUG: ... e i loro rispettivi handle.
	for (int i = 1; i <= MaxDevices; i++)
	{
		UE_LOG(JoyShockPlugin, Display, TEXT("Handle dispositivo %d: %d"), i, h[i-1]);
	}
#endif

	// Adesso riempo l'array degli output...
	for(int i = 1; i<=NumberOfDevices; i++)
	{
		Handles.Add(h[i-1]);
	}
	// ... e restituisco il numero di dispositivi.
	return NumberOfDevices;

}

bool UJoyShockFunctions::GetIMUValues(int deviceID, FVector & AccelOutput, FVector & GyroOutput)
{
	IMU_STATE i = JslGetIMUState(deviceID);
	AccelOutput.Set(i.accelX, i.accelZ, i.accelY); // Inverto Y e Z, convertendo lo spazio da Jsl a UE4.
	GyroOutput.Set(i.gyroX, i.gyroZ, i.gyroY); // Idem, vedi sopra.
	return true;
}

void UJoyShockFunctions::Disconnect()
{
	JslDisconnectAndDisposeAll();
	
}

int UJoyShockFunctions::GetMaxDevices()
{
	return MaxDevices;
}
