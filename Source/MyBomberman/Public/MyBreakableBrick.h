// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyBreakableBrick.generated.h"

UCLASS()
class MYBOMBERMAN_API AMyBreakableBrick : public AActor
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = "Components")
    UStaticMeshComponent* MyBreakableBrickMesh;

public:
    AMyBreakableBrick();

protected:
    virtual void BeginPlay() override;

public:
    virtual float TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;
};
