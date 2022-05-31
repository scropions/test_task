// Fill out your copyright notice in the Description page of Project Settings.


#include "SSGamePool.h"
#include "SlateOptMacros.h"
#include "MyWidget.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSGamePool::Construct(const FArguments& InArgs)
{	
	TSharedPtr<SVerticalBox> VerticalBox = SNew(SVerticalBox);

	for (int i = 0; i < InArgs._Size; i++)
	{
		_cells.Add(TArray<Cell>());
	}

	for (int i = 0; i < InArgs._Size; i++)
	{
		TSharedPtr<SHorizontalBox> HorizontalBox = SNew(SHorizontalBox);

		for (int j = 0; j < InArgs._Size; j++)
		{
			Cell cell;
			cell._button = SNew(SButton).OnClicked(this, &SSGamePool::ButtonClicked, i, j).ButtonStyle(InArgs._buttonStyle).VAlign(EVerticalAlignment::VAlign_Center).HAlign(EHorizontalAlignment::HAlign_Center);
			cell._text_block = SNew(STextBlock).ColorAndOpacity(FSlateColor(FColor::Black));
			_cells[i].Add(cell);
			cell._button->SetContent(_cells[i][j]._text_block.ToSharedRef());

			HorizontalBox->AddSlot()
				[
					_cells[i][j]._button.ToSharedRef()
				];
		}

		VerticalBox->AddSlot()[
			HorizontalBox.ToSharedRef()
		];
	
	}
	
	TSharedPtr<SBorder> Container = SNew(SBorder).BorderBackgroundColor(FSlateColor(FLinearColor::Black))
		[
			VerticalBox.ToSharedRef()
		];
	
	
	ChildSlot
	[
			Container.ToSharedRef()
	];
	
}

FReply SSGamePool::ButtonClicked(int x, int y)
{
	_on_gamepool_clicked.Broadcast(x, y);
	_cells[x][y]._button->SetEnabled(false);

	return FReply::Handled();
}

void SSGamePool::DisableCell(int x, int y, const FString& text)
{
	_cells[x][y]._button->SetEnabled(false);
	_cells[x][y]._text_block->SetText(FText::FromString(text));
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

