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
// coding jesus be like "YOUR CODE MUST BE SELF DOCUMENTING🥵🥵🥵!!11!! DON'T LEAVE COMMENTS!11!!".
// Bruh let me do what I want with my code.

// this guy contains all the juicy component declaration. blueprint generation starts from here.
#include "Samus.h"

// these guys contain all the boring stuff, but they are essential to actually "make" the components real.
#include "BlueprintEditorUtils.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

//////////////////////////////////////// THE MIGHTY CONSTRUCTOR METHOD(s?) /////////////////////////////////////////////

// "let there be UActorComponents and UPROPERTY-ies, and make them attach." - the memory allocator
ASamus::ASamus()
{
	/** *drums rolling* This is Samos' CONSTRUCTOR METHOD!!!
	  * Basically, the engine wants to generate some ACharacter based on this cpp code.
	  * In this method, we need to specify HOW to do that:
	  * 1. We take the component declarations in Samus.h and construct actual "subobjects" based on them.
	  * 2. We gon attach them and do some madness.
	  * There's an exception for complex transform operations. We'll cover them in the next step.
	  */
	
	// This is your shooting ahhh display.
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>("FirstPersonCamera");
	FirstPersonCamera->SetupAttachment(GetMesh());
	
	// Le fake cannon.
	GameplayGun = CreateDefaultSubobject<USkeletalMeshComponent>("GameplayGun");
	GameplayGun->SetupAttachment(FirstPersonCamera);

	// Le real (100% no cap) cannon.
	CutsceneGun = CreateDefaultSubobject<USkeletalMeshComponent>("CutsceneGun");
	
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// "Remember me? This IS me, but 1000x better." - the BP Construction Script
void ASamus::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	/** Just like the Construction Script, turns out ue4 also has a "OnConstruction()".
	 *  This can be used for complex transform operations, such as attaching stuff to sockets.
	 *  Yep, that's right. SetupAttachment() only works for hierarchy, not for transforms.
	 */

	CutsceneGun->AttachToComponent(
		GetMesh(),
		FAttachmentTransformRules::SnapToTargetNotIncludingScale,
		TEXT("GunSocket")); // Ts (this) attaches CutsceneGun to Samus' Suit.
	
}

//////////////////////////////////////////// ENGINE STANDARD FUNCTIONS /////////////////////////////////////////////////

// Called when the game starts or when spawned
void ASamus::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASamus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASamus::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Basic Movement
	PlayerInputComponent->BindAxis("MoveForward",this, &ASamus::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this, &ASamus::MoveRight);
	PlayerInputComponent->BindAxis("Sprint",this, &ASamus::Sprint);
	// Sprinting button is converted to axis to have a callback check every frame. Required for morphing.

	// Actions
	PlayerInputComponent->BindAction("Jump",IE_Pressed,this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump",IE_Released,this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Fire",IE_Pressed, this, &ASamus::Kaboom);
	PlayerInputComponent->BindAction("LockOn",IE_Pressed, this, &ASamus::LockOn);

	// Aiming
	PlayerInputComponent->BindAxis("Turn",this, &ASamus::Turn);
	PlayerInputComponent->BindAxis("LookUp",this, &ASamus::LookUp);
	PlayerInputComponent->BindAxis("TurnRate",this, &ASamus::TurnRate);
	PlayerInputComponent->BindAxis("LookUpRate",this, &ASamus::LookUpRate);
}

///////////////////////////////////////////////// INPUT FUNCTIONS //////////////////////////////////////////////////////

//------------------------------------------------ Basic movement ----------------------------------------------------//

void ASamus::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector(), AxisValue);
}

void ASamus::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector(), AxisValue);
}

//--------------------------------------------------- Aim input ------------------------------------------------------//


void ASamus::Turn(float AxisValue)
{
	// mouse input is calculated as a distance and not as a velocity. looks like we don't need delta seconds here...
	AddControllerYawInput(AxisValue*MouseSensX_Fixed);
}

void ASamus::LookUp(float AxisValue)
{
	// mouse input is calculated as a distance and not as a velocity. looks like we don't need delta seconds here...
	AddControllerPitchInput(AxisValue*MouseSensY_Fixed);
}

void ASamus::TurnRate(float AxisValue)
{
	AddControllerYawInput(AxisValue*ControllerSensX_Fixed*GetWorld()->GetDeltaSeconds());
}

void ASamus::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue*ControllerSensY_Fixed*GetWorld()->GetDeltaSeconds());
}

//----------------------------------------------------- Actions ------------------------------------------------------//

// OPEN FIREEEEEE!!!
void ASamus::Kaboom()
{
}

void ASamus::LockOn()
{
}

void ASamus::Sprint(float AxisValue)
{
	/** In Blueprint, I used a Timeline to drive SpeedAlpha with precision.
	 * It would "progress to 1 linearly" when AxisValue == 1,
	 * and would "reverse to 0 linearly" when AxisValue == 0.
	 * Unfortunately, in C++, timelines are... impossible to use. You can declare them, but you can't set them up.
	 *
	 * So what we do here is: increase or decrease SpeedAlpha by DeltaSeconds divided by SprintingTime,
	 * respectively when button is pressed/not pressed.
	 * Since DeltaSeconds is actual time passed between frames, dividing by SprintingTime can let us
	 * accelerate/decelerate faster/slower. Me omw to laugh in "numerical integration".
	 */
	
	if (AxisValue == 0) { SpeedAlpha-= GetWorld()->GetDeltaSeconds()/SprintingTime; }
	else if (AxisValue == 1) { SpeedAlpha+= GetWorld()->GetDeltaSeconds()/SprintingTime; }
	SpeedAlpha = FMath::Clamp(SpeedAlpha, 0.0f, 1.0f); // We also need to clamp to [0;1] domain.

	// Using the computed SpeedAlpha, we can calculate the character velocity and set it to MaxWalkSpeed.
	// A Lerp is the perfect combination between smoothness and ease of gameplay.
	GetCharacterMovement()->MaxWalkSpeed = FMath::Lerp(WalkingSpeed,SprintingSpeed, SpeedAlpha);
}

////////////////////////////////////////////// GAMEPLAY STATE FUNCTIONS ////////////////////////////////////////////////

void ASamus::UpdateMovementVariables()
{
	/* There are a lot of ways to determine if a character is moving:
	 * - how about manually doing GetCharacterMovement->Velocity ?
	 * - or how about checking on the input?
	 * But the first one will retrieve a movement even if the character is standing on a moving platform.
	 * The second one may retrieve a movement in particular situations (stun, input partially disabled, etc...).
	 *
	 * Best way would be to get the velocity relative to the base we're standing on, and then check if it's nearly 0.
	 * */

	FVector BaseVelocity = GetCharacterMovement()->GetImpartedMovementBaseVelocity();
	FVector Velocity = GetCharacterMovement()->Velocity;
	bIsMoving = (Velocity - BaseVelocity).IsNearlyZero();

	// Checking if our character is sprinting is quite straightforward: SpeedAlpha must be greater than a threshold.
	bIsSprinting = (SpeedAlpha > .5f) & bIsMoving; // let's say .5f, in the middle.

	// Ue4 functions have odd naming. And here's the demonstration.
	bIsInAir = !GetCharacterMovement()->IsMovingOnGround(); // IsMovingOnGround() means "is touching the ground".
	
	
}