#pragma once

#include "RE/R/RepeaterData.hpp"
#include "RE/T/TESBoundAnimObject.hpp"

namespace RE
{
	class __declspec(novtable) TESSound
		: public TESBoundAnimObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESSound };
		inline static constexpr auto VTABLE{ VTABLE::TESSound };
		inline static constexpr auto FORM_TYPE{ FormType::kSoundMarker };

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
		BGSSoundDescriptorForm* descriptor;	   // 68
		TESSoundDefs::RepeaterData repeatData; // 70
	};
	static_assert(sizeof(TESSound) == 0x80);
}
