// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWidget.h"
#include "MinesweeperGameInstance.h"

#define UNKNOWN_SYMBOL 0x25A1

TSharedRef<SWidget> UMyWidget::RebuildWidget()
{
	int pool_size = Size;

	if (GetWorld()  && GetWorld()->GetGameInstance())
	{
		auto game_instance = Cast< UMinesweeperGameInstance>(GetWorld()->GetGameInstance());

		if (game_instance)
		{
			pool_size = game_instance->GetPoolSize();
		}
	}

	SAssignNew(_game_pool, SSGamePool).Size(pool_size).buttonStyle(&CellStyle);
	_game_pool->_on_gamepool_clicked.AddUObject(this, &UMyWidget::OnButtonClicked);

	return _game_pool.ToSharedRef();
}

void UMyWidget::OnButtonClicked(int x, int y)
{
	if (GetWorld() && GetWorld()->GetGameInstance())
	{
		auto game_instance = Cast< UMinesweeperGameInstance>(GetWorld()->GetGameInstance());
		game_instance->OpenCell(y, x);
	}
}

void UMyWidget::StartGame()
{
	if (GetWorld() && GetWorld()->GetGameInstance())
	{

		auto game_instance = Cast< UMinesweeperGameInstance>(GetWorld()->GetGameInstance());

		if (game_instance)
		{
			game_instance->_new_map_callback.AddUObject(this,&UMyWidget::OnNewMapData);
			game_instance->StartGame();
		}
	}
}

void UMyWidget::OnNewMapData(const FString& data)
{
	TArray<FString> arr;
	data.ParseIntoArray(arr, TEXT("\n"));

	for (int i = 0; i < arr.Num(); i++)
	{
		for (int j = 0; j < arr[i].Len(); j++)
		{
			auto symbol = arr[i][j];

			if (symbol != UNKNOWN_SYMBOL)
			{
				FString text;
				text.AppendChar(symbol);

				if (text == "0")
				{
					text = "";
				}

				_game_pool->DisableCell(i, j, text);
			}
		}
	}
}

void UMyWidget::ReleaseSlateResources(bool bReleaseChildren)
{
	_game_pool.Reset();
}