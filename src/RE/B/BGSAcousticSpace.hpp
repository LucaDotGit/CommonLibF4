#pragma once

#include "RE/T/TESBoundObject.hpp"

namespace RE
{
	class __declspec(novtable) BGSAcousticSpace : public TESBoundObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSAcousticSpace;
		inline static constexpr const auto& VTABLE = VTABLE::BGSAcousticSpace;
		inline static constexpr auto FORM_TYPE = FormType::AcousticSpace;

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
		BGSSoundDescriptorForm* loopingSound; // 0x68
		TESRegion* soundRegion;				  // 0x70
		BGSReverbParameters* reverbType;	  // 0x78
		std::uint16_t weatherAttenMillibels;  // 0x80
		bool isInterior;					  // 0x82
	};

	static_assert(sizeof(BGSAcousticSpace) == 0x88);
}
