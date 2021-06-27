// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSObjectiveActor.generated.h"

class USphereComponent;

UCLASS()
class FPSGAME_API AFPSObjectiveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSObjectiveActor();

protected:
	UPROPERTY(VisibleAnywhere,Category="Components")//将其公开，这样蓝图或C++都能编辑
	UStaticMeshComponent* MeshComp;//网格体组件

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* SphereComp;//球体组件，可用于接纳物体碰撞信息

	UPROPERTY(EditDefaultsOnly,Category="Effects")//仅编辑默认
	UParticleSystem* PickupFX;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void PlayEffects();

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	//通过对AActor类按alt+G找到其源代码，crtl+F搜索到其相关函数，复制回继承类进行函数重载
	//在发生重叠时通知Actor函数
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
};
