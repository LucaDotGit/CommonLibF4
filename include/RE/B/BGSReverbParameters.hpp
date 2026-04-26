#pragma once

#include "RE/B/BSIReverbType.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSReverbParameters
		: public TESForm,	   // 00
		  public BSIReverbType // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSReverbParameters };
		inline static constexpr auto VTABLE{ VTABLE::BGSReverbParameters };
		inline static constexpr auto FORM_TYPE{ FormType::kReverbParameters };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		enum class ReverbClass : std::int32_t
		{
			kDefault = 0,
			kClassA = 1,
			kClassB = 2,
			kClassC = 3,
			kClassD = 4,
			kClassE = 5
		};

		class ReverbParams
		{
		public:
			// members
			std::uint16_t decayTime;	 // 00
			std::uint16_t hfReference;	 // 02
			std::int8_t roomFilter;		 // 04
			std::int8_t roomHFFilter;	 // 05
			std::int8_t reflections;	 // 06
			std::int8_t reverb;			 // 07
			std::int8_t decayHFRatio;	 // 08
			std::int8_t reflectionDelay; // 09
			std::int8_t reverbDelay;	 // 0A
			std::int8_t diffusionPct;	 // 0B
			std::int8_t densityPct;		 // 0C
		};
		static_assert(sizeof(ReverbParams) == 0x0E);

		// members
		ReverbParams data;		   // 28
		std::uint32_t reverbClass; // 38
	};
	static_assert(sizeof(BGSReverbParameters) == 0x40);
}
