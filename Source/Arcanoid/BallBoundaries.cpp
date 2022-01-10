// Fill out your copyright notice in the Description page of Project Settings.


#include "BallBoundaries.h"
#include "Kismet/GameplayStatics.h"
#include "Paddle_PlayerController.h"
#include "Components/BoxComponent.h"

// Sets default values
ABallBoundaries::ABallBoundaries()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box_Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX COLLISION"));
	RootComponent = Box_Collision;
}

// Called when the game starts or when spawned
void ABallBoundaries::BeginPlay()
{
	Super::BeginPlay();
	
	Box_Collision->OnComponentBeginOverlap.AddDynamic(this, &ABallBoundaries::OnOverlapBegin);
	ControllerRef = Cast<APaddle_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void ABallBoundaries::OnOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->ActorHasTag("Ball"))
	{
		OtherActor->Destroy();
		ControllerRef->SpawnBall();
	}
}

// Called every frame
void ABallBoundaries::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

