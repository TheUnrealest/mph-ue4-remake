// heheheha

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

/** This is an abstract class. It contains the base structure for a projectile.
 *	Also contains standard functions for physics and collision handling.
 *
 *	Turns out you CAN create a blueprint from C++ and spawn it using ConstructorHelpers.
 */

UCLASS()
class METROIDREMAKE_API AProjectile : public AActor
{
	GENERATED_BODY()

//// ACTOR COMPONENTS: PROJECTILE
public: // Ideally these should be public, to allow external access and extract projectile data at startup.

	/** This is a collision component. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UPrimitiveComponent* SphereCollision;

	/** An eventual mesh to be used (NO COLLISION!!!) */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* StaticMesh;

	/** An eventual particle system to be used. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UParticleSystemComponent* ParticleSystemComponent;
	
	/** Our Projectile Movement Component. Will wheeee around our projectile!!! */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UProjectileMovementComponent* ProjectileMovement;

//// VARIABLES
public:

	/** Projectile damage to the body. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile Configuration|Normal Projectile")
	int Damage = 5;

	/** Projectile damage to the head. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile Configuration|Normal Projectile")
	int HeadshotDamage = 10;

	/** Cannon effect for the projectile. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile Configuration|Normal Projectile|Effects")
	UParticleSystem* CannonEffectEmitter;

	/** Impact effect for the projectile */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile Configuration|Normal Projectile|Effects")
	UParticleSystem* ImpactEffectEmitter;
	
public:
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Hit for projectile collisions (both dynamic or kinematic)
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
