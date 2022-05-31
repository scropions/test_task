// Fill out your copyright notice in the Description page of Project Settings.


#include "MinesweeperGameInstance.h"
#include "WebSocketsModule.h"

void UMinesweeperGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("GameStarted"));
	_socket_instance = MakeShareable(new IWebSocketInstance("wss://hometask.eg1236.com/game1/"));
	_socket_instance->_recive_data_callback.AddUObject(this, &UMinesweeperGameInstance::NewSocketData);
}

void UMinesweeperGameInstance::Shutdown()
{

}

void UMinesweeperGameInstance::OpenCell(int x, int y)
{
	FString command = "open " + FString::FromInt(x) + " " + FString::FromInt(y);
	_socket_instance->SendData(command);

	command = "map";
	_socket_instance->SendData(command);
}

void UMinesweeperGameInstance::StartGame()
{
	const FString command = "new " + FString::FromInt(_app_settings.PoolSize/10);
	_socket_instance->SendData(command);
}

void UMinesweeperGameInstance::NewSocketData(const FString& data)
{
	FString spliter = ":";
	FString command;
	FString string_args;
	data.Split(spliter, &command, &string_args);
	
	if (string_args.Len() < 1)
	{
		return;
	}

	FString space = &string_args[0];

	if (string_args.Len() > 0 || space == " ")
	{
		string_args.RemoveAt(0);
	}

	if (command == TEXT("map"))
	{
		_new_map_callback.Broadcast(string_args);
	}
	else
	{
		ResultCommand(string_args);
	}

}

void UMinesweeperGameInstance::ResultCommand(const FString& data)
{
	if (data == TEXT("You lose"))
	{
		exit(0);
	}
}

