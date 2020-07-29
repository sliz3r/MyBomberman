// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBreakableBrick.h"

AMyBreakableBrick::AMyBreakableBrick()
{
    MyBreakableBrickMesh = CreateDefaultSubobject<UStaticMeshComponent>("BreakableBrickMesh");
    SetRootComponent(MyBreakableBrickMesh);
}

float AMyBreakableBrick::TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    Destroy();
    return DamageAmount;
}

