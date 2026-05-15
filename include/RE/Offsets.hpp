#pragma once

// NOLINTBEGIN(modernize-concat-nested-namespaces)

namespace RE::Offset
{
	namespace ActorValueInfo
	{
		inline constexpr auto RuntimeData01 = F4SE::CreateVariantOffset(0x068, 0x088, 0x088);
		inline constexpr auto RuntimeData02 = F4SE::CreateVariantOffset(0x110, 0x150, 0x150);
		inline constexpr auto ModifiedCallback = F4SE::CreateVariantOffset(0x048, 0x048, 0x048);
		inline constexpr auto DerivationFunction = F4SE::CreateVariantOffset(0x0F0, 0x110, 0x110);
	}

	namespace BGSLocalizedStringDL
	{
		inline constexpr auto StringInfoMap = F4SE::CreateVariantOffset(-0x08, 0x00, 0x00);
	}

	namespace BGSLocalizedStringIL
	{
		inline constexpr auto StringInfoMap = F4SE::CreateVariantOffset(-0x08, 0x00, 0x00);
	}

	namespace BGSLocalizedStringPL
	{
		inline constexpr auto StringInfoMap = F4SE::CreateVariantOffset(-0x08, 0x00, 0x00);
	}

	namespace BGSLocation
	{
		inline constexpr auto LinkedLocations = F4SE::CreateVariantOffset(-0x08, 0x00, 0x00);
	}

	namespace BGSMaterialType
	{
		inline constexpr auto MaterialIDMap = F4SE::CreateVariantOffset(-0x08, 0x00, 0x00);
	}

	namespace BGSMod
	{
		namespace Attachment
		{
			inline constexpr auto LooseModMap = F4SE::CreateVariantOffset(-0x08, 0x00, 0x00);
		}
	}

	namespace BSTimer
	{
		inline constexpr auto RuntimeData = F4SE::CreateVariantOffset(0x20, 0x20, 0x30);
	}

	namespace GameVM
	{
		inline constexpr auto RuntimeData = F4SE::CreateVariantOffset(0x5F0, 0x5F0, 0x600);
	}

	namespace NiAlphaProperty
	{
		inline constexpr auto SetTestMode = F4SE::CreateVariantOffset(0x20, 0x00, 0x00);
		inline constexpr auto SetAlphaTesting = F4SE::CreateVariantOffset(0x20, 0x00, 0x00);
	}

	namespace NiNode
	{
		inline constexpr auto RuntimeData = F4SE::CreateVRVariantOffset(0x160, 0x120, 0x120, 0x120);
	}

	namespace TESDataHandler
	{
		inline constexpr auto RuntimeData = F4SE::CreateVariantOffset(0xFF0, 0xFF0, 0xFF0);
		inline constexpr auto VRModData = F4SE::CreateVRVariantOffset(0xFC0, 0x00, 0x00, 0x00);
		inline constexpr auto CompiledFileCollection = F4SE::CreateVRVariantOffset(0x00, 0xFC0, 0xFC0, 0xFC0);
		inline constexpr auto RegionDataManager = F4SE::CreateVRVariantOffset(0x17E8, 0x1018, 0x1018, 0x1018);
	}

	namespace TESFullName
	{
		inline constexpr auto SparseFullNameMap = F4SE::CreateVariantOffset(-0x08, 0x00, 0x00);
	}

	namespace TESLeveledList
	{
		inline constexpr auto SpecialChanceGlobalMap = F4SE::CreateVariantOffset(-0x08, 0x00, 0x00);
	}

	namespace TESLevItem
	{
		inline constexpr auto OverrideNameMap = F4SE::CreateVariantOffset(-0x08, 0x00, 0x00);
	}

	namespace TESNPC
	{
		inline constexpr auto AlternateHeadPartListMap = F4SE::CreateVariantOffset(-0x08, 0x00, 0x00);
	}

	namespace UI
	{
		inline constexpr auto RuntimeData = F4SE::CreateVariantOffset(0x248, 0x248, 0x258);
	}
}

// NOLINTEND(modernize-concat-nested-namespaces)
