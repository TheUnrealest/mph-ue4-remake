/*
 *	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⣛⡉⢹⢛⣛⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿
 *	⣿⣿⣿⣿⣿⣿⣿⡟⣫⡆⠀⣿⣷⣬⣼⡿⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿
 *	⣿⣿⣿⣿⣿⣿⣿⣷⡘⢿⣾⡿⠿⠿⠛⢃⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
 *	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣌⠫⠶⠿⠟⣋⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
 *	⣿⣿⣿⣿⣿⣿⣿⡏⠉⠏⠩⣭⣭⠉⠘⠉⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿
 *	⣿⣿⣿⣿⣿⣿⣿⡇⠠⠤⠴⢯⣭⢤⠤⢄⢰⣿⣿⣿⣿⣿⣿⣿⣿⣿
 *	⣿⣿⣿⣿⣿⠋⠀⠀⠶⠬⢼⣸⣇⢠⠬⠼⠌⠀⠀⢹⣿⣿⣿⣿⣿⣿
 *	⣿⣿⣿⣿⣿⡆⠀⠀⠀⠀⠙⠙⠛⠉⠀⠀⠀⠀⠠⣾⣿⣿⣿⣿⣿⣿
 *	⣿⣿⣿⣿⠏⠀⢀⣮⣅⣛⠻⠇⠿⢛⣃⣩⣴⠃⠀⠈⣿⣿⣿⣿⣿⣿
 *	⣿⣿⣿⣧⡀⠀⠘⢿⣿⠿⠟⠻⠟⣛⠻⢿⠿⠀⠀⣼⣿⣿⣿⣿⣿⣿
 *	⣿⣿⣿⣿⣿⢀⠀⠀⠲⠈⣭⣭⢩⣭⡴⠐⠀⠀⡌⣿⣿⣿⣿⣿⣿⣿
 *	⣿⣿⣿⣿⠇⣾⣷⣦⣀⠀⠀⠈⠀⠀⠀⣠⣴⣿⣿⡸⣿⣿⣿⣿⣿⣿
 *	⣿⣿⣿⡏⣼⣿⣿⣿⣿⣿⣶⣤⣀⣴⣿⣿⣿⣿⣿⣧⢹⣿⣿⣿⣿⣿
 *	⣿⣿⣿⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣿⣿⣿⣿⣿
 *	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
 *	heheheha.
*/

#pragma once

// these basic inclusions make the class work.
#include "CoreMinimal.h"

// this guy inherits from ACharacter.
#include "GameFramework/Character.h"

// various types needed
#include "Data/Types/GameTypes.h"

// these are our projectile definition. ONLY INCLUDE THEM WHEN YOU NEED THEM DIRECTLY!
#include "Projectiles/Projectile.h"

// the game instance contains info about the whole game:
// level, player and gameplay data (including projectiles, types and various structs)
#include "CollisionQueryParams.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"

// this guy is auto generated. must be the last inclusion, or bad things will happen 💀
#include "Samus.generated.h"

UCLASS()
// Samos is le funni booty hunter, now reimagined in SEE PLUS PLUS (c++)!!! She can... exist, for now.
class ASamus : public ACharacter
{
	GENERATED_BODY()
	
//////////////////////////////////////////////////  ACTOR COMPONENTS  //////////////////////////////////////////////////

	// Rn these are just "ideas". The components do not exist yet.
protected:
	
	/** this is your shooting ahh display. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta=(AllowPrivateAccess="true"))
	class UCameraComponent* FirstPersonCamera;

	/** fake (impostor) (amogus) gun, but the real one for ballistic calculations. only the owner can see it! */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta=(AllowPrivateAccess="true"))
	class USkeletalMeshComponent* GameplayGun;

	/** real (crewmate) gun, but no calculations. the owner can't see it! */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta=(AllowPrivateAccess="true"))
	class USkeletalMeshComponent* CutsceneGun;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Timelines", meta=(AllowPrivateAccess="true"))
	class UTimelineComponent *Timeline;

