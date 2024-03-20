// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JoyShockTest.h"
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

// Queste variabili sono usate internamente, ma ho deciso anche di esporle esternamente con funzioni const.

/*
Numero massimo di dispositivi accettati dal gioco/editor. Non preoccuparti, ne serviranno massimo 2!
TODO: Considera di inserirlo in un file di configurazione facilmente accessibile dall'editor. Non so come si faccia.

SIMBOLO CONSTEXPR: non è possibile modificarlo a runtime. Permette la costruzione di array a lunghezza fissa!
*/ 
static int constexpr MaxDevices = 2; 

/*
Numero di dispositivi restituito alla connessione JslConnectDevices(). E' inutile definire una funzione che ottenga questo valore:
effettivamente cambia solo alla chiamata di JslConnectDevices(), e si azzera con JslDisconnectAndDisposeAll(). Nel caso in cui serva il valore, è possibile
estrapolarlo da JslConnectDevices() e trattenerlo con una variabile in Blueprint.
*/
static int NumberOfDevices; 

UCLASS()
class JOYSHOCKTEST_API UJoyShockFunctions : public UBlueprintFunctionLibrary
{
	

	GENERATED_BODY()
		
		/* Funzioni di gameplay: queste possono essere chiamate in PIE/gioco. */

		UFUNCTION(BlueprintCallable, CallInEditor, meta=(DisplayName="Connect Joy-Cons", ToolTip="Connette i Joy-Con, restituendo un array di handle (deviceID) e il numero di dispositivi connessi. Puoi anche chiamarla in editor!"))
		static int ConnectAndAssignUpdate(
			TArray<int>& Handles);

	UFUNCTION(BlueprintCallable, meta=(DisplayName="Get IMU State", ToolTip="Ottiene lo stato della IMU (Integrated Movement Unit (i guess) (idk non ricordo?) del Joy-Con col deviceID specificato. @todo: dovresti trasformarla in BlueprintPure per essere più versatile da usare con due Joy-Con"))
		static bool GetIMUValues(
			int deviceID,
			FVector &AccelOutput,
			FVector &GyroOutput
		);

	UFUNCTION(BlueprintCallable, CallInEditor, meta=(DisplayName="Disconnect Joy-Cons", ToolTip="Non voglio più giocare con te! - Daxter Oscuro"))
		static void Disconnect();

	UFUNCTION(BlueprintPure, meta=(CompactNodeTitle="JSL: Max Devices"))
		static int GetMaxDevices();

};
