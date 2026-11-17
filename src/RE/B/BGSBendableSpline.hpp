#pragma once

#include "RE/N/NiColor.hpp"
#include "RE/T/TESBoundObject.hpp"

namespace RE
{
	class __declspec(novtable) BGSBendableSpline : public TESBoundObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSBendableSpline;
		inline static constexpr const auto& VTABLE = VTABLE::BGSBendableSpline;
		inline static constexpr auto FORM_TYPE = FormType::BendableSpline;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		class SplineData_Untilv130
		{
		public:
			// members
			REX::Float32 numTiles;	 // 0x00
			std::uint16_t numSlices; // 0x04
			std::uint16_t flags;	 // 0x06
			NiColor color;			 // 0x08
		};

		static_assert(sizeof(SplineData_Untilv130) == 0x14);

		class SplineData : public SplineData_Untilv130 // 0x00
		{
		public:
			// members
			REX::Float32 windSensibility; // 0x14
			REX::Float32 flexibility;	  // 0x18
		};

		static_assert(sizeof(SplineData) == 0x1C);

		// members
		SplineData data;		   // 0x68
		BGSTextureSet* textureSet; // 0x88
	};

	static_assert(sizeof(BGSBendableSpline) == 0x90);
}
