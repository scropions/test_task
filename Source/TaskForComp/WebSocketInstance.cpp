// Fill out your copyright notice in the Description page of Project Settings.


#include "WebSocketInstance.h"
#include "WebSocketsModule.h"

IWebSocketInstance::IWebSocketInstance(const FString& address)
{
	if (!FModuleManager::Get().IsModuleLoaded("WebSockets"))
	{
		FModuleManager::Get().LoadModule("WebSockets");

	}

	_socket = FWebSocketsModule::Get().CreateWebSocket(address);
	
	_socket->OnMessage().AddLambda([this](const FString& message)
		{
			_recive_data_callback.Broadcast(message);
		});

	_socket->OnConnectionError().AddLambda([this](const FString& message)
		{
			UE_LOG(LogTemp, Warning, TEXT("Connection error"));
		});

	_socket->Connect();
}

IWebSocketInstance::~IWebSocketInstance()
{
	if (_socket->IsConnected())
	{
		_socket->Close();
	}
}

void IWebSocketInstance::SendData(const FString& command)
{
	_socket->Send(command);
}