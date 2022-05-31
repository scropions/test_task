// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "IWebSocket.h"
#include "WebSocketInstance.h"
#include "MinesweeperGameInstance.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnNewMapData, const FString& args)

struct ApplicationSettings
{
	int PoolSize = 10;
};

UCLASS()
class TASKFORCOMP_API UMinesweeperGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	void Init() override;
	void Shutdown() override;

public:
	UFUNCTION(BlueprintCallable)
	void SetPoolSize(int size)
	{
		_app_settings.PoolSize = size;
	}
	UFUNCTION(BlueprintCallable)
	int GetPoolSize()
	{
		UE_LOG(LogTemp, Warning, TEXT("Pool:%i"), _app_settings.PoolSize);
		return _app_settings.PoolSize;
	}

	void OpenCell(int x, int y);
	void StartGame();
public:
	FOnNewMapData _new_map_callback;

private:
	void NewSocketData(const FString& data);
	void ResultCommand(const FString& data);
private:
	TSharedPtr<IWebSocketInstance> _socket_instance;

	ApplicationSettings _app_settings;
};
