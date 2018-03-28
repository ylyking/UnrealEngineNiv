// Copyright 2018 BruceLee, Inc. All Rights Reserved.
#include "RenameTool.h"
#include "RenameCommands.h"
#include "RenameToolEdMode.h"
#include "RenameToolEdStyle.h"

#define LOCTEXT_NAMESPACE "FRenameToolModule"

void FRenameToolModule::StartupModule()
{
	//UIStyle Init
	FRenameToolEditStyle::Initialize();
	FRenameToolEditStyle::ReloadTextures();
	//CommandsRegister
	FRenameCommands::Register();
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FEditorModeRegistry::Get().RegisterMode<FRenameToolEdMode>(FRenameToolEdMode::EM_RenameToolEdModeId, LOCTEXT("RenameToolEdMode", "RenameToolEdMode"), FSlateIcon(FRenameToolEditStyle::GetStyleSetName(),"RenameToolEdMode.RenameToolEdMode","RenameToolEdMode.RenameToolEdMode.Small"), true);

}

void FRenameToolModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FEditorModeRegistry::Get().UnregisterMode(FRenameToolEdMode::EM_RenameToolEdModeId);

	FRenameToolEditStyle::Shutdown();

}

#undef LOCTEXT_NAMESPACE

	
IMPLEMENT_MODULE(FRenameToolModule, RenameTool)