// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Brick.generated.h"

class APaddle_PlayerController;
class UBoxComponent;

UCLASS()
class ABrick : public AActor
{
	GENERATED_BODY()

	enum BrickColor 
	{
		BrickColor_BLUE = 1,
		BrickColor_GREEN = 2,
		BrickColor_RED = 3
	};

public:
	// Sets default values for this actor's properties
	ABrick();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		int HitsToBreak;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* SM_Brick;

	UPROPERTY(EditAnywhere)
		UMaterialInstance* MaterialRed;
	UPROPERTY(EditAnywhere)
		UMaterialInstance* MaterialGreen;
	UPROPERTY(EditAnywhere)
		UMaterialInstance* MaterialBlue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UBoxComponent* Box_Collision;

	float SpeedModifierOnBounce;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndexType, bool bFromSweep,
			const FHitResult& SweepResult);

	APaddle_PlayerController* ControllerRef;

	void DestroyBrick();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
