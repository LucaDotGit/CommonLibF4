#pragma once

#include "RE/B/BSLensFlareRenderData.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSLensFlare
		: public TESForm,			   // 00
		  public BSLensFlareRenderData // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSLensFlare };
		inline static constexpr auto VTABLE{ VTABLE::BGSLensFlare };
		inline static constexpr auto FORM_TYPE{ FormType::kLensFlare };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;
	};
	static_assert(sizeof(BGSLensFlare) == 0x50);
}
