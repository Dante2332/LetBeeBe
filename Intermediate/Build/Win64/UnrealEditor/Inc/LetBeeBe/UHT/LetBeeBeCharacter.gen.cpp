// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LetBeeBe/LetBeeBeCharacter.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLetBeeBeCharacter() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_ACharacter();
ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UCurveFloat_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USpringArmComponent_NoRegister();
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputAction_NoRegister();
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputMappingContext_NoRegister();
LETBEEBE_API UClass* Z_Construct_UClass_ALetBeeBeCharacter();
LETBEEBE_API UClass* Z_Construct_UClass_ALetBeeBeCharacter_NoRegister();
UPackage* Z_Construct_UPackage__Script_LetBeeBe();
// End Cross Module References

// Begin Class ALetBeeBeCharacter Function HandleCameraZoomProgress
struct Z_Construct_UFunction_ALetBeeBeCharacter_HandleCameraZoomProgress_Statics
{
	struct LetBeeBeCharacter_eventHandleCameraZoomProgress_Parms
	{
		float Value;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "LetBeeBeCharacter.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Value;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ALetBeeBeCharacter_HandleCameraZoomProgress_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(LetBeeBeCharacter_eventHandleCameraZoomProgress_Parms, Value), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ALetBeeBeCharacter_HandleCameraZoomProgress_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ALetBeeBeCharacter_HandleCameraZoomProgress_Statics::NewProp_Value,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ALetBeeBeCharacter_HandleCameraZoomProgress_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ALetBeeBeCharacter_HandleCameraZoomProgress_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ALetBeeBeCharacter, nullptr, "HandleCameraZoomProgress", nullptr, nullptr, Z_Construct_UFunction_ALetBeeBeCharacter_HandleCameraZoomProgress_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ALetBeeBeCharacter_HandleCameraZoomProgress_Statics::PropPointers), sizeof(Z_Construct_UFunction_ALetBeeBeCharacter_HandleCameraZoomProgress_Statics::LetBeeBeCharacter_eventHandleCameraZoomProgress_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ALetBeeBeCharacter_HandleCameraZoomProgress_Statics::Function_MetaDataParams), Z_Construct_UFunction_ALetBeeBeCharacter_HandleCameraZoomProgress_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_ALetBeeBeCharacter_HandleCameraZoomProgress_Statics::LetBeeBeCharacter_eventHandleCameraZoomProgress_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ALetBeeBeCharacter_HandleCameraZoomProgress()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ALetBeeBeCharacter_HandleCameraZoomProgress_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ALetBeeBeCharacter::execHandleCameraZoomProgress)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_Value);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleCameraZoomProgress(Z_Param_Value);
	P_NATIVE_END;
}
// End Class ALetBeeBeCharacter Function HandleCameraZoomProgress

// Begin Class ALetBeeBeCharacter
void ALetBeeBeCharacter::StaticRegisterNativesALetBeeBeCharacter()
{
	UClass* Class = ALetBeeBeCharacter::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "HandleCameraZoomProgress", &ALetBeeBeCharacter::execHandleCameraZoomProgress },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ALetBeeBeCharacter);
UClass* Z_Construct_UClass_ALetBeeBeCharacter_NoRegister()
{
	return ALetBeeBeCharacter::StaticClass();
}
struct Z_Construct_UClass_ALetBeeBeCharacter_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "LetBeeBeCharacter.h" },
		{ "ModuleRelativePath", "LetBeeBeCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CameraBoom_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Camera" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Camera boom positioning the camera behind the character */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "LetBeeBeCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Camera boom positioning the camera behind the character" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FollowCamera_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Camera" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Follow camera */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "LetBeeBeCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Follow camera" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultMappingContext_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** MappingContext */" },
#endif
		{ "ModuleRelativePath", "LetBeeBeCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "MappingContext" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_JumpAction_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Jump Input Action */" },
