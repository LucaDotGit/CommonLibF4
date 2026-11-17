#pragma once

#include "RE/B/BSLensFlareRenderData.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSLensFlare :
		public TESForm,				 // 0x00
		public BSLensFlareRenderData // 0x20
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSLensFlare;
		inline static constexpr const auto& VTABLE = VTABLE::BGSLensFlare;
		inline static constexpr auto FORM_TYPE = FormType::LensFlare;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;
	};

	static_assert(sizeof(BGSLensFlare) == 0x50);
}
