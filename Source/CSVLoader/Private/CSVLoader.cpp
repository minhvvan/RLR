// MyCustomModule.cpp

#include "CSVLoader.h"
#include "LevelEditor.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "ToolMenus.h"

IMPLEMENT_MODULE(FCSVLoader, CSVLoader)

void FCSVLoader::StartupModule()
{
	UE_LOG(LogTemp, Log, TEXT("CSVLoader Module Started"));
	AddToolbarButton();
}

void FCSVLoader::ShutdownModule()
{
	RemoveToolbarButton();
}

void FCSVLoader::AddToolbarButton()
{
	// LevelEditor 모듈을 가져와서 툴바에 커스텀 버튼 추가
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	MenuExtender = MakeShareable(new FExtender);
	MenuExtender->AddMenuBarExtension(
		"Help",
		EExtensionHook::After,
		nullptr,
		FMenuBarExtensionDelegate::CreateLambda([](FMenuBarBuilder& Builder)
			{
				Builder.AddMenuEntry(
					FText::FromString("Load DataTable"),
					FText::FromString("Click to Load CSV"),
					FSlateIcon(),
					FUIAction(FExecuteAction::CreateLambda([]() {
						FString PythonScriptPath = FPaths::Combine(FPaths::ProjectContentDir(), "Python", "CSVLoader", "asset_generator.py");
						PythonScriptPath = FPaths::ConvertRelativePathToFull(PythonScriptPath);
						PythonScriptPath.InsertAt(0, "py ");
						GEngine->Exec(nullptr, *PythonScriptPath);
						}))
				);
			})
	);

	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
}

void FCSVLoader::RemoveToolbarButton()
{
	if (!MenuExtender.IsValid()) return;

	// LevelEditor 모듈에서 Extender 제거
	FLevelEditorModule* LevelEditorModule = FModuleManager::GetModulePtr<FLevelEditorModule>("LevelEditor");
	if (LevelEditorModule != nullptr)
	{
		LevelEditorModule->GetMenuExtensibilityManager()->RemoveExtender(MenuExtender);
	}

	// Extender가 유효하지 않도록 제거
	MenuExtender.Reset();
}