// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WindowsIPCControls.h"
#include "TestController.generated.h"

class TestQueueManager {
private:
	AActor* parent;
	bool currentTestStarted = false;
	TQueue<AActor*> testQueue;
	FString activeTest = "None";

	void startActiveTest();
	bool isActiveTestDone();
public:
	bool testsStarted = false;
	TestQueueManager(AActor* parent_in);
	AActor* getTest(FString testNameContains);
	void queueTests(UINT16 mess_in);
	void stopAllTests();
	void tick();

};

UCLASS()
class CS425PROJECT_API ATestController : public AActor
{
	GENERATED_BODY()
private:
	IPCCreator* ipcController;
	FTimerHandle ipcTimerHandle;
	void ipcTimerTick();
	void handleMessage(UINT16 mess);
	bool testsStarted = false;
	TestQueueManager* testManager;
public:	
	// Sets default values for this actor's properties
	ATestController();
	void SignalUITestsDone();
	void SignalUISingleTestStarted(UINT16 mess);
	void SignalUISingleTestDone(UINT16 mess);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
