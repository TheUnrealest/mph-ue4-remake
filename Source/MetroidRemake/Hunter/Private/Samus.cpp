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
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
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

	// Impostor (amogus) gun is visible only for us. Real stuff (cutscene) is hidden to us, but visible to the world.
	GameplayGun->SetOnlyOwnerSee(true);
	CutsceneGun->SetOwnerNoSee(true);
	GetMesh()->SetOwnerNoSee(true);
	
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
	
	UpdateMovementVariables();
	
	switch (AimModes)
	{
	case EAimModes::Fixed: 	AdjustAiming_Fixed();
	case EAimModes::Movable: ;
	case EAimModes::Gyro: ;
	}
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
	PlayerInputComponent->BindAction("NextWeapon",IE_Pressed,this,&ASamus::NextWeapon);
	PlayerInputComponent->BindAction("PrevWeapon",IE_Pressed,this,&ASamus::PrevWeapon);

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
	switch(AimModes)
	{
	case EAimModes::Fixed: 
		AddControllerYawInput(AxisValue*MouseSensX_Fixed);
	case EAimModes::Movable:
		CrosshairScreenLocation.X += AxisValue*MouseSensX_Movable;
	case EAimModes::Gyro: break;
	}

	// mouse input is calculated as a distance and not as a velocity. looks like we don't need delta seconds here...
}

void ASamus::LookUp(float AxisValue)
{
	// mouse input is calculated as a distance and not as a velocity. looks like we don't need delta seconds here...
	switch (AimModes)
	{
	case EAimModes::Fixed:
		AddControllerPitchInput(AxisValue*MouseSensY_Fixed); break;
	case EAimModes::Movable:
		CrosshairScreenLocation.Y += AxisValue*MouseSensY_Movable; break;
	case EAimModes::Gyro: break;
	}
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
	// 1. Are we able to fire? @todo do this.

	// 2. Let the mess begin.
	// First of all, we need to create Spawn Parameters. Essential to pass info to the created projectile.
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this; // Player is owner...

	// We can now spawn a projectile and get a reference to it.
	LastProjectileSpawned = GetWorld()->SpawnActor<AProjectile>(
		ProjectileClassToSpawn,						// Spawn the selected class,
		GameplayGun->GetSocketLocation("Gun"),		// at the gun muzzle location,
		GameplayGun->GetSocketRotation("Gun"),		// with the gun world rotation.
		SpawnParams);
	
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

void ASamus::NextWeapon()
{
	// Mr. Maciocco told me a modulo (%) is amazing to create loops of values. Well, here goes nothing!
	BeamTypeIndex++;
	BeamTypeIndex %= NumberOfBeams; // BRO I SWEAR THE AUTOCOMPLETE FUNCTION IS AMAZING
	BeamType = static_cast<EBeamTypes>(BeamTypeIndex); // I am no cpp wizard... don't even know if this is good practice
	UpdateWeapon(); // execute additional game state updates when changing a weapon.
}

void ASamus::PrevWeapon()
{
	// Same as NextWeapon(), but we subtract 1 from BeamTypeIndex.
	BeamTypeIndex--;
	BeamTypeIndex %= NumberOfBeams;
	BeamType = static_cast<EBeamTypes>(BeamTypeIndex); // and the autocomplete function strikes again.
	UpdateWeapon(); // execute additional game state updates when changing a weapon.
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

void ASamus::UpdateWeapon()
{
	ProjectileClassToSpawn = GetProjectileClassToSpawn(); // update which projectile we will spawn.
}


//////////////////////////////////////////////////// AIM ADJUSTMENTS ///////////////////////////////////////////////////

void ASamus::AdjustAiming_Fixed()
{
	/** Adjusting aiming means to "let the projectile impact behind the crosshair". How do we do this?
	 *	Very simple: we rotate the Arm Cannon.
	 *
	 *	Let's say we have a line of sight, which starts from camera center and lands to the point behind the crosshair.
	 *	Now, we want the projectile to hit that point behind the crosshair. Of course, without adjustments, it WON'T
	 *	hit because the cannon position is different from the camera position.
	 *	
	 *	What we want to do is to calculate the rotation needed for the cannon to point at the desired aiming point. And
	 *	to do that, we just need to:
	 *	1) get information on the point behind the crosshair (location, distance from us, normals and stuff)
	 *	2) LookAtRotation() will align the cannon to "point" at a certain "point" (pun intended).
	 *
	 *	For this edge case, the crosshair location is at the center of the camera (ViewportSize/2) at all times.
	 */

	FVector TraceStart = FirstPersonCamera->GetComponentLocation(); // starting point of the trace
	FVector TraceEnd = TraceStart + FirstPersonCamera->GetForwardVector()*MaximumAimDistance; // end position of the trace
	FHitResult Hit;
	
	if (LineTraceByChannel(TraceStart,TraceEnd, Hit))
	{
		// We got a hit, which means there's something we can aim to, on our line of sight.
		AimDistance = Hit.Distance;
		AimingPoint = Hit.Location;
		AimingNormal = Hit.ImpactNormal;
		AimingTargetActor = Hit.GetActor();

		// Now, we try to get the rotation needed by the cannon to aim at the desired point.
		FVector CannonLocation = GameplayGun->GetComponentLocation();
		FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(CannonLocation,Hit.Location);
		NewRotation.Roll = 0.f;
		
		GameplayGun->SetWorldRotation(NewRotation); // and we set it to the cannon. that FindLook is in world space.
		// Geez, it looks really complicated here (but it's not). It's quite intuitive in Blueprints.
	}
	else
	{
		// The aiming point will be at the end of the trace, with max distance, and up normal. No actor.
		AimDistance = MaximumAimDistance;
		AimingPoint = TraceEnd;
		AimingNormal = FVector::UpVector;
		AimingTargetActor = nullptr; // nullptr ts too.
		
		// we only know the rotation relative to camera must be 0, we don't know what are we actually watching in WS.
		GameplayGun->SetRelativeRotation(FRotator(0, 0, 0));
	}
}

void ASamus::AdjustAiming_Movable()
{
	/** This is a generalization of AdjustAiming_Fixed(), where our aiming point is not calculated from camera position
	 *  (because the crosshair is not at the center anymore). We'll use screen deprojection to get the 3d point behind
	 *  the crosshair at a certain X;Y screen position.
	 */
	
}

void ASamus::AdjustAiming_Gyro()
{
	
}

////////////////////////////////////////////////////// UTILITIES ///////////////////////////////////////////////////////

FORCEINLINE TSubclassOf<AProjectile> ASamus::GetProjectileClassToSpawn() const
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

FORCEINLINE bool ASamus::LineTraceByChannel(FVector Start, FVector End, FHitResult& Hit)
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