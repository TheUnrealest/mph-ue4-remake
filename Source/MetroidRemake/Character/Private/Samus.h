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

// these types (enums, structures, etc.) will be really useful for this character.
#include "Types/GameTypes.h"

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
	
//////////////////////////// VARIABLES🔥🔥🔥🔥 I CAN'T HEAR YOU FROM MY UTF-8 ENCODING!!! /////////////////////////////

	//------------------------------------------------- Movement -----------------------------------------------------//
public:
	
	// Speed constants
	
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
	

protected:
	
	// Runtime and helpers
	
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

	

	
	//--------------------------------------------------- Aiming -----------------------------------------------------//
public:
	
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

	/** mouse sensitivity on the x-axis, movable mode. unit is: @todo unit? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aiming|Movable Mode")
	float MouseSensX_Movable = 100.f;

	/** mouse sensitivity on the y-axis, movable mode. unit is: @todo unit? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aiming|Movable Mode")
	float MouseSensY_Movable = 100.f;

	/** controller sensitivity on the x-axis, movable mode. unit is: pixels/s.
	 * @todo: convert it to relative screen location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aiming|Movable Mode")
	float ControllerSensX_Movable = 500.f;

	/** controller sensitivity on the y-axis, movable mode. unit is: pixels/s.
	 * @todo: convert it to relative screen location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aiming|Movable Mode")
	float ControllerSensY_Movable = 500.f;

protected:
	/** location of the crosshair on the screen. only meaningful with movable or gyro mode. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Aiming|Runtime")
	FVector2D CrosshairScreenLocation;

	
//////////////////////////////////  FUNCTIONS 👌👌👌👌👌 BLOW UP UR PC WITH THESE /////////////////////////////////////

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
	void Kaboom();
	void LockOn();

	// Basic aiming
	void Turn(float AxisValue);
	void LookUp(float AxisValue);
	void TurnRate(float AxisValue); // joystick based
	void LookUpRate(float AxisValue); // joystick based

	// ---------------------------------------------- Gameplay State ------------------------------------------------ //

	/** A very neat piece of code, which updates the helper movement variables during Tick().
	 *  We can pass these variables to, let's say, an AnimBP and create an animation. Cool stuff!
	 */
	void UpdateMovementVariables();

};
