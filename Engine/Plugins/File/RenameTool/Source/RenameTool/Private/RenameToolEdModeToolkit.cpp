// Copyright 2018 BruceLee, Inc. All Rights Reserved.

#include "RenameToolEdModeToolkit.h"
#include "RenameToolCompoundWidget.h"
#include "RenameToolEdMode.h"
#include "Engine/Selection.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Docking/SDockableTab.h"
#include "Widgets/Text/STextBlock.h"
#include "EditorModeManager.h"

#define LOCTEXT_NAMESPACE "FRenameToolEdModeToolkit"

FRenameToolEdModeToolkit::FRenameToolEdModeToolkit()
{
}

void FRenameToolEdModeToolkit::Init(const TSharedPtr<IToolkitHost>& InitToolkitHost)
{
	SAssignNew(ToolkitWidget, SRenameToolCompoundWidget);
	FModeToolkit::Init(InitToolkitHost);
}

FName FRenameToolEdModeToolkit::GetToolkitFName() const
{
	return FName("RenameToolEdMode");
}

FText FRenameToolEdModeToolkit::GetBaseToolkitName() const
{
	return NSLOCTEXT("RenameToolEdModeToolkit", "DisplayName", "RenameToolEdMode Tool");
}

class FEdMode* FRenameToolEdModeToolkit::GetEditorMode() const
{
	return GLevelEditorModeTools().GetActiveMode(FRenameToolEdMode::EM_RenameToolEdModeId);
}

#undef LOCTEXT_NAMESPACE
