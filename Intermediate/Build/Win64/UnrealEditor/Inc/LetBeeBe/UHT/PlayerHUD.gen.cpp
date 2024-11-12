// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LetBeeBe/Public/PlayerHUD.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePlayerHUD() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AHUD();
LETBEEBE_API UClass* Z_Construct_UClass_APlayerHUD();
LETBEEBE_API UClass* Z_Construct_UClass_APlayerHUD_NoRegister();
UPackage* Z_Construct_UPackage__Script_LetBeeBe();
// End Cross Module References

// Begin Class APlayerHUD
void APlayerHUD::StaticRegisterNativesAPlayerHUD()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(APlayerHUD);
UClass* Z_Construct_UClass_APlayerHUD_NoRegister()
{
	return APlayerHUD::StaticClass();
}
struct Z_Construct_UClass_APlayerHUD_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Rendering Actor Input Replication" },
		{ "IncludePath", "PlayerHUD.h" },
		{ "ModuleRelativePath", "Public/PlayerHUD.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<APlayerHUD>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_APlayerHUD_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AHUD,
	(UObject* (*)())Z_Construct_UPackage__Script_LetBeeBe,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_APlayerHUD_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_APlayerHUD_Statics::ClassParams = {
	&APlayerHUD::StaticClass,
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
	0x009002ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_APlayerHUD_Statics::Class_MetaDataParams), Z_Construct_UClass_APlayerHUD_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_APlayerHUD()
{
	if (!Z_Registration_Info_UClass_APlayerHUD.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_APlayerHUD.OuterSingleton, Z_Construct_UClass_APlayerHUD_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_APlayerHUD.OuterSingleton;
}
template<> LETBEEBE_API UClass* StaticClass<APlayerHUD>()
{
	return APlayerHUD::StaticClass();
}
APlayerHUD::APlayerHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(APlayerHUD);
APlayerHUD::~APlayerHUD() {}
// End Class APlayerHUD

// Begin Registration
struct Z_CompiledInDeferFile_FID_Unreal_Projects_test_LetBeeBe_Source_LetBeeBe_Public_PlayerHUD_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_APlayerHUD, APlayerHUD::StaticClass, TEXT("APlayerHUD"), &Z_Registration_Info_UClass_APlayerHUD, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(APlayerHUD), 1919134840U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Unreal_Projects_test_LetBeeBe_Source_LetBeeBe_Public_PlayerHUD_h_1232989525(TEXT("/Script/LetBeeBe"),
	Z_CompiledInDeferFile_FID_Unreal_Projects_test_LetBeeBe_Source_LetBeeBe_Public_PlayerHUD_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Unreal_Projects_test_LetBeeBe_Source_LetBeeBe_Public_PlayerHUD_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
