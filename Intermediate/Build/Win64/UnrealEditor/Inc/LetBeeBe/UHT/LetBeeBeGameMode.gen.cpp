// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LetBeeBe/LetBeeBeGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLetBeeBeGameMode() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
LETBEEBE_API UClass* Z_Construct_UClass_ALetBeeBeGameMode();
LETBEEBE_API UClass* Z_Construct_UClass_ALetBeeBeGameMode_NoRegister();
UPackage* Z_Construct_UPackage__Script_LetBeeBe();
// End Cross Module References

// Begin Class ALetBeeBeGameMode
void ALetBeeBeGameMode::StaticRegisterNativesALetBeeBeGameMode()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ALetBeeBeGameMode);
UClass* Z_Construct_UClass_ALetBeeBeGameMode_NoRegister()
{
	return ALetBeeBeGameMode::StaticClass();
}
struct Z_Construct_UClass_ALetBeeBeGameMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "LetBeeBeGameMode.h" },
		{ "ModuleRelativePath", "LetBeeBeGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ALetBeeBeGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_ALetBeeBeGameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_LetBeeBe,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ALetBeeBeGameMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ALetBeeBeGameMode_Statics::ClassParams = {
	&ALetBeeBeGameMode::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x008802ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ALetBeeBeGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_ALetBeeBeGameMode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ALetBeeBeGameMode()
{
	if (!Z_Registration_Info_UClass_ALetBeeBeGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ALetBeeBeGameMode.OuterSingleton, Z_Construct_UClass_ALetBeeBeGameMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ALetBeeBeGameMode.OuterSingleton;
}
template<> LETBEEBE_API UClass* StaticClass<ALetBeeBeGameMode>()
{
	return ALetBeeBeGameMode::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ALetBeeBeGameMode);
ALetBeeBeGameMode::~ALetBeeBeGameMode() {}
// End Class ALetBeeBeGameMode

// Begin Registration
struct Z_CompiledInDeferFile_FID_Unreal_Projects_test_LetBeeBe_Source_LetBeeBe_LetBeeBeGameMode_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ALetBeeBeGameMode, ALetBeeBeGameMode::StaticClass, TEXT("ALetBeeBeGameMode"), &Z_Registration_Info_UClass_ALetBeeBeGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ALetBeeBeGameMode), 2736950663U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Unreal_Projects_test_LetBeeBe_Source_LetBeeBe_LetBeeBeGameMode_h_39578901(TEXT("/Script/LetBeeBe"),
	Z_CompiledInDeferFile_FID_Unreal_Projects_test_LetBeeBe_Source_LetBeeBe_LetBeeBeGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Unreal_Projects_test_LetBeeBe_Source_LetBeeBe_LetBeeBeGameMode_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
