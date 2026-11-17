#pragma once

#include "RE/B/BSIReverbType.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSReverbParameters :
		public TESForm,		 // 0x00
		public BSIReverbType // 0x20
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSReverbParameters;
		inline static constexpr const auto& VTABLE = VTABLE::BGSReverbParameters;
		inline static constexpr auto FORM_TYPE = FormType::ReverbParameters;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		enum class ReverbClass : std::int32_t
		{
			Default = 0,
			ClassA = 1,
			ClassB = 2,
			ClassC = 3,
			ClassD = 4,
			ClassE = 5
		};

		class ReverbParams
		{
		public:
			// members
			std::uint16_t decayTime;	 // 0x00
			std::uint16_t hfReference;	 // 0x02
			std::int8_t roomFilter;		 // 0x04
			std::int8_t roomHFFilter;	 // 0x05
			std::int8_t reflections;	 // 0x06
			std::int8_t reverb;			 // 0x07
			std::int8_t decayHFRatio;	 // 0x08
			std::int8_t reflectionDelay; // 0x09
			std::int8_t reverbDelay;	 // 0x0A
			std::int8_t diffusionPct;	 // 0x0B
			std::int8_t densityPct;		 // 0x0C
		};

		static_assert(sizeof(ReverbParams) == 0x0E);

		// members
		ReverbParams data;		   // 0x28
		std::uint32_t reverbClass; // 0x38
	};

	static_assert(sizeof(BGSReverbParameters) == 0x40);
}
