// ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⣛⡉⢹⢛⣛⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⣫⡆⠀⣿⣷⣬⣼⡿⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡘⢿⣾⡿⠿⠿⠛⢃⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣌⠫⠶⠿⠟⣋⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡏⠉⠏⠩⣭⣭⠉⠘⠉⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠠⠤⠴⢯⣭⢤⠤⢄⢰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠋⠀⠀⠶⠬⢼⣸⣇⢠⠬⠼⠌⠀⠀⢹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡆⠀⠀⠀⠀⠙⠙⠛⠉⠀⠀⠀⠀⠠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠏⠀⢀⣮⣅⣛⠻⠇⠿⢛⣃⣩⣴⠃⠀⠈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⡀⠀⠘⢿⣿⠿⠟⠻⠟⣛⠻⢿⠿⠀⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢀⠀⠀⠲⠈⣭⣭⢩⣭⡴⠐⠀⠀⡌⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇⣾⣷⣦⣀⠀⠀⠈⠀⠀⠀⣠⣴⣿⣿⡸⣿⣿⣿⣿⣿⣿⣿⣿⣿⡏⣼⣿⣿⣿⣿⣿⣶⣤⣀⣴⣿⣿⣿⣿⣿⣧⢹⣿⣿⣿⣿⣿⣿⣿⣿⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿ heheheha

#pragma once

#include "CoreMinimal.h"

/**
 *  This class contains a few Enumerations.
 */

/* The three Aim Modes from, respectively: the present, the past and the "never happened before". */
UENUM(BlueprintType)
enum class EAimModes : uint8
{
	Fixed,		// Classic FPS mode.
	Movable,	// Similar to aiming in Metroid Prime 3/Trilogy, but you move the crosshair with your mouse.
	Gyro		// Uses the Joy-Cons as motion controllers to manually rotate the GameplayGun (and the CutsceneGun).
};

/** All weapon types are here. Want to add the Banana Beam? Go on, this totally isn't a remake. */
UENUM(BlueprintType)
enum class EBeamTypes : uint8
{
	EnergyBeam = 0,
	Battlehammer = 1,
	Judicator = 2,
	VoltDriver = 3,
	Imperialist = 4,
	Magmaul = 5,
	ShockCoil = 6,
	OmegaBeam = 7,
	Missile = 255
};

/** Types of homing traces, for homing projectiles. */
UENUM(BlueprintType)
enum class EHomingTraces : uint8
{
	PlayerTrace, // Homing to players: VoltDriver.
	ObjectTrace, // Homing to special objects (door, switches): EnergyBeam.
	PlayerObjectTrace // Homing to BOTH players and special objects, with priority to nearest: Missile.
};