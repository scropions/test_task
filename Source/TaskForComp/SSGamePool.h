#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FGamePoolClicked, int, int)

struct Cell
{
	TSharedPtr<SButton> _button;
	TSharedPtr<STextBlock> _text_block;
};

class TASKFORCOMP_API SSGamePool : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSGamePool)
	{}
	SLATE_ARGUMENT(int, Size)
	SLATE_ARGUMENT(FButtonStyle*, buttonStyle)
	SLATE_ARGUMENT(FGamePoolClicked, OnButtonClicked)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	void DisableCell(int x, int y, const FString& text);

	FGamePoolClicked _on_gamepool_clicked;
private:
	FReply ButtonClicked(int x, int y);

private:
	TArray<TArray<Cell>> _cells;

};
