#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/N/NiColor.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESModel.hpp"

namespace RE
{
	class __declspec(novtable) BGSMaterialType : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSMaterialType;
		inline static constexpr const auto& VTABLE = VTABLE::BGSMaterialType;
		inline static constexpr auto FORM_TYPE = FormType::MaterialType;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint32_t
		{
			None = 0,
			Stairs = 1 << 0,
			ArrowsStick = 1 << 1,
			CanTunnel = 1 << 2
		};

		[[nodiscard]]
		static auto GetMaterialIDMap() noexcept -> BSTHashMap<std::uint32_t, BGSMaterialType*>&;

		[[nodiscard]]
		static auto GetMaterialTypeByID(std::uint32_t a_materialID) -> BGSMaterialType*;

		// members
		TESModel breakableFXModel;				  // 0x20
		BGSMaterialType* parentType;			  // 0x50
		BGSImpactDataSet* havokImpactDataSet;	  // 0x58
		BSFixedString materialName;				  // 0x60
		std::uint32_t materialID;				  // 0x68
		NiColor materialColor;					  // 0x6C
		REX::Float32 buoyancy;					  // 0x78
		REX::EnumSet<Flags, std::uint32_t> flags; // 0x7C
	};

	static_assert(sizeof(BGSMaterialType) == 0x80);
}
