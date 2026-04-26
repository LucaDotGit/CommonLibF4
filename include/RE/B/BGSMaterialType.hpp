#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/N/NiColor.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESModel.hpp"

namespace RE
{
	class __declspec(novtable) BGSMaterialType
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSMaterialType };
		inline static constexpr auto VTABLE{ VTABLE::BGSMaterialType };
		inline static constexpr auto FORM_TYPE{ FormType::kMaterialType };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint32_t
		{
			kNone = 0,
			kStairs = 1 << 0,
			kArrowsStick = 1 << 1,
			kCanTunnel = 1 << 2
		};

		[[nodiscard]] static auto GetMaterialIDMap() -> BSTHashMap<std::uint32_t, BGSMaterialType*>&;

		[[nodiscard]] static BGSMaterialType* GetMaterialTypeByID(std::uint32_t a_materialID);

		// members
		TESModel breakableFXModel;				  // 20
		BGSMaterialType* parentType;			  // 50
		BGSImpactDataSet* havokImpactDataSet;	  // 58
		BSFixedString materialName;				  // 60
		std::uint32_t materialID;				  // 68
		NiColor materialColor;					  // 6C
		REX::Float32 buoyancy;					  // 78
		REX::EnumSet<Flags, std::uint32_t> flags; // 7C
	};
	static_assert(sizeof(BGSMaterialType) == 0x80);
}
