// Copyright 2018 BruceLee, Inc. All Rights Reserved.
#include "RenameCommands.h"

#define LOCTEXT_NAMESPACE "FRenameToolCommands"

void FRenameCommands::RegisterCommands() 
{
	UI_COMMAND(SetReplace, "Set Replace", "ReplaceSelect", EUserInterfaceActionType::ToggleButton, FInputChord());
	UI_COMMAND(SetCase, "Set Case", "CaseSelect", EUserInterfaceActionType::ToggleButton, FInputChord());
	UI_COMMAND(SetAddFix, "Set AddFix", "AddFixSelect", EUserInterfaceActionType::ToggleButton, FInputChord());
	UI_COMMAND(SetRename, "Set Rename", "RenameSelect", EUserInterfaceActionType::ToggleButton, FInputChord());
}

#undef LOCTEXT_NAMESPACE