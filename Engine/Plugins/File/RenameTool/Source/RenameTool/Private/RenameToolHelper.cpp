// Copyright 2018 BruceLee, Inc. All Rights Reserved.
#include "RenameToolHelper.h"
#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"


FRenameInformation* FRenameToolHelper::GetRenameInformation()
{
	return &RenameInformation;
}

void FRenameToolHelper::Rename(ERenameAction NewRenameAction)
{
	RenameInformation.SetRenameAction(NewRenameAction);
	if (bSetChangeAsset)
	{
		FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
		TArray<FAssetData> SelectedAssets;
		ContentBrowserModule.Get().GetSelectedAssets(SelectedAssets);

		int32 Index = 0;
		for (auto AssetIt = SelectedAssets.CreateIterator(); AssetIt; ++AssetIt)
		{
			const FAssetData& AssetData = *AssetIt;
			if (UObject* Asset = AssetData.GetAsset())
			{
				SetAssetNewName(Asset, Index);
				++Index;
			}
		}
	}
	if (bSetChangeActor)
	{
		TArray<AActor*> SelectionSetCache;
		for (FSelectionIterator It(GEditor->GetSelectedActorIterator()); It; ++It)
		{
			if (AActor* Actor = Cast<AActor>(*It))
			{
				SelectionSetCache.Add(Actor);
			}
		}

		int32 Index = 0;
		for (auto ActorIt = SelectionSetCache.CreateIterator(); ActorIt; ++ActorIt)
		{
			AActor* Actor = *ActorIt;
			UE_LOG(LogTemp, Log, TEXT("aaaa"));
			SetActorNewName(Actor, Index);
			++Index;
		}
	}
}

bool FRenameToolHelper::IsChangeAsset()const
{
	return bSetChangeAsset;
}

bool FRenameToolHelper::IsChangeActor()const
{
	return bSetChangeActor;
}

void FRenameToolHelper::SetChangeAsset(bool NewSetChangeAsset)
{
	bSetChangeAsset = NewSetChangeAsset;
}

void FRenameToolHelper::SetChangeActor(bool NewSetChangeActor)
{
	bSetChangeActor = NewSetChangeActor;
}

FRenameToolHelper::FRenameToolHelper()
	:bSetChangeAsset(false),bSetChangeActor(false)
{
	RenameInformation = FRenameInformation::FRenameInformation();
}

void FRenameToolHelper::SetAssetNewName(UObject* Asset, int Index)
{
	FString NewName;
	switch (RenameInformation.GetRenameAction())
	{
		case ERenameAction::Fix:
		{
			NewName = RenameInformation.GetPrefix() + Asset->GetName() + RenameInformation.GetSuffix();
		}break;

		case ERenameAction::FindAndReplace:
		{
			NewName = Asset->GetName().Replace(*RenameInformation.GetFindStr(), *RenameInformation.GetTargetStr());
		}break;

		case ERenameAction::RenameAndNumerate:
		{
			NewName = RenameInformation.GetName() + FString::FromInt(RenameInformation.GetStartNumber() + Index);
		}break;

		case ERenameAction::ToLowerCase:
		{
			NewName = Asset->GetName().ToLower();
		}break;

		case ERenameAction::ToUpperCase:
		{
			NewName = Asset->GetName().ToUpper();
		}break;
	}
	FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools");
	TArray<FAssetRenameData> AssetsAndNames;
	const FString PackagePath = FPackageName::GetLongPackagePath(Asset->GetOutermost()->GetName());
	new(AssetsAndNames) FAssetRenameData(Asset, PackagePath, NewName);
	AssetToolsModule.Get().RenameAssets(AssetsAndNames);
}

void FRenameToolHelper::SetActorNewName(AActor* Actor, int Index)
{
	FString NewName;
	switch (RenameInformation.GetRenameAction())
	{
		case ERenameAction::Fix:
		{
			NewName = RenameInformation.GetPrefix() + Actor->GetActorLabel() + RenameInformation.GetSuffix();
		}break;

		case ERenameAction::FindAndReplace:
		{
			NewName = Actor->GetActorLabel().Replace(*RenameInformation.GetFindStr(), *RenameInformation.GetTargetStr());
			NewName = TEXT(" ") + NewName;
		}break;

		case ERenameAction::RenameAndNumerate:
		{
			NewName = RenameInformation.GetName() + FString::FromInt(RenameInformation.GetStartNumber() + Index);
			NewName = TEXT(" ") + NewName;
		}break;

		case ERenameAction::ToLowerCase:
		{
			NewName = Actor->GetActorLabel().ToLower();
		}break;

		case ERenameAction::ToUpperCase:
		{
			NewName = Actor->GetActorLabel().ToUpper();
		}break;
	}
	Actor->Rename(*NewName);
	Actor->SetActorLabel(NewName);
}
