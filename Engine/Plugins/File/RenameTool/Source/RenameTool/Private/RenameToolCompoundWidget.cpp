// Copyright 2018 BruceLee, Inc. All Rights Reserved.
#include "RenameToolCompoundWidget.h"
#include "RenameToolEdStyle.h"
#include "RenameCommands.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "SlateOptMacros.h"

#define LOCTEXT_NAMESPACE "RenameToolCompoundWidget"
SRenameToolCompoundWidget::SRenameToolCompoundWidget()
	:RenameToolHelper(FRenameToolHelper::FRenameToolHelper())
{
	Init();
}

SRenameToolCompoundWidget::~SRenameToolCompoundWidget()
{
	RenameToolUISetting.Save();
}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SRenameToolCompoundWidget::Construct(const FArguments& InArgs)
{
	FMargin StandardPadding(6.f, 3.f);
	FMargin StandardUpDownPadding(6.f, 8.f);
	FMargin StandardLeftPadding(6.f, 3.f, 3.f, 3.f);
	FMargin StandardRightPadding(3.f, 3.f, 6.f, 3.f);

	FSlateFontInfo StandardFont = FEditorStyle::GetFontStyle(TEXT("PropertyWindow.NormalFont"));
	const FText BlankText = LOCTEXT("Blank", "");

	this->ChildSlot
	[
		SNew(SVerticalBox)

		+ SVerticalBox::Slot()
		.FillHeight(1.f)
		[
			SNew(SHorizontalBox)
#pragma region ToolBar
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.Padding(1.f, 5.f, 0.f, 5.f)
			[
				BuildToolBar()
			]
#pragma endregion ToolBar
#pragma region Content
			+ SHorizontalBox::Slot()
			.Padding(0.f, 2.f, 2.f, 0.f)
			[
				SNew(SBorder)
				.BorderImage(FEditorStyle::GetBrush("ToolPanel.DarkGroupBorder"))
				.Padding(StandardPadding)
				[
					SNew(SVerticalBox)
				#pragma region Header
					+ SVerticalBox::Slot()
					.AutoHeight()
					.Padding(StandardUpDownPadding)
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					[
					SNew(SHeader)
					[
						SNew(STextBlock)
						.Text(this, &SRenameToolCompoundWidget::GetActiveToolName)
						.TextStyle(FRenameToolEditStyle::Get(), "RenameToolEdMode.Text")
					]
				]
				#pragma endregion Header	
				#pragma region AddFix
					+ SVerticalBox::Slot()
					.Padding(StandardUpDownPadding)
					.FillHeight(1.f)
					[
						SNew(SVerticalBox)
						.Visibility(this,&SRenameToolCompoundWidget::GetVisibilityAddFix)
					#pragma region Prefix
						
						+ SVerticalBox::Slot()
						.AutoHeight()
						.Padding(StandardPadding)
						.HAlign(HAlign_Fill)
						[
							SNew(SHorizontalBox)

						#pragma region PrefixText
							+SHorizontalBox::Slot()
							.FillWidth(0.2f)
							.HAlign(HAlign_Right)
							.Padding(StandardRightPadding)
							[
								SNew(STextBlock)
								.Text(LOCTEXT("RenameToolEd.Prefix", "Prefix"))
								.TextStyle(FRenameToolEditStyle::Get(), "RenameToolEdMode.Text")
							]
						#pragma endregion PrefixText

						#pragma region PrefixInput
							+SHorizontalBox::Slot()
							.FillWidth(0.8f)
							.HAlign(HAlign_Fill)
							.Padding(StandardLeftPadding)
							[
								SNew(SEditableTextBox)
								.Style(FRenameToolEditStyle::Get(), "NormalEditableTextBoxStyle")
								.ToolTipText(LOCTEXT("RenameToolEd.PrefixInput", "Please Enter The Prefix Here"))
								.HintText(LOCTEXT("RenameToolEd.PrefixInput", "Please Enter The Prefix Here"))
								.SelectAllTextWhenFocused(true)
								.OnTextChanged(this, &SRenameToolCompoundWidget::PrefixInputChanged)
							]
						#pragma endregion PrefixInput

						]
					#pragma endregion Prefix
					#pragma region Suffix
						
						+ SVerticalBox::Slot()
						.AutoHeight()
						.Padding(StandardPadding)
						.HAlign(HAlign_Fill)
						[
							SNew(SHorizontalBox)

						#pragma region SuffixText
							+SHorizontalBox::Slot()
							.FillWidth(0.2f)
							.HAlign(HAlign_Right)
							.Padding(StandardRightPadding)
							[
								SNew(STextBlock)
								.Text(LOCTEXT("RenameToolEd.Suffix", "Suffix"))
								.TextStyle(FRenameToolEditStyle::Get(), "RenameToolEdMode.Text")
							]
						#pragma endregion SuffixText

						#pragma region SuffixInput
							+SHorizontalBox::Slot()
							.FillWidth(0.8f)
							.HAlign(HAlign_Fill)
							.Padding(StandardLeftPadding)
							[
								SNew(SEditableTextBox)
								.Style(FRenameToolEditStyle::Get(), "NormalEditableTextBoxStyle")
								.ToolTipText(LOCTEXT("RenameToolEd.SuffixInput", "Please Enter The Suffix Here"))
								.HintText(LOCTEXT("RenameToolEd.SuffixInput", "Please Enter The Suffix Here"))
								.SelectAllTextWhenFocused(true)
								.OnTextChanged(this, &SRenameToolCompoundWidget::SuffixInputChanged)
							]
						#pragma endregion SuffixInput

						]
					#pragma endregion Suffix
					#pragma region Asset/Actor CheckBox
						+ SVerticalBox::Slot()
						.AutoHeight()
						.Padding(StandardPadding)
						.HAlign(HAlign_Fill)
						[
							SNew(SHorizontalBox)

						#pragma region Asset
							//Check Box
							+ SHorizontalBox::Slot()
							.FillWidth(1.f)
							.HAlign(HAlign_Right)
							.Padding(StandardPadding)
							[
								SNew(SCheckBox)
								.OnCheckStateChanged(this,&SRenameToolCompoundWidget::SetChangeAsset)
								.IsChecked(this,&SRenameToolCompoundWidget::CanChangeAsset)
								[
									SNew(STextBlock)
									.Text(LOCTEXT("RenameToolEd.Asset", "Asset"))
									.TextStyle(FRenameToolEditStyle::Get(), "RenameToolEdMode.Text")
								]
							]
						#pragma endregion Asset
						#pragma region Actor
							//Check Box
							+ SHorizontalBox::Slot()
							.FillWidth(1.f)
							.HAlign(HAlign_Left)
							.Padding(StandardPadding)
							[
								SNew(SCheckBox)
								.OnCheckStateChanged(this,&SRenameToolCompoundWidget::SetChangeActor)
								.IsChecked(this, &SRenameToolCompoundWidget::CanChangeActor)
								[
									SNew(STextBlock)
									.Text(LOCTEXT("RenameToolEd.Actor", "Actor"))
									.TextStyle(FRenameToolEditStyle::Get(), "RenameToolEdMode.Text")
								]
							]
						#pragma endregion Actor

						]
					#pragma endregion Asset/Actor CheckBox
					#pragma region ConfimButton
						+SVerticalBox::Slot()
						.AutoHeight()
						.Padding(StandardUpDownPadding)
						.HAlign(HAlign_Right)
						[
							SNew(SButton)
							.ButtonStyle(FRenameToolEditStyle::Get(),"Button")
							.Text(LOCTEXT("RenameToolEd.Confirm","Confirm"))
							.OnClicked(this,&SRenameToolCompoundWidget::ButtonConfirm,ERenameAction::Fix)
						]
					#pragma endregion ConfimButton

					]
				#pragma endregion AddFix
				#pragma region Rename
					+ SVerticalBox::Slot()
					.Padding(StandardUpDownPadding)
					.FillHeight(1.f)
					[
						SNew(SVerticalBox)
						.Visibility(this,&SRenameToolCompoundWidget::GetVisibilityRename)

					#pragma region Name
						+ SVerticalBox::Slot()
						.AutoHeight()
						.Padding(StandardPadding)
						.HAlign(HAlign_Fill)
						[
							SNew(SHorizontalBox)

						#pragma region NameText
							+SHorizontalBox::Slot()
							.FillWidth(0.2f)
							.HAlign(HAlign_Right)
							.Padding(StandardRightPadding)
							[
								SNew(STextBlock)
								.Text(LOCTEXT("RenameToolEd.Name", "Name"))
								.TextStyle(FRenameToolEditStyle::Get(), "RenameToolEdMode.Text")
							]
						#pragma endregion NameText

						#pragma region NameInput
							+SHorizontalBox::Slot()
							.FillWidth(0.8f)
							.HAlign(HAlign_Fill)
							.Padding(StandardLeftPadding)
							[
								SNew(SEditableTextBox)
								.Style(FRenameToolEditStyle::Get(), "NormalEditableTextBoxStyle")
								.ToolTipText(LOCTEXT("RenameToolEd.NameInput", "Please Enter The Name Here"))
								.HintText(LOCTEXT("RenameToolEd.NameInput", "Please Enter The Name Here"))
								.SelectAllTextWhenFocused(true)
								.OnTextChanged(this, &SRenameToolCompoundWidget::NameInputChanged)
							]
						#pragma endregion NameInput

						]
					#pragma endregion Name

					#pragma region StartNumber

						+ SVerticalBox::Slot()
						.AutoHeight()
						.Padding(StandardPadding)
						.HAlign(HAlign_Fill)
						[
							SNew(SHorizontalBox)

						#pragma region StartNumberText
							+SHorizontalBox::Slot()
							.FillWidth(0.2f)
							.HAlign(HAlign_Right)
							.Padding(StandardRightPadding)
							[
								SNew(STextBlock)
								.Text(LOCTEXT("RenameToolEd.StartNumber", "StartNumber"))
								.TextStyle(FRenameToolEditStyle::Get(), "RenameToolEdMode.Text")
							]
						#pragma endregion StartNumberText

						#pragma region StartNumberInput
							+SHorizontalBox::Slot()
							.FillWidth(0.8f)
							.HAlign(HAlign_Fill)
							.Padding(StandardLeftPadding)
							[
								SNew(SEditableTextBox)
								.Style(FRenameToolEditStyle::Get(), "NormalEditableTextBoxStyle")
								.ToolTipText(LOCTEXT("RenameToolEd.StartNumberInput", "Please Enter The StartNumber Here"))
								.HintText(LOCTEXT("RenameToolEd.StartNumberInput", "Please Enter The StartNumber Here"))
								.SelectAllTextWhenFocused(true)
								.OnTextChanged(this, &SRenameToolCompoundWidget::StartNumberInputChanged)
							]
						#pragma endregion StartNumberInput

						]
					#pragma endregion StartNumber
					#pragma region Asset/Actor CheckBox
						+ SVerticalBox::Slot()
						.AutoHeight()
						.Padding(StandardPadding)
						.HAlign(HAlign_Fill)
						[
							SNew(SHorizontalBox)

						#pragma region Asset
							//Check Box
							+ SHorizontalBox::Slot()
							.FillWidth(1.f)
							.HAlign(HAlign_Right)
							.Padding(StandardPadding)
							[
								SNew(SCheckBox)
								.OnCheckStateChanged(this,&SRenameToolCompoundWidget::SetChangeAsset)
								.IsChecked(this,&SRenameToolCompoundWidget::CanChangeAsset)
								[
									SNew(STextBlock)
									.Text(LOCTEXT("RenameToolEd.Asset", "Asset"))
									.TextStyle(FRenameToolEditStyle::Get(), "RenameToolEdMode.Text")
								]
							]
						#pragma endregion Asset
						#pragma region Actor
							//Check Box
							+ SHorizontalBox::Slot()
							.FillWidth(1.f)
							.HAlign(HAlign_Left)
							.Padding(StandardPadding)
							[
								SNew(SCheckBox)
								.OnCheckStateChanged(this,&SRenameToolCompoundWidget::SetChangeActor)
								.IsChecked(this, &SRenameToolCompoundWidget::CanChangeActor)
								[
									SNew(STextBlock)
									.Text(LOCTEXT("RenameToolEd.Actor", "Actor"))
									.TextStyle(FRenameToolEditStyle::Get(), "RenameToolEdMode.Text")
								]
							]
						#pragma endregion Actor

						]
					#pragma endregion Asset/Actor CheckBox
					#pragma region ConfimButton
						+SVerticalBox::Slot()
						.AutoHeight()
						.Padding(StandardUpDownPadding)
						.HAlign(HAlign_Right)
						[
							SNew(SButton)
							.ButtonStyle(FRenameToolEditStyle::Get(),"Button")
							.Text(LOCTEXT("RenameToolEd.Confirm","Confirm"))
							.OnClicked(this,&SRenameToolCompoundWidget::ButtonConfirm,ERenameAction::RenameAndNumerate)
						]
					#pragma endregion ConfimButton
					]
				#pragma endregion Rename
				#pragma region Replace
					+ SVerticalBox::Slot()
					.Padding(StandardUpDownPadding)
					.FillHeight(1.f)
					[
						SNew(SVerticalBox)
						.Visibility(this,&SRenameToolCompoundWidget::GetVisibilityReplace)
					#pragma region FindStr
						
						+ SVerticalBox::Slot()
						.AutoHeight()
						.Padding(StandardPadding)
						.HAlign(HAlign_Fill)
						[
							SNew(SHorizontalBox)

						#pragma region FindStrText
							+SHorizontalBox::Slot()
							.FillWidth(0.2f)
							.HAlign(HAlign_Right)
							.Padding(StandardRightPadding)
							[
								SNew(STextBlock)
								.Text(LOCTEXT("RenameToolEd.FindStr", "FindString"))
								.TextStyle(FRenameToolEditStyle::Get(), "RenameToolEdMode.Text")
							]
						#pragma endregion FindStrText

						#pragma region FindStrInput
							+SHorizontalBox::Slot()
							.FillWidth(0.8f)
							.HAlign(HAlign_Fill)
							.Padding(StandardLeftPadding)
							[
								SNew(SEditableTextBox)
								.Style(FRenameToolEditStyle::Get(), "NormalEditableTextBoxStyle")
								.ToolTipText(LOCTEXT("RenameToolEd.FindStrInput", "Please Enter The FindString Here"))
								.HintText(LOCTEXT("RenameToolEd.FindStrInput", "Please Enter The FindString Here"))
								.SelectAllTextWhenFocused(true)
								.OnTextChanged(this, &SRenameToolCompoundWidget::FindStrInputChanged)
							]
						#pragma endregion FindStrInput

						]
					#pragma endregion FindStr
					#pragma region TargetStr
						
						+ SVerticalBox::Slot()
						.AutoHeight()
						.Padding(StandardPadding)
						.HAlign(HAlign_Fill)
						[
							SNew(SHorizontalBox)

						#pragma region TargetStrText
							+SHorizontalBox::Slot()
							.FillWidth(0.2f)
							.HAlign(HAlign_Right)
							.Padding(StandardRightPadding)
							[
								SNew(STextBlock)
								.Text(LOCTEXT("RenameToolEd.TargetStr", "TargetString"))
								.TextStyle(FRenameToolEditStyle::Get(), "RenameToolEdMode.Text")
							]
						#pragma endregion TargetStrText

						#pragma region TargetStrInput
							+SHorizontalBox::Slot()
							.FillWidth(0.8f)
							.HAlign(HAlign_Fill)
							.Padding(StandardLeftPadding)
							[
								SNew(SEditableTextBox)
								.Style(FRenameToolEditStyle::Get(), "NormalEditableTextBoxStyle")
								.ToolTipText(LOCTEXT("RenameToolEd.TargetStrInput", "Please Enter The TargetString Here"))
								.HintText(LOCTEXT("RenameToolEd.TargetStrInput", "Please Enter The TargetString Here"))
								.SelectAllTextWhenFocused(true)
								.OnTextChanged(this, &SRenameToolCompoundWidget::TargetStrInputChanged)
							]
						#pragma endregion TargetStrInput

						]
					#pragma endregion Target
					#pragma region Asset/Actor CheckBox
						+ SVerticalBox::Slot()
						.AutoHeight()
						.Padding(StandardPadding)
						.HAlign(HAlign_Fill)
						[
							SNew(SHorizontalBox)

						#pragma region Asset
							//Check Box
							+ SHorizontalBox::Slot()
							.FillWidth(1.f)
							.HAlign(HAlign_Right)
							.Padding(StandardPadding)
							[
								SNew(SCheckBox)
								.OnCheckStateChanged(this,&SRenameToolCompoundWidget::SetChangeAsset)
								.IsChecked(this,&SRenameToolCompoundWidget::CanChangeAsset)
								[
									SNew(STextBlock)
									.Text(LOCTEXT("RenameToolEd.Asset", "Asset"))
									.TextStyle(FRenameToolEditStyle::Get(), "RenameToolEdMode.Text")
								]
							]
						#pragma endregion Asset
						#pragma region Actor
							//Check Box
							+ SHorizontalBox::Slot()
							.FillWidth(1.f)
							.HAlign(HAlign_Left)
							.Padding(StandardPadding)
							[
								SNew(SCheckBox)
								.OnCheckStateChanged(this,&SRenameToolCompoundWidget::SetChangeActor)
								.IsChecked(this, &SRenameToolCompoundWidget::CanChangeActor)
								[
									SNew(STextBlock)
									.Text(LOCTEXT("RenameToolEd.Actor", "Actor"))
									.TextStyle(FRenameToolEditStyle::Get(), "RenameToolEdMode.Text")
								]
							]
						#pragma endregion Actor

						]
					#pragma endregion Asset/Actor CheckBox
					#pragma region ConfimButton
						+SVerticalBox::Slot()
						.AutoHeight()
						.Padding(StandardUpDownPadding)
						.HAlign(HAlign_Right)
						[
							SNew(SButton)
							.ButtonStyle(FRenameToolEditStyle::Get(),"Button")
							.Text(LOCTEXT("RenameToolEd.Confirm","Confirm"))
							.OnClicked(this,&SRenameToolCompoundWidget::ButtonConfirm,ERenameAction::FindAndReplace)
						]
					#pragma endregion ConfimButton
					]
				#pragma endregion Replace
				#pragma region Case
					+ SVerticalBox::Slot()
					.AutoHeight()
					.Padding(StandardUpDownPadding)
					.HAlign(HAlign_Fill)
					[
						SNew(SVerticalBox)
						.Visibility(this, &SRenameToolCompoundWidget::GetVisibilityCase)

					#pragma region Asset/Actor CheckBox
						+ SVerticalBox::Slot()
						.AutoHeight()
						.Padding(StandardPadding)
						.HAlign(HAlign_Fill)
						[
							SNew(SHorizontalBox)
						#pragma region Asset
							//Check Box
							+ SHorizontalBox::Slot()
							.FillWidth(1.f)
							.HAlign(HAlign_Right)
							.Padding(StandardPadding)
							[
								SNew(SCheckBox)
								.OnCheckStateChanged(this,&SRenameToolCompoundWidget::SetChangeAsset)
								.IsChecked(this,&SRenameToolCompoundWidget::CanChangeAsset)
								[
									SNew(STextBlock)
									.Text(LOCTEXT("RenameToolEd.Asset", "Asset"))
									.TextStyle(FRenameToolEditStyle::Get(), "RenameToolEdMode.Text")
								]
							]
						#pragma endregion Asset
						#pragma region Actor
							//Check Box
							+ SHorizontalBox::Slot()
							.FillWidth(1.f)
							.HAlign(HAlign_Left)
							.Padding(StandardPadding)
							[
								SNew(SCheckBox)
								.OnCheckStateChanged(this,&SRenameToolCompoundWidget::SetChangeActor)
								.IsChecked(this, &SRenameToolCompoundWidget::CanChangeActor)
								[
									SNew(STextBlock)
									.Text(LOCTEXT("RenameToolEd.Actor", "Actor"))
									.TextStyle(FRenameToolEditStyle::Get(), "RenameToolEdMode.Text")
								]
							]
						#pragma endregion Actor
						]
					#pragma endregion Asset/Actor CheckBox
					#pragma region CaseButton
						+SVerticalBox::Slot()
						.AutoHeight()
						.Padding(StandardPadding)
						.HAlign(HAlign_Fill)
						[
							SNew(SHorizontalBox)
						#pragma region UpperCaseButton
							+SHorizontalBox::Slot()
							.FillWidth(1.f)
							.HAlign(HAlign_Center)
							[
							SNew(SButton)
							.ButtonStyle(FRenameToolEditStyle::Get(), "Button")
							.Text(LOCTEXT("RenameToolEd.UpperCase", "ToUpperCase"))
							.OnClicked(this, &SRenameToolCompoundWidget::ButtonConfirm, ERenameAction::ToUpperCase)
							]
						#pragma endregion UpperCaseButton

						#pragma region LowerCaseButton
							+ SHorizontalBox::Slot()
							.FillWidth(1.f)
							.HAlign(HAlign_Center)
							[
								SNew(SButton)
								.ButtonStyle(FRenameToolEditStyle::Get(), "Button")
								.Text(LOCTEXT("RenameToolEd.LowerCase", "ToLowerCase"))
								.OnClicked(this, &SRenameToolCompoundWidget::ButtonConfirm, ERenameAction::ToLowerCase)
							]
						#pragma endregion LowerCaseButton
						]
					#pragma endregion CaseButton			
					]
				#pragma endregion Case
				]

				

			]
#pragma endregion Content
		]
	];
	
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

TSharedRef<SWidget> SRenameToolCompoundWidget::BuildToolBar()
{
	FToolBarBuilder Toolbar(RenameToolBarUICommandList, FMultiBoxCustomization::None, nullptr, Orient_Vertical);
	Toolbar.SetLabelVisibility(EVisibility::Collapsed);
	Toolbar.SetStyle(&FRenameToolEditStyle::Get(), "RenameToolBar");

	Toolbar.AddToolBarButton(FRenameCommands::Get().SetAddFix);
	Toolbar.AddToolBarButton(FRenameCommands::Get().SetRename);
	Toolbar.AddToolBarButton(FRenameCommands::Get().SetReplace);
	Toolbar.AddToolBarButton(FRenameCommands::Get().SetCase);



	return SNew(SHorizontalBox)

		+ SHorizontalBox::Slot()
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			[
				SNew(SBorder)
				.HAlign(HAlign_Center)
				.Padding(0)
				.BorderImage(FEditorStyle::GetBrush("NoBorder"))
				.IsEnabled(FSlateApplication::Get().GetNormalExecutionAttribute())
				[
					Toolbar.MakeWidget()
				]
			]
		];

}

