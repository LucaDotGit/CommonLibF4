#pragma once

#include "RE/R/RepeaterData.hpp"
#include "RE/T/TESBoundAnimObject.hpp"

namespace RE
{
	class __declspec(novtable) TESSound : public TESBoundAnimObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESSound;
		inline static constexpr const auto& VTABLE = VTABLE::TESSound;
		inline static constexpr auto FORM_TYPE = FormType::SoundMarker;

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
		BGSSoundDescriptorForm* descriptor;	   // 0x68
		TESSoundDefs::RepeaterData repeatData; // 0x70
	};

	static_assert(sizeof(TESSound) == 0x80);
}