///////////////////// ACTOR REFERENCES 🅱️🅿️🅱️🅿️ CONFIGURE THEM IN EDITOR FOR BLUEPRINT SUPPORT!!! /////////////////////
protected:
	
	#pragma region projectile_classreferences
    
    	/** Relationships between Blueprints and C++ are... weird. Blueprints act as classes on their own,
    	 * and you can't spawn them directly as classes (except for ConstructorHelpers).
    	 * A very normal approach to decide which projectile should we spawn is: get BeamType on the character, and switch on
    	 * it to get a StaticClass. This will spawn the C++ class, though, without any mesh or visual effect.
    	 *
    	 * So we spawn the classes pointed by THESE VARIABLES, edited in editor to point at BPs. Cool stuff, huh?
    	 */
    
    	// A reference to BP_Projectile_EnergyBeam class.
    	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Actor References|Projectiles")
    	TSubclassOf<AProjectile> EnergyBeamClass;
    
    	// A reference to BP_Projectile_Battlehammer class.
    	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Actor References|Projectiles")
    	TSubclassOf<AProjectile> BattlehammerClass;
    
    	// A reference to BP_Projectile_VoltDriver class.
    	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Actor References|Projectiles")
    	TSubclassOf<AProjectile> VoltDriverClass;
    
    	// A reference to BP_Projectile_Judicator class.
    	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Actor References|Projectiles")
    	TSubclassOf<AProjectile> JudicatorClass;
    
    	// A reference to BP_Projectile_Imperialist class.
    	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Actor References|Projectiles")
    	TSubclassOf<AProjectile> ImperialistClass;
    
    	// A reference to BP_Projectile_Magmaul class.
    	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Actor References|Projectiles")
    	TSubclassOf<AProjectile> MagmaulClass;
    
    	// A reference to BP_Projectile_ShockCoil class.
    	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Actor References|Projectiles")
    	TSubclassOf<AProjectile> ShockCoilClass;
    
    	// A reference to BP_Projectile_OmegaBeam class.
    	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Actor References|Projectiles")
    	TSubclassOf<AProjectile> OmegaBeamClass;
    	
	#pragma endregion projectile_classreferences
	
//////////////////////////// VARIABLES🔥🔥🔥🔥 I CAN'T HEAR YOU FROM MY UTF-8 ENCODING!!! /////////////////////////////

	//------------------------------------------------- Movement -----------------------------------------------------//
public:
	
	// Speed constants
	#pragma region movement_speedconstants
	
	/** walking speed (no sprinting) in all directions. tied to animation data. unit: UU/s. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Speed Constants")
	float WalkingSpeed = 142.f;

	/** sprinting speed (forward/strafing only). tied to animation data. unit: UU/s. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Speed Constants")
	float SprintingSpeed = 650.f;

	/** time needed to reach full sprint velocity from walking, and vice versa. unit: s \n
	 *  for the real Blueprint OGs, it's the duration of the Speed Interp curve in the Speed Timeline.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Speed Constants", meta=(UIMin="0.0",ClampMin="0.0"))
	float SprintingTime = .3f;

	/** instantaneous z speed when jumping normally. ue4 physics suck -- it'll be a lil bit floaty... */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Speed Constants")
	float JumpSpeed = 900.f;
	
	// Idling thresholds

	/** Turn/Lookup input in fixed mode must be less than this value, to consider the character as "idling" */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Speed Constants", meta=(UIMin="0.0",ClampMin="0.0",UIMax="1.0",ClampMax="1.0"))
	float IdlingThreshold_Fixed = 0.4f;

	#pragma endregion movement_speedconstants

