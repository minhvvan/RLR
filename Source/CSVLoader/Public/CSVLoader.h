#pragma once

#include "Framework/Commands/Commands.h"
#include "Modules/ModuleManager.h"

class FCSVLoader : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

private:
    void AddToolbarButton();
    void RemoveToolbarButton();

    TSharedPtr<class FExtender> MenuExtender;
};