FText SRenameToolCompoundWidget::GetActiveToolName()const
{
	FText OutText;
	if (RenameToolUISetting.GetAddFix())
	{
		OutText = LOCTEXT("RenameToolEd.AddFix","AddFix");
	}
	if (RenameToolUISetting.GetRename())
	{
		OutText = LOCTEXT("RenameToolEd.Rename", "Rename");
	}
	if (RenameToolUISetting.GetReplace())
	{
		OutText = LOCTEXT("RenameToolEd.Replace", "Replace");
	}
	if (RenameToolUISetting.GetCase())
	{
		OutText = LOCTEXT("RenameToolEd.Case", "Case");
	}
	return OutText;
}

FReply SRenameToolCompoundWidget::ButtonConfirm(ERenameAction NewRenameAction)
{
	RenameToolHelper.Rename(NewRenameAction);
	return FReply::Handled();
}

void SRenameToolCompoundWidget::PrefixInputChanged(const FText& NewText)
{
	RenameToolHelper.GetRenameInformation()->SetPrefix(NewText.ToString());
}

void SRenameToolCompoundWidget::SuffixInputChanged(const FText& NewText)
{
	RenameToolHelper.GetRenameInformation()->SetSuffix(NewText.ToString());
}

void SRenameToolCompoundWidget::NameInputChanged(const FText& NewText)
{
	RenameToolHelper.GetRenameInformation()->SetName(NewText.ToString());
}

