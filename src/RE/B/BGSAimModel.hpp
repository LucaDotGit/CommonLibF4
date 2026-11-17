#pragma once

#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSAimModel : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSAimModel;
		inline static constexpr const auto& VTABLE = VTABLE::BGSAimModel;
		inline static constexpr auto FORM_TYPE = FormType::AimModel;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		class Data
		{
		public:
			// members
			REX::Float32 minConeDegrees;			// 0x00
			REX::Float32 maxConeDegrees;			// 0x04
			REX::Float32 coneIncreasePerShot;		// 0x08
			REX::Float32 coneDecreasePerSec;		// 0x0C
			std::uint32_t coneDecreaseDelayMs;		// 0x10
			REX::Float32 coneSneakMultiplier;		// 0x14
			REX::Float32 recoilDiminishSpringForce; // 0x18
			REX::Float32 recoilDiminishSightsMult;	// 0x1C
			REX::Float32 recoilMaxDegPerShot;		// 0x20
			REX::Float32 recoilMinDegPerShot;		// 0x24
			REX::Float32 recoilHipMult;				// 0x28
			std::uint32_t recoilShotsForRunaway;	// 0x2C
			REX::Float32 recoilArcDeg;				// 0x30
			REX::Float32 recoilArcRotateDeg;		// 0x34
			REX::Float32 coneIronSightsMultiplier;	// 0x38
			REX::Float32 baseStability;				// 0x3C
		};

		static_assert(sizeof(Data) == 0x40);

		// members
		Data data; // 0x20
	};

	static_assert(sizeof(BGSAimModel) == 0x60);
}
