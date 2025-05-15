// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeOtherLifeFarm_init() {}
	OTHERLIFEFARM_API UFunction* Z_Construct_UDelegateFunction_OtherLifeFarm_OnCancelPressed__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_OtherLifeFarm;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_OtherLifeFarm()
	{
		if (!Z_Registration_Info_UPackage__Script_OtherLifeFarm.OuterSingleton)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_OtherLifeFarm_OnCancelPressed__DelegateSignature,
			};
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/OtherLifeFarm",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0xEF0BB6B6,
				0xD0FE6AA4,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_OtherLifeFarm.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_OtherLifeFarm.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_OtherLifeFarm(Z_Construct_UPackage__Script_OtherLifeFarm, TEXT("/Script/OtherLifeFarm"), Z_Registration_Info_UPackage__Script_OtherLifeFarm, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0xEF0BB6B6, 0xD0FE6AA4));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
