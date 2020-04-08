// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "NogsBPs.h"
#include "NogsBPsStyle.h"
#include "NogsBPsCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

static const FName NogsBPsTabName("NogsBPs");

#define LOCTEXT_NAMESPACE "FNogsBPsModule"

void FNogsBPsModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FNogsBPsStyle::Initialize();
	FNogsBPsStyle::ReloadTextures();

	FNogsBPsCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FNogsBPsCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FNogsBPsModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FNogsBPsModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FNogsBPsModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(NogsBPsTabName, FOnSpawnTab::CreateRaw(this, &FNogsBPsModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FNogsBPsTabTitle", "NogsBPs"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FNogsBPsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FNogsBPsStyle::Shutdown();

	FNogsBPsCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(NogsBPsTabName);
}

TSharedRef<SDockTab> FNogsBPsModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FNogsBPsModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("NogsBPs.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FNogsBPsModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(NogsBPsTabName);
}

void FNogsBPsModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FNogsBPsCommands::Get().OpenPluginWindow);
}

void FNogsBPsModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FNogsBPsCommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FNogsBPsModule, NogsBPs)