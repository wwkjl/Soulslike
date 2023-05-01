#pragma once


UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	ECS_Unequipped UMETA(DisplayName = "Unequipped"),
	ECS_EquippedOneHandedWeapon UMETA(DisplayName = "Equipped One-Handed Weapon"),
	ECS_EquippedTwoHandedWeapon UMETA(DisplayName = "Equipped Two-Handed Weapon"),
};

UENUM(BlueprintType)
enum class EActionState : uint8
{
	EAS_Unoccupied UMETA(DisplayName = "Unoccupied"),
	EAS_HitReaction UMETA(DisplayName = "HitReaction"),
	EAS_Attacking UMETA(DisplayName = "Attacking"),
	EAS_EquippingWeapon UMETA(DisplayName = "EquippingWeapon"),
	EAS_Dodge UMETA(DisplayName = "Dodge"),
	EAS_Dead UMETA(DisplayName = "Dead"),
};

UENUM(BlueprintType)
enum EDeathPose
{
	EDP_DeathBackFall UMETA(DisplayName = "Death Back Fall"),
	EDP_DeathForwardFall UMETA(DisplayName = "Death Forward Fall"),
	EDP_DeathBackFly UMETA(DisplayName = "Death Back Fly"),
	EDP_DeathRightFall UMETA(DisplayName = "Death Right Fall"),

	EDP_Max UMETA(DisplayName = "DefaultMax")
};

UENUM(BlueprintType)
enum class EEnemyState : uint8	//More Serious
{
	EES_NoState UMETA(DisplayName = "NoState"),

	EES_Dead UMETA(DisplayName = "Dead"),
	EES_Patrolling UMETA(DisplayName = "Patrolling"),
	EES_Chasing UMETA(DisplayName = "Chasing"),
	EES_Attacking UMETA(DisplayName = "Attacking"),
	EES_Engaged UMETA(DisplayName = "Engaged"),

};