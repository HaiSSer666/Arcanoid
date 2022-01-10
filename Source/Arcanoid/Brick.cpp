// Fill out your copyright notice in the Description page of Project Settings.


#include "Brick.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Paddle_PlayerController.h"
#include "Ball.h"

// Sets default values
ABrick::ABrick()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SM_Brick = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Brick"));
	SM_Brick->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RootComponent = SM_Brick;

	Box_Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	Box_Collision->SetBoxExtent(FVector(25.0f, 10.0f, 10.0f));
	Box_Collision->AttachTo(RootComponent);	

	SpeedModifierOnBounce = 1.05f;
}

// Called when the game starts or when spawned
void ABrick::BeginPlay()
{
	Super::BeginPlay();

	Box_Collision->OnComponentBeginOverlap.AddDynamic(this, &ABrick::OnOverlapBegin);
	ControllerRef = Cast<APaddle_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

// Called every frame
void ABrick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABrick::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor,
	UPrimitiveComponent * OtherComp, int32 OtherBodyIndexType, bool bFromSweep,
	const FHitResult & SweepResult)
{
	if (OtherActor->ActorHasTag("Ball")) {

		ABall* MyBall = Cast<ABall>(OtherActor);

		FVector BallVelocity = MyBall->GetVelocity();
		BallVelocity *= (SpeedModifierOnBounce - 1.0f);

		MyBall->GetBall()->SetPhysicsLinearVelocity(BallVelocity, true);

		HitsToBreak--;
		if (!HitsToBreak)
		{
			FTimerHandle UnusedHandle;
			GetWorldTimerManager().SetTimer(UnusedHandle, this, &ABrick::DestroyBrick, 0.1f, false);
		}
		else
		{
			switch (HitsToBreak)
			{
			case 1:
				SM_Brick->SetMaterial(0, MaterialBlue);
				break;
			case 2:
				SM_Brick->SetMaterial(0, MaterialGreen);
				break;
			case 3:
				SM_Brick->SetMaterial(0, MaterialRed);
				break;
			default:
				break;
			}
		}
	}
}

void ABrick::DestroyBrick()
{
	this->Destroy();
}

