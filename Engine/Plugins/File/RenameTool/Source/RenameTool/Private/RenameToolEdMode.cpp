// Copyright 2018 BruceLee, Inc. All Rights Reserved.

#include "RenameToolEdMode.h"
#include "RenameToolEdModeToolkit.h"
#include "Toolkits/ToolkitManager.h"
#include "EditorModeManager.h"

const FEditorModeID FRenameToolEdMode::EM_RenameToolEdModeId = TEXT("EM_RenameToolEdMode");

FRenameToolEdMode::FRenameToolEdMode()
{

}

FRenameToolEdMode::~FRenameToolEdMode()
{

}

void FRenameToolEdMode::Enter()
{
	FEdMode::Enter();

	if (!Toolkit.IsValid() && UsesToolkits())
	{
		Toolkit = MakeShareable(new FRenameToolEdModeToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}
}

void FRenameToolEdMode::Exit()
{
	if (Toolkit.IsValid())
	{
		FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
		Toolkit.Reset();
	}

	// Call base Exit method to ensure proper cleanup
	FEdMode::Exit();
}

bool FRenameToolEdMode::UsesToolkits() const
{
	return true;
}




