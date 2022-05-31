// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "SSGamePool.h"
#include "MyWidget.generated.h"

UCLASS()
class TASKFORCOMP_API UMyWidget : public UWidget
{
	GENERATED_BODY()
protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
public:
	UPROPERTY(EditAnywhere, Category = MyWidget, BlueprintReadWrite)
	int Size;

	UPROPERTY(EditAnywhere, Category = MyWidget)
	FButtonStyle CellStyle;

	UFUNCTION()
	void OnButtonClicked(int x, int y);

	UFUNCTION(BlueprintCallable)
	void StartGame();
private:
	void ReleaseSlateResources(bool bReleaseChildren) override;

	void OnNewMapData(const FString& data);
private:
	TSharedPtr<SSGamePool> _game_pool;

};
