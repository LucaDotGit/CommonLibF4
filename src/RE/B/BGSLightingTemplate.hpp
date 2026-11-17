#pragma once

#include "RE/B/BGSDirectionalAmbientLightingColors.hpp"
#include "RE/I/INTERIOR_DATA.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSLightingTemplate : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSLightingTemplate;
		inline static constexpr const auto& VTABLE = VTABLE::BGSLightingTemplate;
		inline static constexpr auto FORM_TYPE = FormType::LightingTemplate;

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
		INTERIOR_DATA data;													  // 0x20
		BGSGodRays* godRays;												  // 0xB0
		BGSDirectionalAmbientLightingColors directionalAmbientLightingColors; // 0xB8
	};

	static_assert(sizeof(BGSLightingTemplate) == 0xD8);
}
