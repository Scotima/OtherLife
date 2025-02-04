// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "OtherLifeFarm/OtherLifeFarmGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeOtherLifeFarmGameMode() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
OTHERLIFEFARM_API UClass* Z_Construct_UClass_AOtherLifeFarmGameMode();
OTHERLIFEFARM_API UClass* Z_Construct_UClass_AOtherLifeFarmGameMode_NoRegister();
UPackage* Z_Construct_UPackage__Script_OtherLifeFarm();
// End Cross Module References

// Begin Class AOtherLifeFarmGameMode
void AOtherLifeFarmGameMode::StaticRegisterNativesAOtherLifeFarmGameMode()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AOtherLifeFarmGameMode);
UClass* Z_Construct_UClass_AOtherLifeFarmGameMode_NoRegister()
{
	return AOtherLifeFarmGameMode::StaticClass();
}
struct Z_Construct_UClass_AOtherLifeFarmGameMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "OtherLifeFarmGameMode.h" },
		{ "ModuleRelativePath", "OtherLifeFarmGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AOtherLifeFarmGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AOtherLifeFarmGameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_OtherLifeFarm,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AOtherLifeFarmGameMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AOtherLifeFarmGameMode_Statics::ClassParams = {
	&AOtherLifeFarmGameMode::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AOtherLifeFarmGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_AOtherLifeFarmGameMode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AOtherLifeFarmGameMode()
{
	if (!Z_Registration_Info_UClass_AOtherLifeFarmGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AOtherLifeFarmGameMode.OuterSingleton, Z_Construct_UClass_AOtherLifeFarmGameMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AOtherLifeFarmGameMode.OuterSingleton;
}
template<> OTHERLIFEFARM_API UClass* StaticClass<AOtherLifeFarmGameMode>()
{
	return AOtherLifeFarmGameMode::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AOtherLifeFarmGameMode);
AOtherLifeFarmGameMode::~AOtherLifeFarmGameMode() {}
// End Class AOtherLifeFarmGameMode

// Begin Registration
struct Z_CompiledInDeferFile_FID_OtherLifeFarm_Source_OtherLifeFarm_OtherLifeFarmGameMode_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AOtherLifeFarmGameMode, AOtherLifeFarmGameMode::StaticClass, TEXT("AOtherLifeFarmGameMode"), &Z_Registration_Info_UClass_AOtherLifeFarmGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AOtherLifeFarmGameMode), 1936660547U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_OtherLifeFarm_Source_OtherLifeFarm_OtherLifeFarmGameMode_h_2213652285(TEXT("/Script/OtherLifeFarm"),
	Z_CompiledInDeferFile_FID_OtherLifeFarm_Source_OtherLifeFarm_OtherLifeFarmGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_OtherLifeFarm_Source_OtherLifeFarm_OtherLifeFarmGameMode_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
