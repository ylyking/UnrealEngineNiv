// Copyright 2018 BruceLee, Inc. All Rights Reserved.
#pragma once

#include "RenameToolPCH.h"

UENUM()
enum class ERenameAction : uint8
{
	ToLowerCase,
	ToUpperCase,
	Fix,
	RenameAndNumerate,
	FindAndReplace
};

class FRenameInformation
{
private:
	FString Prefix;
	FString Suffix;
	FString FindStr;
	FString TargetStr;
	FString Name;
	ERenameAction RenameAction;
	int StartNumber;
public:
	void SetPrefix(FString NewPrefix);
	void SetSuffix(FString NewSuffix);
	void SetFindStr(FString NewFindStr);
	void SetTargetStr(FString NewTargetStr);
	void SetName(FString NewName);
	void SetStartNumber(int NewStartNumber);
	void SetRenameAction(ERenameAction NewRenameAction);

	FString GetPrefix();
	FString GetSuffix();
	FString GetFindStr();
	FString GetTargetStr();
	FString GetName();
	ERenameAction GetRenameAction();
	int GetStartNumber();

	FRenameInformation();
};
