#pragma once

#include "RE/I/ImageSpaceBaseData.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESTexture.hpp"

namespace RE
{
	class NiTexture;

	class __declspec(novtable) TESImageSpace
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESImageSpace };
		inline static constexpr auto VTABLE{ VTABLE::TESImageSpace };
		inline static constexpr auto FORM_TYPE{ FormType::kImageSpace };

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
		ImageSpaceBaseData data;		   // 20
		TESTexture lutTexture;			   // 78
		NiPointer<NiTexture> niLutTexture; // 88
	};
	static_assert(sizeof(TESImageSpace) == 0x90);
}
