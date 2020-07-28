// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBombermanCharacter.h"

#include "HeadMountedDisplayFunctionLibrary.h"

#include "Camera/CameraComponent.h"

#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

#include "MyBomb.h"

AMyBombermanCharacter::AMyBombermanCharacter()
{
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
}

void AMyBombermanCharacter::SetupPlayerInputComponent(class UInputComponent* playerInputComponent)
{
    check(playerInputComponent);
    playerInputComponent->BindAction("PlaceBomb", IE_Pressed, this, &AMyBombermanCharacter::PlaceBomb);

    playerInputComponent->BindAxis("MoveForward", this, &AMyBombermanCharacter::MoveForward);
    playerInputComponent->BindAxis("MoveRight", this, &AMyBombermanCharacter::MoveRight);
}

float AMyBombermanCharacter::TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    Destroy();
    return DamageAmount;
}

void AMyBombermanCharacter::MoveForward(float value)
{
    Move(value, EAxis::X);
}

void AMyBombermanCharacter::MoveRight(float value)
{
    Move(value, EAxis::Y);
}

void AMyBombermanCharacter::Move(float value, EAxis::Type axis)
{
    if ((Controller != NULL) && (value != 0.0f))
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(axis);
        AddMovementInput(Direction, value);
    }
}

void AMyBombermanCharacter::PlaceBomb()
{
    if (UWorld* currentWorld = GetWorld())
    {
        FTransform locationToSpawn = GetActorTransform();
        FVector location = locationToSpawn.GetLocation();
        locationToSpawn.SetLocation(FVector(location.X, location.Y, location.Z + BombZOffset));
        locationToSpawn.SetRotation(FQuat(0,0,0,0));

        FActorSpawnParameters spawnParameters;
        currentWorld->SpawnActor<AMyBomb>(BombToSpawn, locationToSpawn, spawnParameters);
    }
}