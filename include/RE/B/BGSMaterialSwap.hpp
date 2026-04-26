#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSMaterialSwap
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSMaterialSwap };
		inline static constexpr auto VTABLE{ VTABLE::BGSMaterialSwap };
		inline static constexpr auto FORM_TYPE{ FormType::kMaterialSwap };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12,
				kCustomSwap = 1 << 16
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		class Entry
		{
		public:
			// members
			BSFixedString swapMaterial;		  // 00
			REX::Float32 colorRemappingIndex; // 08
		};
		static_assert(sizeof(Entry) == 0x10);

		// members
		BSTHashMap<BSFixedString, Entry> swapMap; // 20
	};
	static_assert(sizeof(BGSMaterialSwap) == 0x50);
}
