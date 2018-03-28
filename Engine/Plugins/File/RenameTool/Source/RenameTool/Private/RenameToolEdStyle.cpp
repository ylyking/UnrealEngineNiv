// Copyright 2018 BruceLee, Inc. All Rights Reserved.

#include "RenameToolEdStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "SlateGameResources.h"
#include "IPluginManager.h"

#pragma region "Brush宏定义"
	#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
	#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
	#define BORDER_BRUSH( RelativePath, ... ) FSlateBorderBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
	#define TTF_FONT( RelativePath, ... ) FSlateFontInfo( Style->RootToContentDir( RelativePath, TEXT(".ttf") ), __VA_ARGS__ )
	#define TTF_CORE_FONT( RelativePath, ... ) FSlateFontInfo( Style->RootToCoreContentDir( RelativePath, TEXT(".ttf") ), __VA_ARGS__ )
	#define OTF_FONT( RelativePath, ... ) FSlateFontInfo( Style->RootToContentDir( RelativePath, TEXT(".otf") ), __VA_ARGS__ )
#pragma endregion

#pragma region "Icon大小"
	const FVector2D Icon8x8(8.0f, 8.0f);
	const FVector2D Icon16x16(16.0f, 16.0f);
	const FVector2D Icon20x20(20.0f, 20.0f);
	const FVector2D Icon40x40(40.0f, 40.0f);
	const FVector2D Icon32x32(32.0f, 32.0f);
	const FVector2D Icon64x64(64.0f, 64.0f);
#pragma endregion

TSharedPtr< FSlateStyleSet > FRenameToolEditStyle::StyleInstance = NULL;

void FRenameToolEditStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FRenameToolEditStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FRenameToolEditStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("RenameToolEdStyle"));
	return StyleSetName;
}

void FRenameToolEditStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FRenameToolEditStyle::Get()
{
	return *StyleInstance;
}

TSharedRef< FSlateStyleSet > FRenameToolEditStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("RenameToolEdStyle"));

	Style->SetContentRoot(IPluginManager::Get().FindPlugin("RenameTool")->GetBaseDir() / TEXT("Resources"));

#pragma region "Color定义"
	FLinearColor DimBackground= FLinearColor(FColor(64, 64, 64));
	FLinearColor DarkBackground = FLinearColor(FColor(42, 42, 42));
	FLinearColor DimBackgroundHover = FLinearColor(FColor(50, 50, 50));
	FLinearColor DefaultForeground = FLinearColor(0.72f, 0.72f, 0.72f, 1.f);
#pragma endregion 

#pragma region	"输入框Style定义"
	FEditableTextBoxStyle NormalEditableTextBoxStyle = FEditableTextBoxStyle()
		.SetBackgroundImageNormal(BOX_BRUSH("Common/TextBox", FMargin(4.0f / 16.0f)))
		.SetBackgroundImageHovered(BOX_BRUSH("Common/TextBox_Hovered", FMargin(4.0f / 16.0f)))
		.SetBackgroundImageFocused(BOX_BRUSH("Common/TextBox_Hovered", FMargin(4.0f / 16.0f)))
		.SetBackgroundImageReadOnly(BOX_BRUSH("Common/TextBox_ReadOnly", FMargin(4.0f / 16.0f)));
	Style->Set("NormalEditableTextBoxStyle", NormalEditableTextBoxStyle);
#pragma endregion 

#pragma region	"Button Style定义"
	FButtonStyle Button = FButtonStyle()
		.SetNormal(BOX_BRUSH("Common/Button", FVector2D(32, 32), 8.0f / 32.0f))
		.SetHovered(BOX_BRUSH("Common/Button_Hovered", FVector2D(32, 32), 8.0f / 32.0f))
		.SetPressed(BOX_BRUSH("Common/Button_Pressed", FVector2D(32, 32), 8.0f / 32.0f))
		.SetNormalPadding(FMargin(2, 2, 2, 2))
		.SetPressedPadding(FMargin(2, 3, 2, 1));
	Style->Set("Button", Button);
#pragma endregion
	FButtonStyle DeleteButton = FButtonStyle()
		.SetNormal(BOX_BRUSH("Common/Button", FVector2D(32, 32), 8.0f / 32.0f))
		.SetHovered(BOX_BRUSH("Common/Button_Hovered", FVector2D(32, 32), 8.0f / 32.0f))
		.SetPressed(BOX_BRUSH("Common/Button_Pressed", FVector2D(32, 32), 8.0f / 32.0f))
		.SetNormalPadding(FMargin(2, 2, 2, 2))
		.SetPressedPadding(FMargin(2, 3, 2, 1));
	Style->Set("MultiBox.DeleteButton", DeleteButton);

