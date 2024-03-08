// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JoyShockLibrary.h"
#include "JoyShockFunctions.generated.h"
/*
	Questa classe si interfaccia con JoyShockLibrary. Per prima cosa, connetti i controller con ConnectDevices(), anche se viene fatto durante il
	caricamento dei moduli.


*/
// Perché questi valori li devo definire fuori dalla classe? CHE SENSO HA?! SE IO CHIAMO JOYSHOCKFUNCTIONS, VOGLIO LE VARIABILI DI JOYSHOCKFUNCTIONS!
// Ah, il C++. Classico.
// (Penso che sia così perché questa classe viene costruita una volta, dato che è statica...)
// https://stackoverflow.com/questions/12573816/what-is-an-undefined-reference-unresolved-external-symbol-error-and-how-do-i-fix/12574407#12574407

// Queste variabili sono usate solo internamente, per trasferire valori da una funzione all'altra.

static int NumberOfDevices; // Numero di dispositivi restituito alla connessione JslConnectDevices().
static int DevicesArray[]; // Array di interi che contiene gli handle ai dispositivi. La sua lunghezza è definita a runtime.

UCLASS()
class JOYSHOCKTEST_API UJoyShockFunctions : public UBlueprintFunctionLibrary
{
	

	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
		static int ConnectAndAssignUpdate(int &NumberOfDevices);
	UFUNCTION(BlueprintCallable)
		static bool GetIMUValues(
			int deviceID,
			FVector &AccelOutput,
			FVector &GyroOutput
		);
	UFUNCTION(BlueprintCallable)
		static void Disconnect();
};
