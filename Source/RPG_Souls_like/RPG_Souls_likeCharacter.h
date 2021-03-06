// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Type/StructType.h"
#include "Sound/SoundBase.h"
#include "GenericTeamAgentInterface.h"
#include "RPG_Souls_likeCharacter.generated.h"

/* character attribute */
struct FCharacterAttribute {
	
	//class
	TEnumAsByte<ECharacterClass> CharacterClass;

	//texture
	class UTexture2D* CharacterImage;

	//level
	uint8 CharacterLevel;

	//vitality
	uint32 CharacterVitality;

	//attunement
	uint32 CharacterAttunement;

	//strength
	uint32 CharacterStrength;

	//agility
	uint32 CharacterAgility;

	//intelligence
	uint32 CharacterIntelligence;

	//max hp
	uint32 CharacterMaxHp;

	//current hp
	uint32 CharacterCurrentHp;

	//max mp
	uint32 CharacterMaxMp;

	//current mp
	uint32 CharacterCurrentMp;

	//max stamina
	float CharacterMaxStamina;

	//current stamina
	float CharacterCurrentStamina;

	//max exp
	uint32 CharacterMaxExp;

	//current exp
	uint32 CharacterCurrentExp;

	//resistance
	float CharacterResistance;

	//endurance
	uint32 CharacterEndurance;

	//movement speed
	float CharacterMovementSpeed;

	//attack damage
	uint32 CharacterAttackDamage;

	//magic damage
	uint32 CharacterMagicDamage;

	//skill point
	uint8 SkillPoint;

};

UCLASS(config=Game)
class ARPG_Souls_likeCharacter : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	ARPG_Souls_likeCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:
	/* character attribute */
	FCharacterAttribute CharacterAttribute;

	//weapon base
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ABladeWeapon> WeaponClass;

	//shield base
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AShieldWeapon> ShieldClass;

	class ABladeWeapon* Weapon;

	class AShieldWeapon* Shield;

	bool RegenerateStamina;

	// character state
	TEnumAsByte<ECharacterState> CharacterState;

public:
	/* get attribute text block*/
	//get character class
	UFUNCTION()
	FText GetCharacterClass();

	//get character health, mana, stamina, exp
	UFUNCTION()
	FText GetCharacterBasic(int32 Max, int32 Current, FString String);

	//get character vitality, attunement, endurence, strength, agility, intelligence
	UFUNCTION()
	FText GetCharacterAttribute(int32 SelfAttribute, FString String);
	
	FORCEINLINE FCharacterAttribute GetCharacterProperty() { return CharacterAttribute; }

	void SetHealth(int32 const NewHealth);

	void SetVitality(uint32 const NewVitality);

	void SetMana(int32 const NewMana);

	void SetAttunement(uint32 const NewAttunement);

	void SetStamina(float const NewStamina);

	void SetEndurance(uint32 const NewEndurance);

	void SetExp(uint32 const NewExp);

	void SetStrength(uint32 const NewStrength);

	void SetAgility(uint32 const NewAgility);

	void SetIntelligence(uint32 const NewIntelligence);

	void SetResistance(float const NewResistance);

	void SetSkillPoint(uint8 const NewSkillPoint);

	// return team id
	virtual FGenericTeamId GetGenericTeamId() const override { return TeamId; }

	/* impact montage*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowprivateAccess = "true"))
		class UAnimMontage* ImpactMontage;

	/* block_impact montage*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowprivateAccess = "true"))
		class UAnimMontage* BlockImpactMontage;

	void GettingHit();

	//able or unable to receive inputs
	bool HitRecover = true;

	//spawn weapon
	void SpawnWeapon();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	class ACharacterPlayerController* Pc;

	/**
	* AttackStart - trigger when the player initiates an attack
	*/
	virtual void AttackStart();

	/**
	* AttackEnd - trigger when the player stops an attack
	*/
	virtual void AttackEnd();

	/**
	* AttackInput - trigger attack animations based on user input
	*/
	virtual void AttackInput();

	/**
	* CastSpellStart - trigger when the player initiates an CastSpell
	*/
	virtual void CastSpellStart();

	/**
	* CastSpellEnd - trigger when the player stops an CastSpell
	*/
	virtual void CastSpellEnd();

	/**
	* CastSpellInput - trigger CastSpell animations based on user input
	*/
	virtual void CastSpellInput();

	/**
	* BlockStart - trigger when the player initiates an Block
	*/
	virtual void BlockStart();

	/**
	* BlockEnd - trigger when the player stops an Block
	*/
	virtual void BlockEnd();

	/**
	* BlockInput - trigger Block animations based on user input
	*/
	virtual void BlockInput();

	bool IsBlockPressed;

	/**
	* RollStart - trigger when the player initiates a Roll
	*/
	virtual void RollStart();

	/**
	* RollEnd - trigger when the player stops a Roll
	*/
	virtual void RollEnd();

	/**
	* RollInput - trigger Roll animations based on user input
	*/
	virtual void RollInput();

	/**
	* OnAttackHit - triggerred when the collision hit event fires between the weapon and enmy eneities
	*/
	UFUNCTION()
	void OnAttackHit(UPrimitiveComponent* HitComponent, 
		AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/**
	* OnAttackOverlapBegin - triggerred when the collider overlaps another component
	*/
	UFUNCTION()
		void OnAttackOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/**
	* OnAttackOverlapEnd - triggerred when the collider stops overlapping another component
	*/
	UFUNCTION()
		void OnAttackOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/**
	* OnBlockOverlapBegin - triggerred when the collider overlaps another component
	*/
	UFUNCTION()
		void OnBlockOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/**
	* OnBlockOverlapEnd - triggerred when the collider stops overlapping another component
	*/
	UFUNCTION()
		void OnBlockOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	bool AttackBlocked;

	int32 Buff;

	int32 Damage;

	void LockOnEnemy();

	void TargetEnemy();

	AActor* LockOnTarget;

	bool ToggleLock = false;

	bool IsTargeted;


private:
	class UAIPerceptionStimuliSourceComponent* Stimulus;

	void SetupStimulus();

	void OnDistract();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound", meta = (AllowPrivateAccess = "true"))
		USoundBase* DistractionSound;

	TArray<AActor*> AlreadyAttackedEnemy;

	/* level up particle system*/
	UParticleSystem* LevelParticleSystem;
	UParticleSystemComponent* LevelParticleComponent;

	void LevelUp(uint32 const NewExp);

	// team id
	FGenericTeamId TeamId;
};

