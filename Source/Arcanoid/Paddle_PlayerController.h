// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Paddle_PlayerController.generated.h"

class APaddle;
class ABall;
class ABrick;

/**
 * 
 */
UCLASS()
class ARCANOID_API APaddle_PlayerController : public APlayerController
{
	GENERATED_BODY()

	APaddle_PlayerController();

	UFUNCTION()
	virtual void SetupInputComponent() override;

protected:
	virtual void BeginPlay() override;
	void MoveHorizontal(float AxisValue);
	void Launch();

	APaddle* MyPawn;
	ABall* MyBall;
	ABrick* MyBrick;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ABall> BallObj;
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<ABrick>> BrickArray;

	FVector SpawnLocation;
	FRotator SpawnRotation;
	FActorSpawnParameters SpawnParam;

public:
	void SpawnBall();
	void SpawnBrickWall();
};
