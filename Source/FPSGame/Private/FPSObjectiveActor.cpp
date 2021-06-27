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

	//实例化MeshComp,创建默认子对象，类型为UStaticMeshComponent，名字为MeshComp
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	//设置为无碰撞
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//将网格体组件设成为根组件
	RootComponent = MeshComp;

	//实例化SphereComp,创建默认子对象，类型为USphereComponent，名字为SphereComp
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	//将碰撞设置为仅查询
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//将碰撞设置为相应所有通道，并选择ECR_Ignore忽略
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	//将碰撞设置为对ECC_Pawn人形体的通道响应,这样的话就不会对发射子弹进行响应，就会直接穿过对象
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
	//将球体组件附加在网格体组件上
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
	//SpawnEmitterAtLocation(在原处生成发射器)，SpawnEmitterAttached(生成附加发射器)
	//第一个变量是WorldContextObject(世界场景上下文对象),它指的是世界场景中任何类型的Actor
	//第二个变量是EmitterTemplate(发射器模板)
	//第三个变量是位置，因为需求是在原处生成效果，所以选择GetActorLocation(获取Actor位置)
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
	//保证基类的实现不变，再在该函数后添加自定义的函数内容
	Super::NotifyActorBeginOverlap(OtherActor);

	//自定义函数，角色靠近物体时，物体产生PickupFX发射器特效
	PlayEffects();

	//将重叠的OtherActor(定义时已经过过滤，人形体类型）强制转换成AFPSCharacter(角色类型)
	AFPSCharacter* MyCharacter = Cast<AFPSCharacter>(OtherActor);
	if (MyCharacter) 
	{
		MyCharacter->bIsCarryingObjective = true;

		//调用自毁函数，将物体毁灭，实现不被其他玩家重复拾起
		Destroy();
	}
}