protected:
	
	// Runtime and helpers
	#pragma region movement_runtime
	
	/** [0;1] helper value to interpolate walking/sprinting speed, and do various effects.
	 *  0 = not sprinting
	 *  1 = fully sprinting
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement|Runtime", meta=(ClampMin="0.0",ClampMax="1.0"))
	float SpeedAlpha = 0.f;

	/** While on controller, can we sprint? We shouldn't if MoveForward axis has a very low input. */

	/** Are we sprinting? Means that SpeedAlpha > hardcoded threshold. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement|Runtime")
	bool bIsSprinting = false;

	/** Are we in air? Very, very easy (0.1 gpa activity). */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement|Runtime")
	bool bIsInAir = false;

	/** Are we moving? Extremely ez. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement|Runtime")
	bool bIsMoving = false;

	#pragma endregion movement_runtime

	
	//--------------------------------------------------- Aiming -----------------------------------------------------//
public:

	// Aim constants: fixed aiming
	#pragma region aiming_fixed

	/** mouse sensitivity on the x-axis, fixed mode. unit is some unreal engine sorcery, tomfoolery. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aiming|Fixed Mode")
	float MouseSensX_Fixed = 1.f;

	/** mouse sensitivity on the y-axis, fixed mode. unit is some unreal engine sorcery, tomfoolery. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aiming|Fixed Mode")
	float MouseSensY_Fixed = 1.f;

	/** controller sensitivity on the x-axis, fixed mode. unit is: player rotation deg/s */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aiming|Fixed Mode")
	float ControllerSensX_Fixed = 180.f;

	/** controller sensitivity on the y-axis, fixed mode. unit is: player rotation deg/s */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aiming|Fixed Mode")
	float ControllerSensY_Fixed = 180.f;

	/** Offset of the cannon from camera center, in fixed mode.
	 *  Should be editable at runtime (inside a domain), the aiming/firing code takes cannon position in account. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aiming|Fixed Mode")
	FVector ArmCannonOffset_Fixed = FVector(14,16,-16);

	#pragma endregion aiming_fixed
	
	// Aim constants: movable aiming
	#pragma region aiming_movable
	
	/** mouse sensitivity on the x-axis, movable mode. unit is: @todo unit? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aiming|Movable Mode")
	float MouseSensX_Movable = 10.f;

	/** mouse sensitivity on the y-axis, movable mode. unit is: @todo unit? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aiming|Movable Mode")
	float MouseSensY_Movable = 10.f;

	/** controller sensitivity on the x-axis, movable mode. unit is: pixels/s.
	 * @todo: convert it to relative screen location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aiming|Movable Mode")
	float ControllerSensX_Movable = 500.f;

	/** controller sensitivity on the y-axis, movable mode. unit is: pixels/s.
	 * @todo: convert it to relative screen location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aiming|Movable Mode")
	float ControllerSensY_Movable = 500.f;

	/** maximum pitch rotation speed in movable mode (when the cursor is at y=0/y=max). unit is: pitch degrees/s. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aiming|Movable Mode")
	float PitchSpeed_Movable = 180.f;

	/** maximum yaw rotation speed in movable mode (when the cursor is at x=0/x=max). unit is: yaw degrees/s. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aiming|Movable Mode")
	float YawSpeed_Movable = 180.f;

	/** exponent applied to raw input on the x-axis, movable mode. a high value will zero out low values.
	 *  SIGN WILL BE PRESERVED FOR EVEN EXPONENTS -- DON'T WORRY! */
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Aiming|Movable Mode")
	int AimFilterX = 3;

	/** exponent applied to raw input on the y-axis, movable mode. a high value will zero out low values.
	 *  SIGN WILL BE PRESERVED FOR EVEN EXPONENTS -- DON'T WORRY! */
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Aiming|Movable Mode")
	int AimFilterY = 3;

	/** Offset of the cannon from camera center, in movable mode.
	 *  Should be editable at runtime (inside a domain), the aiming/firing code takes cannon position in account. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aiming|Movable Mode")
	FVector ArmCannonOffset_Movable = FVector(12,11,-16);

	#pragma endregion aiming_movable

	// Aim constants: gyro aiming
	#pragma region aiming_gyro
	#pragma endregion aiming_gyro

	/** The aim mode we're currently using.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aiming")
	EAimModes AimModes = EAimModes::Fixed;

	/** If the distance of a point behind the crosshair is less than this value, the cannon will correct its orientation
	 * to point at it. If not, treat it as infinite distance and do not adjust aiming. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aiming")
	float MaximumAimDistance = 3500.f;
	
protected:
	
	// Runtime
	#pragma region aiming_runtime

	#pragma region aiming_runtime:aiming_point_info

	/** distance of the aiming point ("target") from the player. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Aiming|Runtime|Aiming Point Info")
	float AimDistance;

	/** Location of the aiming point. To get this we cast a line trace: if there's a hit, that's the point,
	 * if there isn't, it'll be line trace end. Used for aim adjustments, HUD and Imperialist
	 * optimization.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Aiming|Runtime|Aiming Point Info")
	FVector AimingPoint;

	/** Normal of the aiming point. Just like AimingPoint, we cast a line trace. Defaults to UP (0;0;1) if no hit. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Aiming|Runtime|Aiming Point Info")
	FVector AimingNormal;

	/** The actor we (might) be pointing at. We still don't know if it's a target or just a clump of sand,
	 *  so get ready to cast to something like ATargetablePawn. And we don't even know if it's valid! */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Aiming|Runtime|Aiming Point Info")
	AActor* AimingTargetActor;
	#pragma endregion aiming_runtime:aiming_point_info

	/** location of the crosshair on the screen. only meaningful with movable or gyro mode. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Aiming|Runtime")
	FVector2D CrosshairScreenLocation;
	
	#pragma endregion aiming_runtime

	//--------------------------------------------------- Firing -----------------------------------------------------//
public:
	
	/** The beam type we're currently using. Ultra ez. Defaults to EnergyBeam. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Firing")
	EBeamTypes BeamType = EBeamTypes::EnergyBeam;
	
protected:
	
	/** The projectile class we've chosen to spawn. Can change at runtime, of course.
	 *  Defaults to EnergyBeamClass (BP_Projectile_EnergyBeam) to avoid nullptr madness.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Firing")
	TSubclassOf<AProjectile> ProjectileClassToSpawn = EnergyBeamClass;

	/** Beam index to spawn. Ranges from 0 to NumberOfBeams, I think.
	 *	Only needed internally: this will create an efficient selection loop using modulo.
	 *	The result of this modulo operation will be propagated back to EBeamTypes BeamType.
	 */
	int BeamTypeIndex = 0;
	const int NumberOfBeams = 8;

