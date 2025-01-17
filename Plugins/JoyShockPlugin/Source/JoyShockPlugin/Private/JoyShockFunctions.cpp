// heheheha


#include "JoyShockFunctions.h"
#include "JoyShockPlugin.h"

int UJoyShockFunctions::NumberOfDevices = 0;
TMap<int, E_JSP_ControllerType> UJoyShockFunctions::ControllerMap = {};

void UJoyShockFunctions::JSP_ConnectAll(TArray<int>& Handles)
{
	NumberOfDevices = JslConnectDevices(); // Inizio a connettere tutti i dispositivi trovati.
	JslGetConnectedDeviceHandles(Devices, NumberOfDevices);
	int k = 0;
	for (int i : Devices) // Per ogni handle contenuto in Devices...
	{
		UE_LOG(JoyShockPlugin, Display, TEXT("Dispositivo %d: %s"), k, (i<0) ? TEXT("INVALIDO") : *FString::FromInt(i)); // 1. stampa un piccolo messaggino di debug
		
		if (i>=0) // 2. se e' valido (ovvero maggiore o uguale a 0...)
		{
			E_JSP_ControllerType e = static_cast<E_JSP_ControllerType>(JslGetControllerSplitType(i)); // Ottengo il tipo di controller, convertendo da int a enum con static_cast
			// Ricorda, JslGetControllerSplitType fornisce: 1 -> LeftController;  2 -> RightController; 3 -> FullController.
			
			ControllerMap.Add(i, e); // Poi combino nella mappa l'handle (i) e il tipo del controller (e).

			Handles.Add(i); // Dato che l'handle è valido, lo passo in Blueprint in un container TArray<int>.
		}
		k++;
	}
}

void UJoyShockFunctions::JSP_DisconnectAll()
{
	JslDisconnectAndDisposeAll(); // Chiamo la funzione per disconnettere tutti i controller.
	ControllerMap.Empty(); // Svuoto la mappa dei controller.
}

int UJoyShockFunctions::JSP_GetMaxDevices()
{
	return sizeof(Devices); // La grandezza dell'array temporaneo equivale al numero massimo di dispositivi gestibili.
}

int UJoyShockFunctions::JSP_GetConnectedDevices(TMap<int, TEnumAsByte<E_JSP_ControllerType>> & Map)
{
	// Per esporre E_JSP_ControllerType a Blueprint, bisogna convertirla a int8 tramite TEnumAsByte e static_cast.
	// Ricorda: Blueprint non gestisce nativamente le Enum, piuttosto le interpreta come interi a 8 bit (byte) "decorati" con l'enumerazione.
	for (TTuple<int, E_JSP_ControllerType> T : ControllerMap)
	{
		Map.Add(T.Key, static_cast<TEnumAsByte<E_JSP_ControllerType>>(T.Value)); // Handle e tipologia dei dispositivi connessi.
		// L'output sarà, VISIVAMENTE, una TMap<int, E_JSP_ControllerType>, ma al suo interno c'è <int, byte>.
	}
	return NumberOfDevices; // Numero di dispositivi connessi in questo momento.
}

float UJoyShockFunctions::JSP_GetDeltaTime(int deviceID)
{
	return JslGetTimeSinceLastUpdate(deviceID);
}

/* Funzioni di calibrazione */

void UJoyShockFunctions::JSP_SetAutoCalibrationEnabled(int deviceID, bool enabled)
{
	JslSetAutomaticCalibration(deviceID, enabled);
}

void UJoyShockFunctions::JSP_GetAutoCalibrationState(int deviceID, bool & enabled, bool & isSteady, int & confidence)
{
	JSL_AUTO_CALIBRATION c = JslGetAutoCalibrationStatus(deviceID);
	enabled = c.autoCalibrationEnabled;
	isSteady = c.isSteady;
	confidence = c.confidence;
}

void UJoyShockFunctions::JSP_SetContinuousCalibration(int deviceID, E_JSP_ContCalibrationFunction e)
{
	switch (e)
	{
	case Start: JslStartContinuousCalibration(deviceID); break;
	case Stop: JslPauseContinuousCalibration(deviceID); break;
	case Reset: JslResetContinuousCalibration(deviceID); break;
	}
}

FVector UJoyShockFunctions::JSP_GetCalibrationOffset(int deviceID)
{
	FVector v;
	JslGetCalibrationOffset(deviceID, v.X, v.Y, v.Z);
	return v;
}

void UJoyShockFunctions::JSP_SetGyroSpace(int deviceID, E_JSP_GyroSpace e)
{
	JslSetGyroSpace(deviceID, e);
}