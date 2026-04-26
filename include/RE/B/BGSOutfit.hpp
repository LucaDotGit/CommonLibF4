#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSOutfit
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSOutfit };
		inline static constexpr auto VTABLE{ VTABLE::BGSOutfit };
		inline static constexpr auto FORM_TYPE{ FormType::kOutfit };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		// members
		BSTArray<TESForm*> outfitItems; // 20
	};
	static_assert(sizeof(BGSOutfit) == 0x38);
}
