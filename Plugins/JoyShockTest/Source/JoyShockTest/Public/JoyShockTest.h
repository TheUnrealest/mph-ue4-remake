// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

#define JOYSHOCK_DEBUG true	// Cambialo per attivare/disattivare funzionalità di debug.
							// Se impostato su false, il preprocessore spoglierà dal codice tutte le funzionalità di debug.

#define JOYSHOCK_STARTUPCONNECT true	// Connetti i Joy-Con all'avvio del plugin. O all'avvio dell'editor, decidi tu.

DECLARE_LOG_CATEGORY_EXTERN(JoyShockPlugin, Display, All);

class FJoyShockTestModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	/** Handle to the test dll we will load */
	void*	ExampleLibraryHandle;
};
