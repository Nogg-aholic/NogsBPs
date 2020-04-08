// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "NogsBPsStyle.h"

class FNogsBPsCommands : public TCommands<FNogsBPsCommands>
{
public:

	FNogsBPsCommands()
		: TCommands<FNogsBPsCommands>(TEXT("NogsBPs"), NSLOCTEXT("Contexts", "NogsBPs", "NogsBPs Plugin"), NAME_None, FNogsBPsStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};