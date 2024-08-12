// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "../../Public/MariaDBActor.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMariaDBActor() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	MARIADBCONNECTION_API UClass* Z_Construct_UClass_AMariaDBActor();
	MARIADBCONNECTION_API UClass* Z_Construct_UClass_AMariaDBActor_NoRegister();
	UPackage* Z_Construct_UPackage__Script_MariaDBConnection();
// End Cross Module References
	void AMariaDBActor::StaticRegisterNativesAMariaDBActor()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AMariaDBActor);
	UClass* Z_Construct_UClass_AMariaDBActor_NoRegister()
	{
		return AMariaDBActor::StaticClass();
	}
	struct Z_Construct_UClass_AMariaDBActor_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AMariaDBActor_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_MariaDBConnection,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMariaDBActor_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMariaDBActor_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "MariaDBActor.h" },
		{ "ModuleRelativePath", "Public/MariaDBActor.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AMariaDBActor_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMariaDBActor>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AMariaDBActor_Statics::ClassParams = {
		&AMariaDBActor::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AMariaDBActor_Statics::Class_MetaDataParams), Z_Construct_UClass_AMariaDBActor_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_AMariaDBActor()
	{
		if (!Z_Registration_Info_UClass_AMariaDBActor.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AMariaDBActor.OuterSingleton, Z_Construct_UClass_AMariaDBActor_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AMariaDBActor.OuterSingleton;
	}
	template<> MARIADBCONNECTION_API UClass* StaticClass<AMariaDBActor>()
	{
		return AMariaDBActor::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AMariaDBActor);
	AMariaDBActor::~AMariaDBActor() {}
	struct Z_CompiledInDeferFile_FID_Users_kreby_Desktop_Project_RLR_RLR_Plugins_Plugins_MariaDBConnection_Source_MariaDBConnection_Public_MariaDBActor_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_kreby_Desktop_Project_RLR_RLR_Plugins_Plugins_MariaDBConnection_Source_MariaDBConnection_Public_MariaDBActor_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AMariaDBActor, AMariaDBActor::StaticClass, TEXT("AMariaDBActor"), &Z_Registration_Info_UClass_AMariaDBActor, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMariaDBActor), 3921388689U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_kreby_Desktop_Project_RLR_RLR_Plugins_Plugins_MariaDBConnection_Source_MariaDBConnection_Public_MariaDBActor_h_1852204835(TEXT("/Script/MariaDBConnection"),
		Z_CompiledInDeferFile_FID_Users_kreby_Desktop_Project_RLR_RLR_Plugins_Plugins_MariaDBConnection_Source_MariaDBConnection_Public_MariaDBActor_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_kreby_Desktop_Project_RLR_RLR_Plugins_Plugins_MariaDBConnection_Source_MariaDBConnection_Public_MariaDBActor_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
