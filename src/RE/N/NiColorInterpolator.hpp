#pragma once

#include "RE/N/NiColorA.hpp"
#include "RE/N/NiKeyBasedInterpolator.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class NiColorData;

	class __declspec(novtable) NiColorInterpolator : public NiKeyBasedInterpolator // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NiColorInterpolator;
		inline static constexpr const auto& VTABLE = VTABLE::NiColorInterpolator;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::NiColorInterpolator;

		~NiColorInterpolator() override; // 0x00

		// members
		NiColorA value;				 // 0x18
		NiPointer<NiColorData> data; // 0x20
		std::uint32_t lastIndex;	 // 0x28
	};

	static_assert(sizeof(NiColorInterpolator) == 0x38);
}
