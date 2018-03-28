// Copyright 2018 BruceLee, Inc. All Rights Reserved.
#pragma once
#include "RenameInformation.h"
class FRenameToolUISetting
{
public:
	FRenameToolUISetting();

	void SetAddFix();
	void SetRename();
	void SetReplace();
	void SetCase();
	void CancelAllSet();
	void SetChangeAsset(bool NewBoolOfChangeAsset);
	void SetChangeActor(bool NewBoolOfChangeActor);


	bool GetAddFix()const;
	bool GetRename()const;
	bool GetReplace()const;
	bool GetCase()const;
	bool IsChangeAsset()const;
	bool IsChangeActor()const;

	void Save();
	void Load();

private:
	bool bSetAddFix;
	bool bSetRename;
	bool bSetReplace;
	bool bSetCase;
	bool bCanChangeAsset;
	bool bCanChangeActor;
};