#pragma region projectile_data
	// Here we got the data that will be extracted from the projectile BPs.

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Firing|Projectile Data|Energy Beam")
	float EnergyBeam_Delay = .05f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Firing|Projectile Data|Battlehammer")
	float Battlehammer_Delay = .05f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Firing|Projectile Data|Judicator")
	float Judicator_Delay = .05f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Firing|Projectile Data|Volt Driver")
	float VoltDriver_Delay = .05f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Firing|Projectile Data|Imperialist")
	float Imperialist_Delay = .05f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Firing|Projectile Data|Magmaul")
	float Magmaul_Delay = .05f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Firing|Projectile Data|Shock Coil")
	float ShockCoil_Delay = .05f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Firing|Projectile Data|Omega Beam")
	float OmegaBeam_Delay = .05f;
	
#pragma endregion projectile_data

	/** A reference to the last projectile spawned. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Firing")
	AProjectile* LastProjectileSpawned;


	//-------------------------------------------------- Debug Stuff -------------------------------------------------//

	#pragma region debug
	
	/** Should we draw our AIM ADJUST line traces? */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Debug")
	bool Debug_bShowAimAdjustTrace = false;

	/** Color of the aim adjust debug lines. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Debug")
	FColor Debug_AimAdjustTraceColor = FColor::Red;
	#pragma endregion debug
	
/////////////////////////////////// FUNCTIONS 👌👌👌👌👌 BLOW UP UR PC WITH THESE /////////////////////////////////////

	//--------------------------------------------------- Engine -----------------------------------------------------//
public:
	
	// --------- Constructors --------- //
	
	ASamus(); // "let there be ASamus" - the constructor gods

	// Equivalent of Construction Script.
	virtual void OnConstruction(const FTransform& Transform) override;

	// --------- Editor Overrides --------- //

	// Called when the game starts or when spawned.
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// -------------------------------------------------- Input ----------------------------------------------------- //
protected:
	// Basic movement
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	
	/** weeeeeeeeee. a simple linear interp between walking and sprinting speed. */
	void Sprint(float AxisValue);

	// Actions. Jump and StopJumping are defined in ACharacter.
	void NextWeapon(); // select the next weapon.
	void PrevWeapon(); // select the previous weapon.
	void Kaboom(); // FIRE!!!
	void LockOn(); // fortnite free hacks 100% no virus aimbot esp wallhack

	// Basic aiming
	void Turn(float AxisValue); // mouse based
	void LookUp(float AxisValue); // mouse based
	void TurnRate(float AxisValue); // joystick based
	void LookUpRate(float AxisValue); // joystick based

	// ---------------------------------------------- Gameplay State ------------------------------------------------ //

	/** A very neat piece of code, which updates the helper movement variables during Tick().
	 *  We can pass these variables to, let's say, an AnimBP and create an animation. Cool stuff!
	 */
	void UpdateMovementVariables();

	/** Another amazing piece of code to execute when we are changing weapons. Do stuff! */
	void UpdateWeapon();


	// ---------------------------------------------- Cannon and Aim ------------------------------------------------ //

	// The Arm Cannon can be Aim Adjusted in a way so that a projectile will actually hit the point behind the crosshair.
	// Originally, there was a unique BP function for all three control modes.
	// But it's pretty hard to read in C++ code. So, I sliced it in three parts.

	// Aim adjustments for fixed mode.
	void AdjustAiming_Fixed();
	
	// Aim adjustments for movable mode.
	void AdjustAiming_Movable();
	
	// Aim adjustments for gyro mode.
	void AdjustAiming_Gyro();

	// ------------------------------------------------- Utilities -------------------------------------------------- //
	
	/** This helper function selects which projectile class are we gonna spawn. FORCEINLINE so BLAZINGLY FAST. */
	FORCEINLINE TSubclassOf<AProjectile> GetProjectileClassToSpawn() const
	{
		switch (BeamType)
		{
		case 0: return EnergyBeamClass;
		case 1: return BattlehammerClass;
		case 2: return JudicatorClass;
		case 3: return VoltDriverClass;
		case 4: return ImperialistClass;
		case 5: return MagmaulClass;
		case 6: return ShockCoilClass;
		case 7: return OmegaBeamClass;
		case 255: return EnergyBeamClass;
		default: return EnergyBeamClass;
		}
	}

	/** This function casts a raytrace and returns some stuff. FORCEINLINEd, but idk if it actually works.*/
	FORCEINLINE bool LineTraceByChannel(FVector Start, FVector End, FHitResult& Hit)
	{
		return UKismetSystemLibrary::LineTraceSingle(
		GetWorld(),
		Start,
		End,
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false,
		TArray<AActor*>(),
		Debug_bShowAimAdjustTrace ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
		Hit,
		true);
	}

	// -------------------------------------------------- Getters --------------------------------------------------- //
public:
	// @todo: target and lock on target getters?

	/** Returns the current crosshair screen location. Useful for HUD and Widgets. FORCEINLINE WHOOOM!!! */
	FORCEINLINE FVector2D GetCrosshairLocation()
	{
		return CrosshairScreenLocation;
	}
};
