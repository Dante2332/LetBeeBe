// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "PlayerHUD.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef LETBEEBE_PlayerHUD_generated_h
#error "PlayerHUD.generated.h already included, missing '#pragma once' in PlayerHUD.h"
#endif
#define LETBEEBE_PlayerHUD_generated_h

#define FID_Unreal_Projects_test_LetBeeBe_Source_LetBeeBe_Public_PlayerHUD_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAPlayerHUD(); \
	friend struct Z_Construct_UClass_APlayerHUD_Statics; \
public: \
	DECLARE_CLASS(APlayerHUD, AHUD, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/LetBeeBe"), NO_API) \
	DECLARE_SERIALIZER(APlayerHUD)


#define FID_Unreal_Projects_test_LetBeeBe_Source_LetBeeBe_Public_PlayerHUD_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API APlayerHUD(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	APlayerHUD(APlayerHUD&&); \
	APlayerHUD(const APlayerHUD&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, APlayerHUD); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(APlayerHUD); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(APlayerHUD) \
	NO_API virtual ~APlayerHUD();


#define FID_Unreal_Projects_test_LetBeeBe_Source_LetBeeBe_Public_PlayerHUD_h_12_PROLOG
#define FID_Unreal_Projects_test_LetBeeBe_Source_LetBeeBe_Public_PlayerHUD_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Unreal_Projects_test_LetBeeBe_Source_LetBeeBe_Public_PlayerHUD_h_15_INCLASS_NO_PURE_DECLS \
	FID_Unreal_Projects_test_LetBeeBe_Source_LetBeeBe_Public_PlayerHUD_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LETBEEBE_API UClass* StaticClass<class APlayerHUD>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Unreal_Projects_test_LetBeeBe_Source_LetBeeBe_Public_PlayerHUD_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
