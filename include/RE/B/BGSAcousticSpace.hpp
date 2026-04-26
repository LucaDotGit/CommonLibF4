#pragma once

#include "RE/T/TESBoundObject.hpp"

namespace RE
{
	class __declspec(novtable) BGSAcousticSpace
		: public TESBoundObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSAcousticSpace };
		inline static constexpr auto VTABLE{ VTABLE::BGSAcousticSpace };
		inline static constexpr auto FORM_TYPE{ FormType::kAcousticSpace };

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
		BGSSoundDescriptorForm* loopingSound; // 68
		TESRegion* soundRegion;				  // 70
		BGSReverbParameters* reverbType;	  // 78
		std::uint16_t weatherAttenMillibels;  // 80
		bool isInterior;					  // 82
	};
	static_assert(sizeof(BGSAcousticSpace) == 0x88);
}
