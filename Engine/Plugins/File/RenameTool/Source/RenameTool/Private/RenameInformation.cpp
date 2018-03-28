// Copyright 2018 BruceLee, Inc. All Rights Reserved.
#include "RenameInformation.h"

void FRenameInformation::SetPrefix(FString NewPrefix)
{
	Prefix = NewPrefix;
}
void FRenameInformation::SetSuffix(FString NewSuffix)
{
	Suffix = NewSuffix;
}
void FRenameInformation::SetName(FString NewName)
{
	Name = NewName;
}
void FRenameInformation::SetFindStr(FString NewFindStr)
{
	FindStr = NewFindStr;
}
void FRenameInformation::SetTargetStr(FString NewTargetStr)
{
	TargetStr = NewTargetStr;
}
void FRenameInformation::SetStartNumber(int NewStartNumber)
{
	StartNumber = NewStartNumber;
}
void FRenameInformation::SetRenameAction(ERenameAction NewRenameAction)
{
	RenameAction = NewRenameAction;
}

FString FRenameInformation::GetPrefix()
{
	return Prefix;
}
FString FRenameInformation::GetSuffix()
{
	return Suffix;
}
FString FRenameInformation::GetFindStr()
{
	return FindStr;
}
FString FRenameInformation::GetTargetStr()
{
	return TargetStr;
}
FString FRenameInformation::GetName()
{
	return Name;
}
ERenameAction FRenameInformation::GetRenameAction()
{
	return RenameAction;
}
int FRenameInformation::GetStartNumber()
{
	return StartNumber;
}

FRenameInformation::FRenameInformation()
	:Prefix(""), Suffix(""), Name(""), FindStr(""), TargetStr(""), StartNumber(1), RenameAction(ERenameAction::FindAndReplace)
{

}