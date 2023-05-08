// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SoulslikeCharacter.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AttributeComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Items/Item.h"
#include "Items/Weapon/Weapon.h"
#include "Animation/AnimMontage.h"
#include "HUD/SoulslikeHUD.h"
#include "HUD/SoulslikeOverlay.h"
#include "Items/Soul.h"
#include "Items/Treasure.h"
#include "TargetSystemComponent.h"


ASoulslikeCharacter::ASoulslikeCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f);

	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 300.f;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(CameraBoom);

	TargetSystem = CreateDefaultSubobject<UTargetSystemComponent>(TEXT("TargetSystem"));
	TargetSystem->TargetableActors = ABaseCharacter::StaticClass();
	TargetSystem->LockedOnWidgetParentSocket = FName("LockOnTarget");
}

void ASoulslikeCharacter::Tick(float DeltaTime)
{
	if (Attributes && SoulslikeOverlay && IsUnoccupied())
	{
		Attributes->RegenStamina(DeltaTime);
		SoulslikeOverlay->SetStaminaBarPercent(Attributes->GetStaminaPercent());
	}
}

void ASoulslikeCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(SoulslikeContext, 0);
		}
	}

	Tags.Add(FName("EngageableTarget"));

	InitializeSoulslikeOverlay();
	SetDodgeDirectionForward();
}

void ASoulslikeCharacter::Move(const FInputActionValue& Value)
{
	if (ActionState != EActionState::EAS_Unoccupied) return;

	const FVector2D MovementVector = Value.Get<FVector2D>();
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	//Actor Standard Movement
	//const FVector ForwardDirection = GetActorForwardVector();
	//const FVector RightDirection = GetActorRightVector();

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, MovementVector.Y);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, MovementVector.X);

	DodgeDirection = ForwardDirection * MovementVector.Y + RightDirection * MovementVector.X;
	//UE_LOG(LogTemp, Warning, TEXT("%lf, %lf, %lf"), DodgeDirection.X, DodgeDirection.Y, DodgeDirection.Z);
}

void ASoulslikeCharacter::MoveEnd(const FInputActionValue& Value)
{
	SetDodgeDirectionForward();
}

void ASoulslikeCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerPitchInput(LookAxisVector.Y);
	AddControllerYawInput(LookAxisVector.X);
	TargetSystem->TargetActorWithAxisInput(LookAxisVector.X);
}

void ASoulslikeCharacter::EKeyPressed()
{
	AWeapon* OverlappingWeapon = Cast<AWeapon>(OverlappingItem);
	if (OverlappingWeapon)
	{
		if (EquippedWeapon)
		{
			EquippedWeapon->Destroy();
		}
		EquipWeapon(OverlappingWeapon);
	}
	else
	{
		if (CanDisarm())
		{
			Disarm();
		}
		else if (CanArm())
		{
			Enarm();
		}
	}
}

void ASoulslikeCharacter::Dodge()
{
	if (!IsUnoccupied() || !HasEnoughStamina()) return;
	const FRotator FacingRotator = DodgeDirection.Rotation();
	SetActorRotation(FacingRotator);
	isInvincible = true;

	PlayDodgeMontage();
	ActionState = EActionState::EAS_Dodge;
	if (Attributes && SoulslikeOverlay)
	{
		Attributes->UseStamina(Attributes->GetDodgeCost());
		SoulslikeOverlay->SetStaminaBarPercent(Attributes->GetStaminaPercent());
	}
}

void ASoulslikeCharacter::LockOn()
{
	if (IsDead()) return;

	TargetSystem->TargetActor();
	CombatTarget = TargetSystem->IsLocked() ? TargetSystem->GetLockedOnTargetActor() : nullptr;
}


void ASoulslikeCharacter::EquipWeapon(AWeapon* Weapon)
{
	Weapon->Equip(GetMesh(), FName("RightHandSocket"), this, this);
	CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;
	OverlappingItem = nullptr;
	EquippedWeapon = Weapon;
}

void ASoulslikeCharacter::Attack1()
{
	Super::Attack1();

	if (CanAttack())
	{
		if (CombatTarget)
		{
			FaceTarget(CombatTarget->GetActorLocation());
		}
		PlayAttack1Montage();
		ActionState = EActionState::EAS_Attacking;
	}
	
}

void ASoulslikeCharacter::PlayEquipMontage(FName SectionName)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && EquipMontage)
	{
		AnimInstance->Montage_Play(EquipMontage, 1.f);
		AnimInstance->Montage_JumpToSection(SectionName, EquipMontage);
	}
}

void ASoulslikeCharacter::AttackEnd()
{
	Super::AttackEnd();
	ActionState = EActionState::EAS_Unoccupied;
}

bool ASoulslikeCharacter::CanAttack()
{
	return 	ActionState == EActionState::EAS_Unoccupied &&
		CharacterState != ECharacterState::ECS_Unequipped;
}

void ASoulslikeCharacter::DodgeEnd()
{
	Super::DodgeEnd();
	ActionState = EActionState::EAS_Unoccupied;
}

void ASoulslikeCharacter::DodgeInvincibleEnd()
{
	Super::DodgeInvincibleEnd();
}

bool ASoulslikeCharacter::CanDisarm()
{

	return 	ActionState == EActionState::EAS_Unoccupied &&
		CharacterState != ECharacterState::ECS_Unequipped;
}

