// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBomb.h"

#include "Components/StaticMeshComponent.h"

AMyBomb::AMyBomb()
{
    MyBombMesh = CreateDefaultSubobject<UStaticMeshComponent>("BombMesh");
    SetRootComponent(MyBombMesh);
}

