#include "MyMainCharacter.h"

#include "HeadMountedDisplayFunctionLibrary.h"

#include "Camera/CameraComponent.h"

#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/PrimitiveComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"

#include "Engine.h"
#include "MyBomb.h"

AMyMainCharacter::AMyMainCharacter()
{
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
}

void AMyMainCharacter::SetupPlayerInputComponent(class UInputComponent* playerInputComponent)
{
    check(playerInputComponent);
    playerInputComponent->BindAction("PlaceBomb", IE_Pressed, this, &AMyMainCharacter::PlaceBomb);

    playerInputComponent->BindAxis("MoveForward", this, &AMyMainCharacter::MoveForward);
    playerInputComponent->BindAxis("MoveRight", this, &AMyMainCharacter::MoveRight);
}

float AMyMainCharacter::TakeDamage(float damageAmount, const FDamageEvent& damageEvent, AController* eventInstigator, AActor* damageCauser)
{
    PlayerHealth -= damageAmount;

    if (PlayerHealth <= 0.f)
    {
        Destroy();
    }
    else
    {
        UGameplayStatics::PlaySound2D(this, DamageSound);
    }

    return damageAmount;
}

void AMyMainCharacter::ApplyPowerUp(PowerUpType type)
{
    switch (type)
    {
        case PowerUpType::SPEED:
        {
            GetWorldTimerManager().ClearTimer(SpeedPowerUpCooldownTimer);
            GetCharacterMovement()->MaxWalkSpeed += 1000;
            GetWorldTimerManager().SetTimer(SpeedPowerUpCooldownTimer, this, &AMyMainCharacter::RevertSpeedPowerUp, PowerUpTime);
        }
        break;
        case PowerUpType::DAMAGE:
        {
            GetWorldTimerManager().ClearTimer(DamagePowerUpCooldownTimer);
            CanSpawnBigBomb = true;
            GetWorldTimerManager().SetTimer(DamagePowerUpCooldownTimer, this, &AMyMainCharacter::RevertDamagePowerUp, PowerUpTime);
        }
        break;
        default:
        {
            //Invalid PowerUpType
            check(false);
        }
        break;
    }
}

bool AMyMainCharacter::IsPowerActive(PowerUpType type)
{
    switch (type)
    {
        case PowerUpType::SPEED:
        {
            return GetWorldTimerManager().IsTimerActive(SpeedPowerUpCooldownTimer);
        }
        break;
        case PowerUpType::DAMAGE:
        {
            return GetWorldTimerManager().IsTimerActive(DamagePowerUpCooldownTimer);
        }
        break;
        default:
        {
            //Invalid PowerUpType
            check(false);
        }
    }
    return false;
}

void AMyMainCharacter::MoveForward(float value)
{
    Move(value, EAxis::X);
}

void AMyMainCharacter::MoveRight(float value)
{
    Move(value, EAxis::Y);
}

void AMyMainCharacter::Move(float value, EAxis::Type axis)
{
    if ((Controller != NULL) && (value != 0.0f))
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(axis);
        AddMovementInput(Direction, value);
    }
}

void AMyMainCharacter::RevertSpeedPowerUp()
{
    GetCharacterMovement()->MaxWalkSpeed -= 1000;
    GetWorldTimerManager().ClearTimer(SpeedPowerUpCooldownTimer);
}

void AMyMainCharacter::RevertDamagePowerUp()
{
    CanSpawnBigBomb = false;
    GetWorldTimerManager().ClearTimer(DamagePowerUpCooldownTimer);
}

void AMyMainCharacter::RestoreBombPlacementCooldown()
{
    BombPlacementCooldownActive = false;
    GetWorldTimerManager().ClearTimer(BombPlacementCooldownTimer);
}

void AMyMainCharacter::PlaceBomb()
{
    UWorld* currentWorld = GetWorld();
    if (BombPlacementCooldownActive == false && currentWorld != nullptr)
    {
        FTransform locationToSpawn = GetActorTransform();
        FVector location = locationToSpawn.GetLocation();
        locationToSpawn.SetLocation(FVector(location.X, location.Y, location.Z + BombZOffset));
        locationToSpawn.SetRotation(FQuat(0, 0, 0, 0));

        FActorSpawnParameters spawnParameters;
        if (CanSpawnBigBomb)
        {
            currentWorld->SpawnActor<AMyBomb>(BoostedBombToSpawn, locationToSpawn, spawnParameters);
            GetWorldTimerManager().ClearTimer(DamagePowerUpCooldownTimer);
            CanSpawnBigBomb = false;
        }
        else
        {
            currentWorld->SpawnActor<AMyBomb>(BombToSpawn, locationToSpawn, spawnParameters);
        }
        BombPlacementCooldownActive = true;
        GetWorldTimerManager().SetTimer(BombPlacementCooldownTimer, this, &AMyMainCharacter::RestoreBombPlacementCooldown, TimeBetweenBoomPlacement);
    }
}