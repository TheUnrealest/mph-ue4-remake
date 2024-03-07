// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JoyShockLibrary.h"
#include "JoyShockFunctions.generated.h"

/**
 * 
 */
UCLASS()
class JOYSHOCKTEST_API UJoyShockFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable)
		static bool GetImuState(
			FVector& AccelVectorOutput,
			FVector& GyroVectorOutput,
			const int deviceID = 0
		);

	UFUNCTION(BlueprintPure)
		static bool IsStillConnected(
			int deviceID = 0
		);
	UFUNCTION(BlueprintCallable)
		static void ConnectDevices();
	UFUNCTION(BlueprintCallable)
		static void DisconnectDevices();

	static void Update(int number, JOY_SHOCK_STATE S1, JOY_SHOCK_STATE S2, IMU_STATE IMU1, IMU_STATE IMU2, float DeltaTime);
};
