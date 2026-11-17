#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSOutfit : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSOutfit;
		inline static constexpr const auto& VTABLE = VTABLE::BGSOutfit;
		inline static constexpr auto FORM_TYPE = FormType::Outfit;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		// members
		BSTArray<TESForm*> outfitItems; // 0x20
	};

	static_assert(sizeof(BGSOutfit) == 0x38);
}
