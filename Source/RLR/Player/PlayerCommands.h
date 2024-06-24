// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include <Kismet/GameplayStatics.h>
#include <EnhancedInputSubsystems.h>
#include "GameFramework/Actor.h"
#include "PlayerCommands.generated.h"



USTRUCT()
struct FSkill
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, Category = Action);
	UInputAction* Q;

	UPROPERTY(EditAnywhere, Category = Action);
	UInputAction* W;

	UPROPERTY(EditAnywhere, Category = Action);
	UInputAction* E;

	UPROPERTY(EditAnywhere, Category = Action);
	UInputAction* R;

	UPROPERTY(EditAnywhere, Category = Action);
	UInputAction* A;

	UPROPERTY(EditAnywhere, Category = Action);
	UInputAction* S;

	UPROPERTY(EditAnywhere, Category = Action);
	UInputAction* D;

	UPROPERTY(EditAnywhere, Category = Action);
	UInputAction* F;

	UPROPERTY(EditAnywhere, Category = Action);
	UInputAction* SPACE;

	UPROPERTY(EditAnywhere, Category = Action);
	UInputAction* Attack;
};

USTRUCT()
struct FUser
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Action);
	UInputAction* I;
	
	UPROPERTY(EditAnywhere, Category = Action);
	UInputAction* O;
	
	UPROPERTY(EditAnywhere, Category = Action);
	UInputAction* P;
	
	UPROPERTY(EditAnywhere, Category = Action);
	UInputAction* J;
	
	UPROPERTY(EditAnywhere, Category = Action);
	UInputAction* K;
	
	UPROPERTY(EditAnywhere, Category = Action);
	UInputAction* L;
	
	UPROPERTY(EditAnywhere, Category = Action);
	UInputAction* N;
	
	UPROPERTY(EditAnywhere, Category = Action);
	UInputAction* M;
	
	UPROPERTY(EditAnywhere, Category = Action);
	UInputAction* G;
	
	UPROPERTY(EditAnywhere, Category = Action);
	UInputAction* U;
	
	UPROPERTY(EditAnywhere, Category = Action);
	UInputAction* F4;
	
	UPROPERTY(EditAnywhere, Category = Action);
	UInputAction* ESC;
};

USTRUCT()
struct FConsume
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Action);
	UInputAction* Num0;
	
	UPROPERTY(EditAnywhere, Category = Action);
	UInputAction* Num1;
	
	UPROPERTY(EditAnywhere, Category = Action);
	UInputAction* Num2;
	
	UPROPERTY(EditAnywhere, Category = Action);
	UInputAction* Num3;
	
	UPROPERTY(EditAnywhere, Category = Action);
	UInputAction* Num4;
	
	UPROPERTY(EditAnywhere, Category = Action);
	UInputAction* Num5;
	
	UPROPERTY(EditAnywhere, Category = Action);
	UInputAction* Num6;
	
	UPROPERTY(EditAnywhere, Category = Action);
	UInputAction* Num7;
	
	UPROPERTY(EditAnywhere, Category = Action);
	UInputAction* Num8;
	
	UPROPERTY(EditAnywhere, Category = Action);
	UInputAction* Num9;
};

UCLASS()
class RLR_API APlayerCommands : public AActor
{
	GENERATED_BODY()

public:
	APlayerCommands();

	void Init();

	UPROPERTY(EditAnywhere, Category = Action);
	FSkill Skill;

	UPROPERTY(EditAnywhere, Category = Action);
	FUser User;

	UPROPERTY(EditAnywhere, Category = Action);
	FConsume Consume;
	
	UPROPERTY(EditAnywhere, Category = Action);
	UInputAction* Move;
};

