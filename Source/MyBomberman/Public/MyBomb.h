// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyBomb.generated.h"

UCLASS()
class MYBOMBERMAN_API AMyBomb : public AActor
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = "Components")
    UStaticMeshComponent* MyBombMesh;

public:
    AMyBomb();
};
