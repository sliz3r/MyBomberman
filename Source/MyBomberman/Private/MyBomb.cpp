// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBomb.h"

#include "Components/StaticMeshComponent.h"

AMyBomb::AMyBomb()
{
    MyBombMesh = CreateDefaultSubobject<UStaticMeshComponent>("BombMesh");
    SetRootComponent(MyBombMesh);
}

void AMyBomb::Explode()
{
    Destroy();
}

void AMyBomb::BeginPlay()
{
    Super::BeginPlay();

    FTimerHandle ExplodeTimer;
    GetWorldTimerManager().SetTimer(ExplodeTimer, this, &AMyBomb::Explode, ExplosionDelay);
}
