#pragma once

#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSAimModel
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSAimModel };
		inline static constexpr auto VTABLE{ VTABLE::BGSAimModel };
		inline static constexpr auto FORM_TYPE{ FormType::kAimModel };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		class Data
		{
		public:
			// members
			REX::Float32 minConeDegrees;			// 00
			REX::Float32 maxConeDegrees;			// 04
			REX::Float32 coneIncreasePerShot;		// 08
			REX::Float32 coneDecreasePerSec;		// 0C
			std::uint32_t coneDecreaseDelayMs;		// 10
			REX::Float32 coneSneakMultiplier;		// 14
			REX::Float32 recoilDiminishSpringForce; // 18
			REX::Float32 recoilDiminishSightsMult;	// 1C
			REX::Float32 recoilMaxDegPerShot;		// 20
			REX::Float32 recoilMinDegPerShot;		// 24
			REX::Float32 recoilHipMult;				// 28
			std::uint32_t recoilShotsForRunaway;	// 2C
			REX::Float32 recoilArcDeg;				// 30
			REX::Float32 recoilArcRotateDeg;		// 34
			REX::Float32 coneIronSightsMultiplier;	// 38
			REX::Float32 baseStability;				// 3C
		};
		static_assert(sizeof(Data) == 0x40);

		// members
		Data data; // 20
	};
	static_assert(sizeof(BGSAimModel) == 0x60);
}
