// Fill out your copyright notice in the Description page of Project Settings.


#include "JoyShockFunctions.h"
#include "JoyShockLibrary.h"


bool UJoyShockFunctions::GetImuState(FVector& AccelVector, FVector& GyroVector, const int deviceID)
{
	IMU_STATE Test = JslGetIMUState(deviceID);
	AccelVector.Set(Test.accelX, Test.accelY, Test.accelZ);
	GyroVector.Set(Test.gyroX, Test.gyroY, Test.gyroZ);
	return true;
}

bool UJoyShockFunctions::IsStillConnected(int deviceID)
{
	return JslStillConnected(deviceID);
}

void UJoyShockFunctions::Update(int number, JOY_SHOCK_STATE S1, JOY_SHOCK_STATE S2, IMU_STATE IMU1, IMU_STATE IMU2, float DeltaTime)
{
}


void UJoyShockFunctions::ConnectDevices()
{
	int x = JslConnectDevices();
	UE_LOG(LogTemp, Display, TEXT("Numero controller: %d"), x);
	JslSetCallback(&Update);
}

void UJoyShockFunctions::DisconnectDevices()
{
	JslDisconnectAndDisposeAll();
}

