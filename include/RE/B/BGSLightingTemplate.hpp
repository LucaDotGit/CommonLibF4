#pragma once

#include "RE/B/BGSDirectionalAmbientLightingColors.hpp"
#include "RE/I/INTERIOR_DATA.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSLightingTemplate
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSLightingTemplate };
		inline static constexpr auto VTABLE{ VTABLE::BGSLightingTemplate };
		inline static constexpr auto FORM_TYPE{ FormType::kLightingTemplate };

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
		INTERIOR_DATA data;													  // 20
		BGSGodRays* godRays;												  // B0
		BGSDirectionalAmbientLightingColors directionalAmbientLightingColors; // B8
	};
	static_assert(sizeof(BGSLightingTemplate) == 0xD8);
}
