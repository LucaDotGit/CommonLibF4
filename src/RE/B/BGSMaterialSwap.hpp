#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSMaterialSwap : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSMaterialSwap;
		inline static constexpr const auto& VTABLE = VTABLE::BGSMaterialSwap;
		inline static constexpr auto FORM_TYPE = FormType::MaterialSwap;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12,
				CustomSwap = 1 << 16
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		class Entry
		{
		public:
			// members
			BSFixedString swapMaterial;		  // 0x00
			REX::Float32 colorRemappingIndex; // 0x08
		};

		static_assert(sizeof(Entry) == 0x10);

		// members
		BSTHashMap<BSFixedString, Entry> swapMap; // 0x20
	};

	static_assert(sizeof(BGSMaterialSwap) == 0x50);
}
