using UnrealBuildTool;

public class CSVLoader : ModuleRules
{
    public CSVLoader(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateIncludePaths.AddRange(new string[] { "CSVLoader/Private" });

        // 일반적으로 필요한 모듈
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

        // Slate 및 SlateCore 추가
        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "ToolMenus" });

        // 에디터 전용 모듈 추가 (UnrealEd, LevelEditor 등)
        if (Target.bBuildEditor)
        {
            PrivateDependencyModuleNames.AddRange(new string[] { "UnrealEd", "LevelEditor", "EditorStyle" });
        }

    }
}