#endif
		{ "ModuleRelativePath", "LetBeeBeCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Jump Input Action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SprintAction_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
		{ "ModuleRelativePath", "LetBeeBeCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MoveAction_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Move Input Action */" },
#endif
		{ "ModuleRelativePath", "LetBeeBeCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Move Input Action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LookAction_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Look Input Action */" },
#endif
		{ "ModuleRelativePath", "LetBeeBeCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Look Input Action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AimAction_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Aim Input Action */" },
#endif
		{ "ModuleRelativePath", "LetBeeBeCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Aim Input Action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ShootAction_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Shoot Input Action */" },
#endif
		{ "ModuleRelativePath", "LetBeeBeCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Shoot Input Action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CameraZoomCurve_MetaData[] = {
		{ "Category", "Camera" },
		{ "ModuleRelativePath", "LetBeeBeCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StartWalkSpeed_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
		{ "ModuleRelativePath", "LetBeeBeCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Sensitivity_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
		{ "ModuleRelativePath", "LetBeeBeCharacter.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CameraBoom;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FollowCamera;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DefaultMappingContext;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_JumpAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SprintAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MoveAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LookAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AimAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ShootAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CameraZoomCurve;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_StartWalkSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Sensitivity;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ALetBeeBeCharacter_HandleCameraZoomProgress, "HandleCameraZoomProgress" }, // 2422740245
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ALetBeeBeCharacter>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ALetBeeBeCharacter_Statics::NewProp_CameraBoom = { "CameraBoom", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALetBeeBeCharacter, CameraBoom), Z_Construct_UClass_USpringArmComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CameraBoom_MetaData), NewProp_CameraBoom_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ALetBeeBeCharacter_Statics::NewProp_FollowCamera = { "FollowCamera", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALetBeeBeCharacter, FollowCamera), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FollowCamera_MetaData), NewProp_FollowCamera_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ALetBeeBeCharacter_Statics::NewProp_DefaultMappingContext = { "DefaultMappingContext", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALetBeeBeCharacter, DefaultMappingContext), Z_Construct_UClass_UInputMappingContext_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultMappingContext_MetaData), NewProp_DefaultMappingContext_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ALetBeeBeCharacter_Statics::NewProp_JumpAction = { "JumpAction", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALetBeeBeCharacter, JumpAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_JumpAction_MetaData), NewProp_JumpAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ALetBeeBeCharacter_Statics::NewProp_SprintAction = { "SprintAction", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALetBeeBeCharacter, SprintAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SprintAction_MetaData), NewProp_SprintAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ALetBeeBeCharacter_Statics::NewProp_MoveAction = { "MoveAction", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALetBeeBeCharacter, MoveAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MoveAction_MetaData), NewProp_MoveAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ALetBeeBeCharacter_Statics::NewProp_LookAction = { "LookAction", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALetBeeBeCharacter, LookAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LookAction_MetaData), NewProp_LookAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ALetBeeBeCharacter_Statics::NewProp_AimAction = { "AimAction", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALetBeeBeCharacter, AimAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AimAction_MetaData), NewProp_AimAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ALetBeeBeCharacter_Statics::NewProp_ShootAction = { "ShootAction", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALetBeeBeCharacter, ShootAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ShootAction_MetaData), NewProp_ShootAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ALetBeeBeCharacter_Statics::NewProp_CameraZoomCurve = { "CameraZoomCurve", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALetBeeBeCharacter, CameraZoomCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CameraZoomCurve_MetaData), NewProp_CameraZoomCurve_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ALetBeeBeCharacter_Statics::NewProp_StartWalkSpeed = { "StartWalkSpeed", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALetBeeBeCharacter, StartWalkSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StartWalkSpeed_MetaData), NewProp_StartWalkSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ALetBeeBeCharacter_Statics::NewProp_Sensitivity = { "Sensitivity", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALetBeeBeCharacter, Sensitivity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Sensitivity_MetaData), NewProp_Sensitivity_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ALetBeeBeCharacter_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALetBeeBeCharacter_Statics::NewProp_CameraBoom,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALetBeeBeCharacter_Statics::NewProp_FollowCamera,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALetBeeBeCharacter_Statics::NewProp_DefaultMappingContext,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALetBeeBeCharacter_Statics::NewProp_JumpAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALetBeeBeCharacter_Statics::NewProp_SprintAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALetBeeBeCharacter_Statics::NewProp_MoveAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALetBeeBeCharacter_Statics::NewProp_LookAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALetBeeBeCharacter_Statics::NewProp_AimAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALetBeeBeCharacter_Statics::NewProp_ShootAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALetBeeBeCharacter_Statics::NewProp_CameraZoomCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALetBeeBeCharacter_Statics::NewProp_StartWalkSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALetBeeBeCharacter_Statics::NewProp_Sensitivity,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ALetBeeBeCharacter_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ALetBeeBeCharacter_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_ACharacter,
	(UObject* (*)())Z_Construct_UPackage__Script_LetBeeBe,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ALetBeeBeCharacter_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ALetBeeBeCharacter_Statics::ClassParams = {
	&ALetBeeBeCharacter::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_ALetBeeBeCharacter_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_ALetBeeBeCharacter_Statics::PropPointers),
	0,
	0x008000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ALetBeeBeCharacter_Statics::Class_MetaDataParams), Z_Construct_UClass_ALetBeeBeCharacter_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ALetBeeBeCharacter()
{
	if (!Z_Registration_Info_UClass_ALetBeeBeCharacter.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ALetBeeBeCharacter.OuterSingleton, Z_Construct_UClass_ALetBeeBeCharacter_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ALetBeeBeCharacter.OuterSingleton;
}
template<> LETBEEBE_API UClass* StaticClass<ALetBeeBeCharacter>()
{
	return ALetBeeBeCharacter::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ALetBeeBeCharacter);
ALetBeeBeCharacter::~ALetBeeBeCharacter() {}
// End Class ALetBeeBeCharacter

// Begin Registration
struct Z_CompiledInDeferFile_FID_Unreal_Projects_test_LetBeeBe_Source_LetBeeBe_LetBeeBeCharacter_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ALetBeeBeCharacter, ALetBeeBeCharacter::StaticClass, TEXT("ALetBeeBeCharacter"), &Z_Registration_Info_UClass_ALetBeeBeCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ALetBeeBeCharacter), 219602137U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Unreal_Projects_test_LetBeeBe_Source_LetBeeBe_LetBeeBeCharacter_h_2232958344(TEXT("/Script/LetBeeBe"),
	Z_CompiledInDeferFile_FID_Unreal_Projects_test_LetBeeBe_Source_LetBeeBe_LetBeeBeCharacter_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Unreal_Projects_test_LetBeeBe_Source_LetBeeBe_LetBeeBeCharacter_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
