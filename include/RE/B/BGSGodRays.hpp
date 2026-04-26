#pragma once

#include "RE/N/NiColor.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSGodRays
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSGodRays };
		inline static constexpr auto VTABLE{ VTABLE::BGSGodRays };
		inline static constexpr auto FORM_TYPE{ FormType::kGodRays };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		class GodRaysData
		{
		public:
			// members
			NiColor colorAir;		  // 00
			NiColor colorBack;		  // 0C
			NiColor colorFwd;		  // 18
			REX::Float32 intensity;	  // 24
			REX::Float32 scatterAir;  // 28
			REX::Float32 scatterBack; // 2C
			REX::Float32 scatterFwd;  // 30
			REX::Float32 phaseBack;	  // 34
			REX::Float32 phaseFwd;	  // 38
		};
		static_assert(sizeof(GodRaysData) == 0x3C);

		// members
		GodRaysData data; // 20
	};
	static_assert(sizeof(BGSGodRays) == 0x60);
}
