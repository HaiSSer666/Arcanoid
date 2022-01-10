// Fill out your copyright notice in the Description page of Project Settings.


#include "Paddle_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"
#include "Engine/World.h"
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"

APaddle_PlayerController::APaddle_PlayerController()
{
}

void APaddle_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	EnableInput(this);
	InputComponent->BindAxis("MoveRight", this, &APaddle_PlayerController::MoveHorizontal);
	InputComponent->BindAction("Launch", IE_Pressed, this, &APaddle_PlayerController::Launch);
}

void APaddle_PlayerController::BeginPlay()
{
	TArray<AActor*> Cameras;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), Cameras);

	FViewTargetTransitionParams Params;
	SetViewTarget(Cameras[0], Params);

	MyPawn = Cast<APaddle>(GetPawn());

	SpawnBall();
	SpawnBrickWall();
}

void APaddle_PlayerController::MoveHorizontal(float AxisValue)
{
	if (MyPawn)
	{
		MyPawn->MoveHorizontal(AxisValue);
	}
}

void APaddle_PlayerController::Launch()
{
	MyBall->Launch();
}

void APaddle_PlayerController::SpawnBall()
{
	if (!MyBall)
		MyBall = nullptr;

	if (BallObj)
	{
		SpawnLocation = FVector(0.0f, 0.0f, 50.0f);
		SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
		MyBall = GetWorld()->SpawnActor<ABall>(BallObj, SpawnLocation, SpawnRotation, SpawnParam);
	}
}

void APaddle_PlayerController::SpawnBrickWall()
{
	float xSpawn = -125.0f;
	float zSpawn = 350.0f;
	int nIndex = -1;
	UClass* Brick;

	FVector BrickSpawnLocation = FVector(xSpawn, 0.0f, zSpawn);

	if (BrickArray.Num())
	{
		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 6; j++)
			{
				nIndex = FMath::RandRange(0, BrickArray.Num() - 1);
				Brick = BrickArray[nIndex];
				MyBrick = GetWorld()->SpawnActor<ABrick>(Brick, BrickSpawnLocation, SpawnRotation, SpawnParam);
				xSpawn += 50.0f;
				BrickSpawnLocation = FVector(xSpawn, 0.0f, zSpawn);
			}
			xSpawn = -125.0f;
			zSpawn -= 20.f;
			BrickSpawnLocation = FVector(xSpawn, 0.0f, zSpawn);
		}
	}
}