void SRenameToolCompoundWidget::StartNumberInputChanged(const FText& NewText)
{
	RenameToolHelper.GetRenameInformation()->SetStartNumber(FCString::Atoi(*NewText.ToString()));
}

void SRenameToolCompoundWidget::FindStrInputChanged(const FText& NewText)
{
	RenameToolHelper.GetRenameInformation()->SetFindStr(NewText.ToString());
}

void SRenameToolCompoundWidget::TargetStrInputChanged(const FText& NewText)
{
	RenameToolHelper.GetRenameInformation()->SetTargetStr(NewText.ToString());
}

void SRenameToolCompoundWidget::SetChangeAsset(ECheckBoxState InState)
{
	if (InState==ECheckBoxState::Checked)
	{
		RenameToolHelper.SetChangeAsset(true);
		RenameToolUISetting.SetChangeAsset(true);
	}
	else
	{
		RenameToolHelper.SetChangeAsset(false);
		RenameToolUISetting.SetChangeAsset(false);

	}
}

void SRenameToolCompoundWidget::SetChangeActor(ECheckBoxState InState)
{
	if (InState == ECheckBoxState::Checked)
	{
		RenameToolHelper.SetChangeActor(true);
		RenameToolUISetting.SetChangeActor(true);
	}
	else
	{
		RenameToolHelper.SetChangeActor(false);
		RenameToolUISetting.SetChangeActor(false);
	}
}

