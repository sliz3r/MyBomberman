// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "MyPowerUpTriggerBox.generated.h"

UENUM(BlueprintType)
enum class PowerUpType : uint8
{
    SPEED = 0 UMETA(DisplayName = "Speed Boost"),
    DAMAGE = 1 UMETA(DisplayName = "Damage Boost")
};

UCLASS()
class MYBOMBERMAN_API AMyPowerUpTriggerBox : public ATriggerBox
{
    GENERATED_BODY()

    /** PowerUp Type */
    UPROPERTY(EditAnywhere, Category = "Power Up")
    PowerUpType PowerUpType;

public:
    AMyPowerUpTriggerBox();

    UFUNCTION()
    void OnOverlapBegin(class AActor* overlappedActor, class AActor* otherActor);
};
