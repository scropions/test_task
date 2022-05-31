// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IWebSocket.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnReciveSocketData, const FString& data)

class TASKFORCOMP_API IWebSocketInstance
{
public:
	IWebSocketInstance() = delete;
	IWebSocketInstance(const FString& address);
	~IWebSocketInstance();
	void SendData(const FString& command);
	FOnReciveSocketData _recive_data_callback;

private:
	TSharedPtr<IWebSocket> _socket;

};