ECheckBoxState SRenameToolCompoundWidget::CanChangeAsset()const
{
	if (RenameToolHelper.IsChangeAsset())
	{
		return ECheckBoxState::Checked;
	}
	else
	{
		return ECheckBoxState::Unchecked;
	}
	
}

ECheckBoxState SRenameToolCompoundWidget::CanChangeActor()const
{
	if (RenameToolHelper.IsChangeActor())
	{
		return ECheckBoxState::Checked;
	}
	else
	{
		return ECheckBoxState::Unchecked;
	}
}

void SRenameToolCompoundWidget::Init()
{
	CommandsInit();
	UISettingInit();
}

void SRenameToolCompoundWidget::CommandsInit()
{
	RenameToolBarUICommandList = MakeShareable(new FUICommandList);

	RenameToolBarUICommandList->MapAction
	(
		FRenameCommands::Get().SetAddFix,
		FExecuteAction::CreateRaw(&RenameToolUISetting,&FRenameToolUISetting::SetAddFix),
		FCanExecuteAction(),
		FIsActionChecked::CreateLambda
		(	[=]
			{
				return RenameToolUISetting.GetAddFix();
			}
		)
	);
	RenameToolBarUICommandList->MapAction
	(
		FRenameCommands::Get().SetRename,
		FExecuteAction::CreateRaw(&RenameToolUISetting, &FRenameToolUISetting::SetRename),
		FCanExecuteAction(),
		FIsActionChecked::CreateLambda
		([=]
			{
				return RenameToolUISetting.GetRename();
			}
		)
	);
	RenameToolBarUICommandList->MapAction
	(
		FRenameCommands::Get().SetReplace,
		FExecuteAction::CreateRaw(&RenameToolUISetting, &FRenameToolUISetting::SetReplace),
		FCanExecuteAction(),
		FIsActionChecked::CreateLambda
		([=]
			{
				return RenameToolUISetting.GetReplace();
			}
		)
	);
	RenameToolBarUICommandList->MapAction
	(
		FRenameCommands::Get().SetCase,
		FExecuteAction::CreateRaw(&RenameToolUISetting, &FRenameToolUISetting::SetCase),
		FCanExecuteAction(),
		FIsActionChecked::CreateLambda
		([=]
			{
				return RenameToolUISetting.GetCase();
			}
		)
	);
}

