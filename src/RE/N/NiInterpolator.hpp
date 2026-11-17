#pragma once

#include "RE/N/NiObject.hpp"

namespace RE
{
	class NiAVObjectPalette;
	class NiBoolInterpolator;
	class NiColorA;
	class NiObjectNET;
	class NiPoint3;
	class NiQuaternion;
	class NiQuatTransform;

	class __declspec(novtable) NiInterpolator : public NiObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NiInterpolator;
		inline static constexpr const auto& VTABLE = VTABLE::NiInterpolator;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::NiInterpolator;

		~NiInterpolator() override; // 0x00

		// add
		virtual auto Update(
			REX::Float32 a_time,
			NiObjectNET* a_interpolationTarget,
			NiQuatTransform& a_outValue) -> bool; // 0x28
		virtual auto Update(REX::Float32 a_time, NiObjectNET* a_interpolationTarget, NiColorA& a_outValue)
			-> bool; // 0x29
		virtual auto Update(REX::Float32 a_time, NiObjectNET* a_interpolationTarget, NiPoint3& a_outValue)
			-> bool; // 0x2A
		virtual auto Update(REX::Float32 a_time, NiObjectNET* a_interpolationTarget, NiQuaternion& a_outValue)
			-> bool; // 0x2B
		virtual auto Update(REX::Float32 a_time, NiObjectNET* a_interpolationTarget, REX::Float32& a_outValue)
			-> bool;																							// 0x2C
		virtual auto Update(REX::Float32 a_time, NiObjectNET* a_interpolationTarget, bool& a_outValue) -> bool; // 0x2D
		virtual auto IsBoolValueSupported() -> bool;															// 0x2E
		virtual auto IsFloatValueSupported() -> bool;															// 0x2F
		virtual auto IsQuaternionValueSupported() -> bool;														// 0x30
		virtual auto IsPoint3ValueSupported() -> bool;															// 0x31
		virtual auto IsColorAValueSupported() -> bool;															// 0x32
		virtual auto IsTransformValueSupported() -> bool;														// 0x33
		virtual void Collapse();																				// 0x34
		virtual void GuaranteeTimeRange(REX::Float32 a_startTime, REX::Float32 a_endTime);						// 0x35
		virtual auto GetSequenceInterpolator(REX::Float32 a_startTime, REX::Float32 a_endTime)
			-> NiInterpolator*;																		   // 0x36
		virtual auto ResolveDependencies(NiAVObjectPalette* a_palette) -> bool;						   // 0x37
		virtual auto SetUpDependencies() -> bool;													   // 0x38
		virtual auto AlwaysUpdate() -> bool;														   // 0x39
		virtual auto IsNiBoolInterpolator() -> NiBoolInterpolator*;									   // 0x3A
		virtual void GetActiveTimeRangeImpl(REX::Float32& a_outStartTime, REX::Float32& a_outEndTime); // 0x3B

		// members
		REX::Float32 lastTime; // 0x10
	};

	static_assert(sizeof(NiInterpolator) == 0x18);
}
