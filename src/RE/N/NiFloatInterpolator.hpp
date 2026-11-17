#pragma once

#include "RE/N/NiKeyBasedInterpolator.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class NiFloatData;

	class __declspec(novtable) NiFloatInterpolator : public NiKeyBasedInterpolator // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NiFloatInterpolator;
		inline static constexpr const auto& VTABLE = VTABLE::NiFloatInterpolator;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::NiFloatInterpolator;

		~NiFloatInterpolator() override; // 0x00

		// members
		REX::Float32 value;			 // 0x18
		NiPointer<NiFloatData> data; // 0x20
		std::uint32_t lastIndex;	 // 0x28
	};

	static_assert(sizeof(NiFloatInterpolator) == 0x30);
}
