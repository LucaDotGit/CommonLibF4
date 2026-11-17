#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSFootstep : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSFootstep;
		inline static constexpr const auto& VTABLE = VTABLE::BGSFootstep;
		inline static constexpr auto FORM_TYPE = FormType::Footstep;

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
		BSFixedString tagString;	 // 0x20
		BGSImpactDataSet* impactSet; // 0x28
	};

	static_assert(sizeof(BGSFootstep) == 0x30);
}
