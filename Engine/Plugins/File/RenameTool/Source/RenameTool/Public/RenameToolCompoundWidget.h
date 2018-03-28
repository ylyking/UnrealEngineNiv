// Copyright 2018 BruceLee, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "RenameToolUISetting.h"
#include "RenameToolHelper.h"
#include "Layout/Visibility.h"
#include "Input/Reply.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SWidget.h"
#include "Widgets/SCompoundWidget.h"

class SRenameToolCompoundWidget :public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SRenameToolCompoundWidget)
	{}
	SLATE_END_ARGS()
	SRenameToolCompoundWidget();
	~SRenameToolCompoundWidget();


	void Construct(const FArguments& InArgs);
protected:
	
private:

	//WidgetVisibility
	EVisibility GetVisibilityAddFix()const;
	EVisibility GetVisibilityRename()const;
	EVisibility GetVisibilityReplace()const;
	EVisibility GetVisibilityCase()const;

	FRenameToolHelper RenameToolHelper;

	FRenameToolUISetting RenameToolUISetting;

	TSharedPtr<FUICommandList> RenameToolBarUICommandList;

	TSharedRef<SWidget> BuildToolBar();

	FText GetActiveToolName() const;

	FReply ButtonConfirm(ERenameAction NewRenameAction);

	void PrefixInputChanged(const FText& NewText);
	void SuffixInputChanged(const FText& NewText);
	void NameInputChanged(const FText& NewText);
	void StartNumberInputChanged(const FText& NewText);
	void FindStrInputChanged(const FText& NewText);
	void TargetStrInputChanged(const FText& NewText);

	void SetChangeAsset(ECheckBoxState InState);
	void SetChangeActor(ECheckBoxState InState);

	ECheckBoxState CanChangeAsset()const;
	ECheckBoxState CanChangeActor()const;


	void Init();
	void CommandsInit();
	void UISettingInit();

	
};