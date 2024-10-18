// Fill out your copyright notice in the Description page of Project Settings.


#include "JoyShockFunctions.h"

/* Funzioni di connessione */

int UJoyShockFunctions::JSP_ConnectAll(TArray<int>& Handles)
{
	// Alla connessione, dobbiamo connettere i dispositivi e trovare i loro handle.
	NumberOfDevices = JslConnectDevices();
	int h[MaxDevices];
	JslGetConnectedDeviceHandles(h, NumberOfDevices);

#if JOYSHOCK_DEBUG // Guarda l'header principale: JoyShockTest.h
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

void UJoyShockFunctions::JSP_DisconnectAll()
{
	JslDisconnectAndDisposeAll();
}

/* Funzioni dati */

void UJoyShockFunctions::JSP_GetAllMotionValues(int deviceID, FVector & Acceleration, FRotator & Gyro, FQuat & Quaternion, FVector & Gravity)
{
	// Questa funzione raccoglie tutti i risultati di due funzioni: JslGetIMUState e JslGetMotionState.
	/* JslGetImuState: fornisce valori NON ELABORATI direttamente dalla IMU.
	   
	   - L'accelerazione qui è direttamente estrapolata dall'accelerometro. Non essendo elaborata, contiene però anche gli effetti dell'accelerazione di gravità.
	   
	   - Il giroscopio è sicuramente l'unico valore utile di questa funzione. Dopo una corretta calibrazione, misura in gradi/s la velocità angolare nelle tre
	   dimensioni. Gli assi utilizzati e la valutazione dell'angolo in Eulero dipendono anche dallo spazio utilizzato (JslSetGyroSpace).
	*/

	IMU_STATE i = JslGetIMUState(deviceID);
	Gyro = FRotator(i.gyroY, i.gyroZ, i.gyroX); // Nei FRotator di UE4 non viene seguito l'ordine XYZ, ma... YZX?! Questo è sicuramente dovuto al fatto che
												// ad esempio, per comandare la rotazione pitch (Y) si utilizza un'asse parallela a quella delle X.
	
	/* JslGetMotionState: fornisce valori ELABORATI che potrebbero non provenire direttamente dalla IMU.
	   
	   - Dall'accelerazione rilevata dalla IMU si sottrae l'accelerazione di gravità (9.81m/s2) prendendo in considerazione la normale. In questo modo si ottiene 
	   un metodo affidabile per controllare la velocità e la direzione nello spazio locale del controller, ma *non* il verso, e quindi non la posizione.
	   (come ben ti ha insegnato il professore di fisica in prima, un vettore è composto da modulo, direzione e verso, e senza il verso, non s'ha da fare!)

	   - Il quaternione è calcolato utilizzando la tecnica di fusione sensore (sensor fusion), ma non è pratico da utilizzare come sistema di puntamento.
	   La sua trasformazione in Eulero è buggosa, e ancora non sono riuscito a trovare un metodo per utilizzarla. Inizia a parlare di "parte reale" e "parte
	   immaginaria" di quaternioni e sto già impazzendo!
	   Qui sono tenuto a spiegare solo "cosa sono" i valori, mentre come li userò... sarà per la prossima puntata su UE4 (in inglese "mematico")!

	   - La gravità è estrapolata direttamente dalla IMU, ed è filtrata nell'eventualità del movimento. L'esatto contrario dell'accelerazione.
	   Il suo vettore è normalizzato nel range [-1,1].
	*/

	MOTION_STATE m = JslGetMotionState(deviceID);
	Quaternion.X = m.quatX;
	Quaternion.Y = m.quatY;
	Quaternion.Z = m.quatZ;
	Quaternion.W = m.quatW;
	Acceleration.Set(m.accelX, m.accelY, m.accelZ);
	Gravity.Set(m.gravX, m.gravZ, m.gravY); // Asse Z e Y sono invertite in JSL.
}

void UJoyShockFunctions::JSP_GetAccumulGyro(int deviceID, FRotator &gyro)
{
	JslGetAndFlushAccumulatedGyro(deviceID, gyro.Roll, gyro.Pitch, gyro.Yaw);
}

void UJoyShockFunctions::JSP_GetLeftThumbstick(int deviceID, FVector2D & Thumbstick)
{
	Thumbstick.Set(JslGetLeftX(deviceID), JslGetLeftY(deviceID));
}

void UJoyShockFunctions::JSP_GetRightThumbstick(int deviceID, FVector2D & Thumbstick)
{
	Thumbstick.Set(JslGetRightX(deviceID), JslGetRightY(deviceID));
}

/* Funzioni parametriche */

int UJoyShockFunctions::JSP_GetMaxDevices()
{
	return MaxDevices;
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
