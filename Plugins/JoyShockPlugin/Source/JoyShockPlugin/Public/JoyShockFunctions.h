#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JoyShockLibrary.h"
#include "JoyShockFunctions.generated.h"

/**
 * Questa classe espone a Blueprint tutte le funzioni per GESTIRE i controller.
 * L'input, invece, è gestito dall'interfaccia di Unreal.
 * Qualsiasi valore chiamato prima di JSP_ConnectAll è invalido. Potrei trovare un modo per restituire un valore arbitrario (tipo -2) se non è stata eseguita
 * l'inizializzazione.
 */

static int constexpr MaxDevices = 2; // quanti byte da allocare per Devices = quanti dispositivi colleghiamo al massimo. PUO' CAUSARE OUT OF BOUNDS.
static int i; // variabile di aiuto per riempire il TArray degli handle. resettata a 0 ogni volta che riconnetto.
static int NumberOfDevices; // numero di dispositivi connessi al momento.
static int Devices[MaxDevices]; // array per la traduzione a TArray.


UCLASS()
class JOYSHOCKPLUGIN_API UJoyShockFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

		UFUNCTION(BlueprintCallable)
		static void JSP_ConnectAll(
			TArray<int> & Handles);

		UFUNCTION(BlueprintCallable)
		static void JSP_DisconnectAll();
};
