// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSObjectiveActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FPSCharacter.h"


// Sets default values
AFPSObjectiveActor::AFPSObjectiveActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	//ʵ����MeshComp,����Ĭ���Ӷ�������ΪUStaticMeshComponent������ΪMeshComp
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	//����Ϊ����ײ
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//��������������Ϊ�����
	RootComponent = MeshComp;

	//ʵ����SphereComp,����Ĭ���Ӷ�������ΪUSphereComponent������ΪSphereComp
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	//����ײ����Ϊ����ѯ
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//����ײ����Ϊ��Ӧ����ͨ������ѡ��ECR_Ignore����
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	//����ײ����Ϊ��ECC_Pawn�������ͨ����Ӧ,�����Ļ��Ͳ���Է����ӵ�������Ӧ���ͻ�ֱ�Ӵ�������
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
	//��������������������������
	SphereComp->SetupAttachment(MeshComp);
}

// Called when the game starts or when spawned
void AFPSObjectiveActor::BeginPlay()
{
	Super::BeginPlay();
	PlayEffects();
}

void AFPSObjectiveActor::PlayEffects()
{
	//SpawnEmitterAtLocation(��ԭ�����ɷ�����)��SpawnEmitterAttached(���ɸ��ӷ�����)
	//��һ��������WorldContextObject(���糡�������Ķ���),��ָ�������糡�����κ����͵�Actor
	//�ڶ���������EmitterTemplate(������ģ��)
	//������������λ�ã���Ϊ��������ԭ������Ч��������ѡ��GetActorLocation(��ȡActorλ��)
	UGameplayStatics::SpawnEmitterAtLocation(this, PickupFX, GetActorLocation());
}

// Called every frame
/*
void AFPSObjectiveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
*/

void AFPSObjectiveActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	//��֤�����ʵ�ֲ��䣬���ڸú���������Զ���ĺ�������
	Super::NotifyActorBeginOverlap(OtherActor);

	//�Զ��庯������ɫ��������ʱ���������PickupFX��������Ч
	PlayEffects();

	//���ص���OtherActor(����ʱ�Ѿ������ˣ����������ͣ�ǿ��ת����AFPSCharacter(��ɫ����)
	AFPSCharacter* MyCharacter = Cast<AFPSCharacter>(OtherActor);
	if (MyCharacter) 
	{
		MyCharacter->bIsCarryingObjective = true;

		//�����Իٺ��������������ʵ�ֲ�����������ظ�ʰ��
		Destroy();
	}
}

