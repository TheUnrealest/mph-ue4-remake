#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JoyShockLibrary.h"
#include "JoyShockFunctions.generated.h"

/**
 * Questa classe espone a Blueprint tutte le funzioni per GESTIRE i controller: connessione, identificazione, calibrazione, disconnessione.
 * L'input, invece, è gestito dall'interfaccia di Unreal in base all'indice in Devices (sì, è più efficiente).
 * Qualsiasi valore chiamato prima di JSP_ConnectAll è invalido. Potrei trovare un modo per restituire un valore arbitrario (tipo -2) se non è stata eseguita
 * l'inizializzazione.
 * 
 * Al momento, questo sistema è ottimizzato solamente solo per Joy-Con. Ma con un po' di lavoro, anche Dualshock e Dualsense funzioneranno a meraviglia!
 */

/*
Array int degli handle che viene restituito a JslGetConnectedDeviceHandles(). Ok, qui la cosa si fa complicata quindi ascoltami. Non possiamo sapere con certezza quanti controller
saranno collegati a runtime: effettivamente ne basterebbero solo due nel caso di Joy-Con, o uno nel caso di Dualshock/Dualsense. Però qualche matto furioso potrebbe collegarne tre,
quattro, cinque, otto (se ha le schede Bluetooth adatte!).
Fatto sta che quindi vorremmo un array di interi a lunghezza variabile, giusto? C++ dice NO: l'allocazione deve essere determinata dal compilatore. Quindi potrei pensare di
utilizzare TArray, che sfrutta un allocatore dinamico della memoria (unica cosa gratificante di Unreal Engine). Ma JslConnectDevices() non ha idea di cosa sia un TArray.

Per questa ragione devo creare un vettore "di traduzione" (questo qua sotto), che raccolga gli handle da JslConnectDevices, e li utilizzi gradualmente per allocare un TArray.
Esso ha una lunghezza fissa che determina il numero massimo di dispositivi collegabili senza causare un out of bounds.
Come faccio a determinare se allocare i valori? Se JslConnectDevices() sovrascrive solo due degli otto valori, come lo posso sapere? Semplice: grazie a NumberOfDevices.
*/
static int Devices[8] = {-1,-1,-1,-1,-1,-1,-1,-1}; // -1 è un valore per indicare un handle INVALIDO. Pare che Jsl non inserira' mai handle negativi.

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

/*
Questa enum determina di che tipo è il controller: JC destro, JC sinistro oppure completo (Pro Controller, Dualshock/Dualsense...)
SPERIMENTALE: Associa un numero al byte corrispondente.
*/
UENUM(BlueprintType)
enum E_JSP_ControllerType
{
	LeftController = 1,
	RightController = 2,
	FullController = 3
};




UCLASS()
class JOYSHOCKPLUGIN_API UJoyShockFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	// Mappa che correla l'handle di un controller con la sua tipologia. Verrà usato per capire quali tipologie di eventi inviare in gioco.
	static TMap<int, E_JSP_ControllerType> ControllerMap;

	/*
	Numero di dispositivi restituito alla connessione JslConnectDevices(). E' inutile definire una funzione che ottenga questo valore:
	effettivamente cambia solo alla chiamata di JslConnectDevices(), e si azzera con JslDisconnectAndDisposeAll(). Nel caso in cui serva il valore, e' possibile
	estrapolarlo da JslConnectDevices() e trattenerlo con una variabile in Blueprint.
	Ma nel caso serva ad una classe che NON chiama JslConnectDevices(), per evitare l'overhead del casting e' meglio allocare qualche byte di RAM in piu' con una funzione parametrica.
	*/
	static int NumberOfDevices;


		UFUNCTION(BlueprintCallable)
			static void JSP_ConnectAll(
				TArray<int> & Handles);

		UFUNCTION(BlueprintCallable)
			static void JSP_DisconnectAll();


		/* Funzioni parametriche: forniscono un solo parametro statico. */

		UFUNCTION(BlueprintPure, meta = (CompactNodeTitle = "JSP: Max Devices"))
			static int JSP_GetMaxDevices();

		UFUNCTION(BlueprintPure, meta = (CompactNodeTitle = "JSP: Devices Connected"))
			static int JSP_GetConnectedDevices(
				TMap<int, TEnumAsByte<E_JSP_ControllerType>> & Map);

		UFUNCTION(BlueprintPure, meta = (CompactNodeTitle = "JSP: Delta Time"))
			static float JSP_GetDeltaTime(
			int deviceID);

		/* Funzioni di calibrazione */
		// Auto
		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Auto Calibration Enabled", ToolTip = "Attiva/disattiva auto calibrazione per il Joy-Con con il deviceID fornito."))
			static void JSP_SetAutoCalibrationEnabled(
				int deviceID,
				bool enabled
			);

		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Auto Calibration State", ToolTip = "Legge da Jsl lo stato di auto calibrazione per il Joy-Con con il deviceID fornito. Non so ancora cosa sia il valore confidence."))
			static void JSP_GetAutoCalibrationState(
				int deviceID,
				bool & enabled,
				bool & isSteady,
				int & confidence
			);

		// Manuale
		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Continuous Calibration State", ToolTip = "Imposta lo stato della calibrazione continua (Continuous Calibration)."))
			static void JSP_SetContinuousCalibration(
				int deviceID,
				E_JSP_ContCalibrationFunction e
			);

		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Calibration Offset", ToolTip = "Ottiene l'offset calcolato alla calibrazione."))
			static FVector JSP_GetCalibrationOffset(
				int deviceID
			);

		// Spazio gyro
		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Gyro Space", ToolTip = "Imposta il sistema di riferimento del giroscopio."))
			static void JSP_SetGyroSpace(
				int deviceID,
				E_JSP_GyroSpace e
			);


		
};
