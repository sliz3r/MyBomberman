// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyBreakableBrick.generated.h"

UCLASS()
class MYBOMBERMAN_API AMyBreakableBrick : public AActor
{
    GENERATED_BODY()

    /** Brick Mesh */
    UPROPERTY(EditAnywhere, Category = "Components")
    UStaticMeshComponent* MyBreakableBrickMesh;

public:
    AMyBreakableBrick();

    virtual float TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;
};
