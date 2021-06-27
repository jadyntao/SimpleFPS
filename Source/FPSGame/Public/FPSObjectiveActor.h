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
	UPROPERTY(VisibleAnywhere,Category="Components")//���乫����������ͼ��C++���ܱ༭
	UStaticMeshComponent* MeshComp;//���������

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* SphereComp;//��������������ڽ���������ײ��Ϣ

	UPROPERTY(EditDefaultsOnly,Category="Effects")//���༭Ĭ��
	UParticleSystem* PickupFX;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void PlayEffects();

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	//ͨ����AActor�ఴalt+G�ҵ���Դ���룬crtl+F����������غ��������ƻؼ̳�����к�������
	//�ڷ����ص�ʱ֪ͨActor����
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
};
