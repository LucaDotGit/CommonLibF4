#pragma once

#include "RE/N/NiColor.hpp"
#include "RE/T/TESBoundObject.hpp"

namespace RE
{
	class __declspec(novtable) BGSBendableSpline
		: public TESBoundObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSBendableSpline };
		inline static constexpr auto VTABLE{ VTABLE::BGSBendableSpline };
		inline static constexpr auto FORM_TYPE{ FormType::kBendableSpline };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		class SplineData_Untilv130
		{
		public:
			// members
			REX::Float32 numTiles;	 // 00
			std::uint16_t numSlices; // 04
			std::uint16_t flags;	 // 06
			NiColor color;			 // 08
		};
		static_assert(sizeof(SplineData_Untilv130) == 0x14);

		class SplineData
			: public SplineData_Untilv130 // 00
		{
		public:
			// members
			REX::Float32 windSensibility; // 14
			REX::Float32 flexibility;	  // 18
		};
		static_assert(sizeof(SplineData) == 0x1C);

		// members
		SplineData data;		   // 68
		BGSTextureSet* textureSet; // 88
	};
	static_assert(sizeof(BGSBendableSpline) == 0x90);
}