#pragma region	"Text Style定义"
	FTextBlockStyle NormalText = FTextBlockStyle()
		.SetFont(TTF_FONT("Fonts/Deng", 10))
		.SetColorAndOpacity(FSlateColor::UseForeground())
		.SetShadowOffset(FVector2D::ZeroVector)
		.SetShadowColorAndOpacity(FLinearColor::Black)
		.SetHighlightColor(FLinearColor(0.02f, 0.3f, 0.0f))
		.SetHighlightShape(BOX_BRUSH("Common/TextBlockHighlightShape", FMargin(3.f / 8.f)));

	Style->Set("RenameToolEdMode.Text", FTextBlockStyle(NormalText)
	);
#pragma endregion

#pragma region "RenameToolBar Style定义"
	Style->Set("RenameToolBar.ToggleButton", FCheckBoxStyle()
		.SetCheckBoxType(ESlateCheckBoxType::ToggleButton)
		.SetUncheckedImage(BOX_BRUSH("Common/Selection", 8.0f / 32.0f, DimBackground))
		.SetUncheckedPressedImage(BOX_BRUSH("RenameMode/TabActive", 8.0f / 32.0f))
		.SetUncheckedHoveredImage(BOX_BRUSH("Common/Selection", 8.0f / 32.0f, DimBackgroundHover))
		.SetCheckedImage(BOX_BRUSH("RenameMode/TabActive", 8.0f / 32.0f))
		.SetCheckedHoveredImage(BOX_BRUSH("RenameMode/TabActive", 8.0f / 32.0f))
		.SetCheckedPressedImage(BOX_BRUSH("RenameMode/TabActive", 8.0f / 32.0f))
		.SetPadding(0));

	Style->Set("RenameToolBar.Label", FTextBlockStyle(NormalText).SetFont(TTF_FONT("Fonts/Deng", 9)));
	Style->Set("RenameToolBar.Background", new BOX_BRUSH("Common/GroupBorder", FMargin(4.0f / 16.0f)));
	Style->Set("RenameToolBar.Icon", new IMAGE_BRUSH("Icons/icon_tab_Toolbars_16x", Icon16x16));
	Style->Set("RenameToolBar.Expand", new IMAGE_BRUSH("Icons/toolbar_expand_16x", Icon16x16));
	Style->Set("RenameToolBar.SubMenuIndicator", new IMAGE_BRUSH("Common/SubmenuArrow", Icon8x8));
	Style->Set("RenameToolBar.SToolBarComboButtonBlock.Padding", FMargin(4.0f));
	Style->Set("RenameToolBar.SToolBarButtonBlock.Padding", FMargin(0.f));
	Style->Set("RenameToolBar.SToolBarCheckComboButtonBlock.Padding", FMargin(4.0f));
	Style->Set("RenameToolBar.SToolBarButtonBlock.CheckBox.Padding", FMargin(10.0f, 6.f));
	Style->Set("RenameToolBar.SToolBarComboButtonBlock.ComboButton.Color", DefaultForeground);
	Style->Set("RenameToolBar.Block.IndentedPadding", FMargin(18.0f, 2.0f, 4.0f, 4.0f));
	Style->Set("RenameToolBar.Block.Padding", FMargin(2.0f, 2.0f, 4.0f, 4.0f));
	Style->Set("RenameToolBar.Separator", new BOX_BRUSH("RenameMode/Button", 4.0f / 32.0f));
	Style->Set("RenameToolBar.Separator.Padding", FMargin(0.5f));
#pragma endregion

#pragma region "ToolBarIconStyle"
	Style->Set("RenameToolEdMode.SetAddFix", new IMAGE_BRUSH("Icons/icon_add", Icon32x32));
	Style->Set("RenameToolEdMode.SetReplace", new IMAGE_BRUSH("Icons/icon_replace", Icon32x32));
	Style->Set("RenameToolEdMode.SetRename", new IMAGE_BRUSH("Icons/icon_rename", Icon32x32));
	Style->Set("RenameToolEdMode.SetCase", new IMAGE_BRUSH("Icons/icon_case", Icon32x32));

	Style->Set("RenameToolEdMode.RenameToolEdMode", new IMAGE_BRUSH("Icons/icon_rename_mode", Icon40x40));
	Style->Set("RenameToolEdMode.RenameToolEdMode.Small", new IMAGE_BRUSH("Icons/icon_rename_mode", Icon40x40));
#pragma endregion

	return Style;
}