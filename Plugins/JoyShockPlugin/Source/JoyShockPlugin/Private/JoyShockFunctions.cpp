// heheheha


#include "JoyShockFunctions.h"

void UJoyShockFunctions::JSP_ConnectAll(TArray<int>& Handles)
{
	Handles.Empty(); // svuota l'array alla riconnessione, evitiamo di avere dispositivi fantasma
	i = 0; // ricominciamo da capo.
	NumberOfDevices = JslConnectDevices();
	JslGetConnectedDeviceHandles(Devices, NumberOfDevices); // per tradurre da std::array a TArray[] ho bisogno di una variabile array temporanea Devices[MaxDevices].
	// std::array a lunghezza variabile non è supportato in C++ vanilla. UE4 ha un'ottima implementazione, però...
	for (i = 0; NumberOfDevices; i++)
	{
		Handles.Add(Devices[i]); // per ogni handle raccolto da Devices, aggiungo una voce in TArray<int> Handles.
	}
	return;
}

void UJoyShockFunctions::JSP_DisconnectAll()
{
	JslDisconnectAndDisposeAll();
}