bool ASoulslikeCharacter::CanArm()
{
	return 	ActionState == EActionState::EAS_Unoccupied &&
		CharacterState == ECharacterState::ECS_Unequipped &&
		EquippedWeapon;
}

void ASoulslikeCharacter::Disarm()
{
	PlayEquipMontage(FName("Unequip"));
	CharacterState = ECharacterState::ECS_Unequipped;
	ActionState = EActionState::EAS_EquippingWeapon;
}

void ASoulslikeCharacter::Enarm()
{
	PlayEquipMontage(FName("Equip"));
	CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;
	ActionState = EActionState::EAS_EquippingWeapon;
}

void ASoulslikeCharacter::FaceTarget(FVector TargetVector)
{
	FVector FacingDirection = TargetVector - GetActorLocation();
	FacingDirection.Z = 0.f;
	const FRotator FacingRotator = FacingDirection.Rotation();
	SetActorRotation(FacingRotator);
}

void ASoulslikeCharacter::Die_Implementation()
{
	Super::Die_Implementation();

	TargetSystem->TargetLockOff();
	ActionState = EActionState::EAS_Dead;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ASoulslikeCharacter::AttachWeaponToBack()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->AttachMeshToSocket(GetMesh(), FName("SpineSocket"));
	}
}

void ASoulslikeCharacter::AttachWeaponToHand()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->AttachMeshToSocket(GetMesh(), FName("RightHandSocket"));
	}
}

void ASoulslikeCharacter::FinishEquipping()
{
	ActionState = EActionState::EAS_Unoccupied;
}

void ASoulslikeCharacter::HitReactEnd()
{
	ActionState = EActionState::EAS_Unoccupied;
}

void ASoulslikeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ASoulslikeCharacter::Move);
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Completed, this, &ASoulslikeCharacter::MoveEnd);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASoulslikeCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ASoulslikeCharacter::Jump);
		EnhancedInputComponent->BindAction(EKeyAction, ETriggerEvent::Triggered, this, &ASoulslikeCharacter::EKeyPressed);
		EnhancedInputComponent->BindAction(Attack1Action, ETriggerEvent::Triggered, this, &ASoulslikeCharacter::Attack1);
		EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Triggered, this, &ASoulslikeCharacter::Dodge);
		EnhancedInputComponent->BindAction(LockOnAction, ETriggerEvent::Triggered, this, &ASoulslikeCharacter::LockOn);
	}
}

void ASoulslikeCharacter::Jump()
{
	if (IsUnoccupied())
	{
		Super::Jump();
	}
}

void ASoulslikeCharacter::GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter)
{
	if (isInvincible)
	{
		return;
	}

	Super::GetHit_Implementation(ImpactPoint, Hitter);

	SetWeaponCollisionEnabled(ECollisionEnabled::NoCollision);
	if (Attributes && Attributes->GetHealthPercent() > 0.f)
	{
		ActionState = EActionState::EAS_HitReaction;
	}
	
}

float ASoulslikeCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	HandleDamage(DamageAmount);
	SetHUDHealth();
	return DamageAmount;
}

void ASoulslikeCharacter::SetOverlappingItem(AItem* Item)
{
	OverlappingItem = Item;
}

void ASoulslikeCharacter::AddSouls(ASoul* Soul)
{
	if (Attributes && SoulslikeOverlay)
	{
		Attributes->AddSouls(Soul->GetSouls());
		SoulslikeOverlay->SetSoul(Attributes->GetSouls());
	}
}

void ASoulslikeCharacter::AddGolds(ATreasure* Gold)
{
	if (Attributes && SoulslikeOverlay)
	{
		Attributes->AddGolds(Gold->GetGold());
		SoulslikeOverlay->SetGold(Attributes->GetGolds());
	}
}

void ASoulslikeCharacter::SetHUDHealth()
{
	if (SoulslikeOverlay && Attributes)
	{
		SoulslikeOverlay->SetHealthBarPercent(Attributes->GetHealthPercent());
	}
}

void ASoulslikeCharacter::InitializeSoulslikeOverlay()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		ASoulslikeHUD* SoulslikeHUD = Cast<ASoulslikeHUD>(PlayerController->GetHUD());
		if (SoulslikeHUD)
		{
			SoulslikeOverlay = SoulslikeHUD->GetSoulslikeOverlay();
			if (SoulslikeOverlay && Attributes)
			{
				SoulslikeOverlay->SetHealthBarPercent(Attributes->GetHealthPercent());
				SoulslikeOverlay->SetStaminaBarPercent(1.f);
				SoulslikeOverlay->SetGold(0);
				SoulslikeOverlay->SetSoul(0);
			}
		}
	}
}

void ASoulslikeCharacter::SetDodgeDirectionForward()
{
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	DodgeDirection = ForwardDirection;
}

bool ASoulslikeCharacter::IsUnoccupied()
{
	return ActionState == EActionState::EAS_Unoccupied;
}

bool ASoulslikeCharacter::IsDead()
{
	return ActionState == EActionState::EAS_Dead;
}

bool ASoulslikeCharacter::HasEnoughStamina()
{
	return Attributes && Attributes->GetStamina() > Attributes->GetDodgeCost();
}
