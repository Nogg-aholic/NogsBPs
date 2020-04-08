// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "NogsBPsCommands.h"

#define LOCTEXT_NAMESPACE "FNogsBPsModule"

void FNogsBPsCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "NogsBPs", "Bring up NogsBPs window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