void SRenameToolCompoundWidget::UISettingInit()
{
	RenameToolUISetting.Load();
	RenameToolHelper.SetChangeActor(RenameToolUISetting.IsChangeActor());
	RenameToolHelper.SetChangeAsset(RenameToolUISetting.IsChangeAsset());
}

#pragma region WidgetVisiable
EVisibility SRenameToolCompoundWidget::GetVisibilityAddFix() const
{
	if (RenameToolUISetting.GetAddFix())
	{
		return EVisibility::Visible;
	}
	else
	{
		return EVisibility::Collapsed;
	}
}
EVisibility SRenameToolCompoundWidget::GetVisibilityRename()const
{
	if (RenameToolUISetting.GetRename())
	{
		return EVisibility::Visible;
	}
	else
	{
		return EVisibility::Collapsed;
	}
}
EVisibility SRenameToolCompoundWidget::GetVisibilityReplace()const
{
	if (RenameToolUISetting.GetReplace())
	{
		return EVisibility::Visible;
	}
	else
	{
		return EVisibility::Collapsed;
	}
}
EVisibility SRenameToolCompoundWidget::GetVisibilityCase()const
{
	if (RenameToolUISetting.GetCase())
	{
		return EVisibility::Visible;
	}
	else
	{
		return EVisibility::Collapsed;
	}
}
#pragma endregion WidgetVisiable

#undef LOCTEXT_NAMESPACE
