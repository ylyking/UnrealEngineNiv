// Copyright 2018 BruceLee, Inc. All Rights Reserved.
#pragma once
#include "RenameInformation.h"

class FRenameToolHelper 
{
public:
	FRenameToolHelper();
	FRenameInformation* GetRenameInformation();
	void Rename(ERenameAction NewRenameAction);

	bool IsChangeAsset()const;
	bool IsChangeActor()const;

	void SetChangeAsset(bool NewSetChangeAsset);
	void SetChangeActor(bool NewSetChangeActor);

private:
	void SetAssetNewName(UObject* Asset, int Index);
	void SetActorNewName(AActor* Actor, int Index);

	FRenameInformation RenameInformation;
	bool bSetChangeAsset;
	bool bSetChangeActor;
};
