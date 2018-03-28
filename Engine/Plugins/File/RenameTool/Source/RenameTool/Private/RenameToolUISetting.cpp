// Copyright 2018 BruceLee, Inc. All Rights Reserved.

#include "RenameToolUISetting.h"

FRenameToolUISetting::FRenameToolUISetting()
	:bSetAddFix(true),bSetCase(false),bSetRename(false),bSetReplace(false)
{

}

void FRenameToolUISetting::SetAddFix()
{
	CancelAllSet();
	bSetAddFix = true;
}

void FRenameToolUISetting::SetRename()
{
	CancelAllSet();
	bSetRename = true;
}

void FRenameToolUISetting::SetReplace()
{
	CancelAllSet();
	bSetReplace = true;
}

void FRenameToolUISetting::SetCase()
{
	CancelAllSet();
	bSetCase = true;
}

void FRenameToolUISetting::CancelAllSet()
{
	bSetAddFix = false;
	bSetCase = false;
	bSetRename = false;
	bSetReplace = false;
}

void FRenameToolUISetting::SetChangeAsset(bool NewBoolOfChangeAsset)
{
	bCanChangeAsset = NewBoolOfChangeAsset;
}

void FRenameToolUISetting::SetChangeActor(bool NewBoolOfChangeActor)
{
	bCanChangeActor = NewBoolOfChangeActor;
}

bool FRenameToolUISetting::GetAddFix()const
{
	return bSetAddFix;
}

bool FRenameToolUISetting::GetRename()const
{
	return bSetRename;
}

bool FRenameToolUISetting::GetReplace()const
{
	return bSetReplace;
}

bool FRenameToolUISetting::GetCase()const
{
	return bSetCase;
}

bool FRenameToolUISetting::IsChangeAsset() const
{
	return bCanChangeAsset;
}

bool FRenameToolUISetting::IsChangeActor() const
{
	return bCanChangeActor;
}

void FRenameToolUISetting::Save()
{
	GConfig->SetBool(TEXT("RenameToolEd"), TEXT("bSetAddFix"), bSetAddFix, GEditorPerProjectIni);
	GConfig->SetBool(TEXT("RenameToolEd"), TEXT("bSetRename"), bSetRename, GEditorPerProjectIni);
	GConfig->SetBool(TEXT("RenameToolEd"), TEXT("bSetReplace"), bSetReplace, GEditorPerProjectIni);
	GConfig->SetBool(TEXT("RenameToolEd"), TEXT("bSetCase"), bSetCase, GEditorPerProjectIni);
	GConfig->SetBool(TEXT("RenameToolEd"), TEXT("bCanChangeAsset"), bCanChangeAsset, GEditorPerProjectIni);
	GConfig->SetBool(TEXT("RenameToolEd"), TEXT("bCanChangeActor"), bCanChangeActor, GEditorPerProjectIni);



}

void FRenameToolUISetting::Load()
{
	GConfig->GetBool(TEXT("RenameToolEd"), TEXT("bSetAddFix"), bSetAddFix, GEditorPerProjectIni);
	GConfig->GetBool(TEXT("RenameToolEd"), TEXT("bSetRename"), bSetRename, GEditorPerProjectIni);
	GConfig->GetBool(TEXT("RenameToolEd"), TEXT("bSetReplace"), bSetReplace, GEditorPerProjectIni);
	GConfig->GetBool(TEXT("RenameToolEd"), TEXT("bSetCase"), bSetCase, GEditorPerProjectIni);
	GConfig->GetBool(TEXT("RenameToolEd"), TEXT("bCanChangeAsset"), bCanChangeAsset, GEditorPerProjectIni);
	GConfig->GetBool(TEXT("RenameToolEd"), TEXT("bCanChangeActor"), bCanChangeActor, GEditorPerProjectIni);
}
