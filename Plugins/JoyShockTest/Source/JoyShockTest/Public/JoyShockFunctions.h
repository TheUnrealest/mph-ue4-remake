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
	Le variabili, seppur statiche, vanno definite fuori dalla definizione della classe {UCLASS...}.
	
	Perché? La risposta la trovi qui:
	https://stackoverflow.com/questions/12573816/what-is-an-undefined-reference-unresolved-external-symbol-error-and-how-do-i-fix/12574407#12574407

*/

/*
Numero massimo di dispositivi accettati dal gioco/editor. Non preoccuparti, ne serviranno massimo 2!
TODO: Considera di inserirlo in un file di configurazione facilmente accessibile dall'editor. Non so come si faccia.

SIMBOLO CONSTEXPR: non è possibile modificarlo a runtime. Permette la costruzione di array a lunghezza fissa!
*/ 
static int constexpr MaxDevices = 2; 

static FQuat q;

/*
Numero di dispositivi restituito alla connessione JslConnectDevices(). E' inutile definire una funzione che ottenga questo valore:
effettivamente cambia solo alla chiamata di JslConnectDevices(), e si azzera con JslDisconnectAndDisposeAll(). Nel caso in cui serva il valore, è possibile
estrapolarlo da JslConnectDevices() e trattenerlo con una variabile in Blueprint.
*/
static int NumberOfDevices;

/*
Questa enum crea un metodo più "bellino" per poter selezionare la funzione della calibrazione continua (Continuous Calibration).
*/
UENUM(BlueprintType)
enum E_JSP_ContCalibrationFunction
{
	// Raccogli i dati e usali immediatamente per la calibrazione.
	Start,
	// Smetti di raccogliere dati, ma non cancellarli. Continua ad usarli per la calibrazione.
	Stop,
	// Resetta la calibrazione e cancella i dati. Da usare in congiunzione, prima di Start, volendo.
	Reset
};

/*
Questa enum crea un metodo migliore per poter selezionare lo spazio del giroscopio (JSP_SetGyroSpace).
*/
UENUM(BlueprintType)
enum E_JSP_GyroSpace
{
	// L'alternativa intramontabile dello spazio locale. L'asse Z varia in base all'inclinazione dell'asse Y, per questa ragione.
	Local,
	// Utilizza la gravita' per fissare l'asse Z con lo sguardo del giocatore.
	World,
	// L'innovazione marchiata JibbSmart, utilizza la gravita' in modo adattivo e allinea l'asse Z perpendicolarmente all'asse Y.
	Player
};

UCLASS()
class JOYSHOCKTEST_API UJoyShockFunctions : public UBlueprintFunctionLibrary
{
	

	GENERATED_BODY()
		
		/* Funzioni di connessione */

	UFUNCTION(BlueprintCallable, CallInEditor, meta=(DisplayName="Connect Joy-Cons", ToolTip="Connette i Joy-Con, restituendo un array di handle (deviceID) e il numero di dispositivi connessi. Puoi anche chiamarla in editor!"))
		static int JSP_ConnectAll(
			TArray<int>& Handles);

	UFUNCTION(BlueprintCallable, CallInEditor, meta=(DisplayName="Disconnect Joy-Cons", ToolTip="Non voglio piu' giocare con te! - Daxter Oscuro"))
		static void JSP_DisconnectAll();

		/* Funzioni di gameplay */

	UFUNCTION(BlueprintPure, meta=(DisplayName="Get Motion State", ToolTip="Ottiene lo stato di accelerometri, giroscopi e del quaternione calcolato da Jsl."))
		static void JSP_GetAllMotionValues(
			int deviceID,
			FVector &Acceleration,
			FRotator &Gyro,
			FQuat & Quaternion,
			FVector & Gravity
		);

	UFUNCTION(BlueprintCallable, meta=(DisplayName="Get Accumulated Gyro",ToolTip="Ottiene lo stato dei giroscopi, ma tenendo in acconto il passare del tempo Dt. Controproducente con UE4, dato che in ogni caso e' necessario moltiplicare per Delta Seconds, e calcolare una media ogni frame e'... dispendioso."))
		static void JSP_GetAccumulGyro(
			int deviceID,
			FRotator & gyro
		);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Left Thumbstick", ToolTip = "Ottiene i dati del joystick analogico sinistro."))
		static void JSP_GetLeftThumbstick(
			int deviceID,
			FVector2D & Thumbstick
		);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Right Thumbstick", ToolTip = "Ottiene i dati del joystick analogico destro."))
		static void JSP_GetRightThumbstick(
			int deviceID,
			FVector2D & Thumbstick
		);

	/* Funzioni parametriche: forniscono un solo parametro statico. */

	UFUNCTION(BlueprintPure, meta=(CompactNodeTitle="JSP: Max Devices"))
		static int JSP_GetMaxDevices();

	/* Funzioni di calibrazione */
	// Auto
	UFUNCTION(BlueprintCallable, meta=(DisplayName="Set Auto Calibration Enabled",ToolTip="Attiva/disattiva auto calibrazione per il Joy-Con con il deviceID fornito."))
		static void JSP_SetAutoCalibrationEnabled(
			int deviceID,
			bool enabled
		);
	
	UFUNCTION(BlueprintCallable, meta=(DisplayName="Get Auto Calibration State",ToolTip="Legge da Jsl lo stato di auto calibrazione per il Joy-Con con il deviceID fornito. Non so ancora cosa sia il valore confidence."))
		static void JSP_GetAutoCalibrationState(
			int deviceID,
			bool & enabled,
			bool & isSteady,
			int & confidence
		);

	// Manuale
	UFUNCTION(BlueprintCallable, meta=(DisplayName="Set Continuous Calibration State",ToolTip="Imposta lo stato della calibrazione continua (Continuous Calibration)."))
		static void JSP_SetContinuousCalibration(
			int deviceID,
			E_JSP_ContCalibrationFunction e
		);

	UFUNCTION(BlueprintCallable, meta=(DisplayName="Get Calibration Offset", ToolTip="Ottiene l'offset calcolato alla calibrazione."))
		static FVector JSP_GetCalibrationOffset(
			int deviceID
		);

	// Spazio gyro
	UFUNCTION(BlueprintCallable, meta=(DisplayName="Set Gyro Space", ToolTip="Imposta il sistema di riferimento del giroscopio."))
		static void JSP_SetGyroSpace(
			int deviceID,
			E_JSP_GyroSpace e
		);

};
