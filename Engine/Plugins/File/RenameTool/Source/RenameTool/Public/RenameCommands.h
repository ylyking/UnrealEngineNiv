// Copyright 2018 BruceLee, Inc. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "RenameToolEdStyle.h"

class FRenameCommands : public TCommands<FRenameCommands>
{
public:

	FRenameCommands()
		: TCommands<FRenameCommands>(TEXT("RenameToolEdMode"), NSLOCTEXT("Contexts", "RenameToolEdMode", "Rename Tool Plugins"), NAME_None, FRenameToolEditStyle::GetStyleSetName())
	{
	}
	// TCommands<> interface
	virtual void RegisterCommands() override;

	//Tool Bar
	TSharedPtr< FUICommandInfo > SetAddFix;
	TSharedPtr< FUICommandInfo > SetRename;
	TSharedPtr< FUICommandInfo > SetReplace;
	TSharedPtr< FUICommandInfo > SetCase;

};
