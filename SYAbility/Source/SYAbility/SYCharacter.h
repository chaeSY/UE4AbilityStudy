// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "SYCharacter.generated.h"

class UAbilitySystemComponent;
class UGameplayAbility;
class UGameplayEffect;
class USYAttributeSet;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChanged, int32, DeltaAttribute);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDamaged, int32, DamageAmount, AActor*, DamageCauser);

UCLASS()
class SYABILITY_API ASYCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASYCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;
	// IAbilitySystemInterface는 GetAbilitySystemComponent 상속을 강제함
	// AbilitySystemComponent로 Interface의 기능을 사용할 수 있음

public:
	void UpdateHUD() const;

//attribute
public:
	UFUNCTION(BlueprintPure)
	float GetHealth() const;

	UFUNCTION(BlueprintPure)
	float GetMaxHealth() const;

	UFUNCTION(BlueprintPure)
	float GetStamina() const;

	UFUNCTION(BlueprintPure)
	float GetMaxStamina() const;

	void HandleChangedHealth(float DeltaHealth);
	void HandleChangedStamina(float DeltaStamina);
	void HandleDamage(float DamageAmount, AActor* DamageCauser);

	UPROPERTY(Category = "SYAttribute", BlueprintAssignable, BlueprintCallable)
	FOnAttributeChanged OnChangedHealth;

	UPROPERTY(Category = "SYAttribute", BlueprintAssignable, BlueprintCallable)
	FOnAttributeChanged OnChangedStamina;

	UPROPERTY(Category = "SYAttribute", BlueprintAssignable, BlueprintCallable)
	FOnDamaged OnDamaged;

private:
	UPROPERTY()
	const class USYAttributeSet* AttributeSet;

//ability
public:
	UFUNCTION(BlueprintCallable)
	void CancelAbility();

private:
	void InitAbility();
	void GrantAbility(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level, int32 InputCode);

private:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UGameplayAbility>> AbilityClasses;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UGameplayEffect>> PassiveAbilityEffects;

};
