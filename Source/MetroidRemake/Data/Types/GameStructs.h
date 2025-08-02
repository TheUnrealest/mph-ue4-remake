// ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⣛⡉⢹⢛⣛⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⣫⡆⠀⣿⣷⣬⣼⡿⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡘⢿⣾⡿⠿⠿⠛⢃⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣌⠫⠶⠿⠟⣋⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡏⠉⠏⠩⣭⣭⠉⠘⠉⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠠⠤⠴⢯⣭⢤⠤⢄⢰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠋⠀⠀⠶⠬⢼⣸⣇⢠⠬⠼⠌⠀⠀⢹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡆⠀⠀⠀⠀⠙⠙⠛⠉⠀⠀⠀⠀⠠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠏⠀⢀⣮⣅⣛⠻⠇⠿⢛⣃⣩⣴⠃⠀⠈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⡀⠀⠘⢿⣿⠿⠟⠻⠟⣛⠻⢿⠿⠀⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢀⠀⠀⠲⠈⣭⣭⢩⣭⡴⠐⠀⠀⡌⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇⣾⣷⣦⣀⠀⠀⠈⠀⠀⠀⣠⣴⣿⣿⡸⣿⣿⣿⣿⣿⣿⣿⣿⣿⡏⣼⣿⣿⣿⣿⣿⣶⣤⣀⣴⣿⣿⣿⣿⣿⣧⢹⣿⣿⣿⣿⣿⣿⣿⣿⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿ heheheha

#pragma once

#include "CoreMinimal.h"
#include "GameTypes.h"
#include "GameStructs.generated.h"

/**
 *	This class contains important structures used globally.
 */


/** This is needed by ProjectileDataBase to pass projectile values project-wide.
 *	Ue4 documentation says "garbo collection doesn't work with USTRUCTs, git gud". Well, I hope I don't have to create
 *	1450000 variables for this...
 *	Remember, this struct does not have all projectile related values. Most of them are useless outside the class.
 *	
 *	Trajectory and physics related parameters are the most useful ones, for now... *cod black ops ending theme*
 */
USTRUCT(BlueprintType)
struct FProjectileData
{
	GENERATED_BODY()

	// 1: Normal projectile data
	
	/** Velocity of the normal projectile. */
	UPROPERTY(BlueprintReadOnly)
	float ProjectileSpeed = 1000.f;

	/** Collision radius of the normal projectile. */
	UPROPERTY(BlueprintReadOnly)
	float CollisionRadius = 15.f;

	/** Delay between two normal shots of this projectile. */
	UPROPERTY(BlueprintReadOnly)
	float Delay = .05f;

	/** Gravity scale of the projectile (in fractions of WorldGravityZ). */
	UPROPERTY(BlueprintReadOnly)
	float GravityMultiplier = 1.f;

	#pragma region separator1 // Charge
	// BLUEPRINT SEPARATOR - WON'T DO SH*T
	UPROPERTY(BlueprintReadOnly)
	bool _____Charge_Configuration_____;
#pragma endregion separator1

	// 2. Charged projectile data

	/** Velocity of the charged projectile. */
	UPROPERTY(BlueprintReadOnly)
	float ProjectileSpeed_Charged = 850.f;

	/** Collision radius of the charged projectile. */
	UPROPERTY(BlueprintReadOnly)
	float CollisionRadius_Charged = 20.f;

	/** Time in seconds to fully charge the projectile. */
	UPROPERTY(BlueprintReadOnly)
	float FullChargeTimer = 1.5f;

	#pragma region separator2 // Homing
	// ANOTHER BLUEPRINT SEPARATOR - YUPPIEEEEE!!!
	UPROPERTY(BlueprintReadOnly)
	bool _____Homing_Configuration_____;
#pragma endregion separator2

	// 3. Homing capabilities
	
	/** Is this a homing projectile? Only charged projectiles can do homing. */
	UPROPERTY(BlueprintReadOnly)
	bool IsHomingProjectile = false;

	/** Type of homing trace. Lookup E_HomingTraces. */
	UPROPERTY(BlueprintReadWrite)
	EHomingTraces HomingTraceType = EHomingTraces::PlayerTrace;

	/** Radius of the homing trace. Higher radius = more homing effect. */
	UPROPERTY(BlueprintReadOnly)
	float HomingTraceRadius = 250.f;

	/** Length of the homing trace. */
	UPROPERTY(BlueprintReadOnly)
	float HomingTraceLength = 4000.f;

	#pragma region separator3 // Effects
	UPROPERTY(BlueprintReadOnly)
	bool _____Other_Effects_____;
	#pragma endregion separator3

	// 4. Global effects
	
	/** A general color for Beam related objects (doors, shields, etc.).
	 * Implemented using a Multiply node in Materials. */
	UPROPERTY(BlueprintReadOnly)
	FLinearColor BeamGeneralColor = FLinearColor(1.f,1.f,1.f,1.f);

	/** Recolor tint for the Arm Cannon. Given a mask assigned in the MI, replace the color with this based on
	 *	current beam we're using.
	 */
	UPROPERTY(BlueprintReadOnly)
	FLinearColor ArmCannonRecolor_Metal = FLinearColor(.307f,.307f,.307f,1.f);

	/** Color 1 for Arm Cannon energy lines (those shiny things). */
	UPROPERTY(BlueprintReadOnly)
	FLinearColor ArmCannonRecolor_Line1 = FLinearColor(0.f,0.f,0.f,1.f);

	/** Color 2 for Arm Cannon energy lines (those shiny things). */
	UPROPERTY(BlueprintReadOnly)
	FLinearColor ArmCannonRecolor_Line2 = FLinearColor(1.f,1.f,1.f,1.f);
};