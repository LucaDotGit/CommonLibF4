#pragma once

#include "RE/N/NiLight.hpp"

namespace RE
{
	class __declspec(novtable) NiPointLight
		: public NiLight // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NiPointLight };
		inline static constexpr auto VTABLE{ VTABLE::NiPointLight };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::NiPointLight };

		~NiPointLight() override; // 00

		// members
		REX::Float32 constAttenuation;				 // 170
		REX::Float32 linearAttenuation;				 // 174
		REX::Float32 quadraticAttenuation;			 // 178
		std::array<REX::Float32, 3> animationOffset; // 17C
	};
	static_assert(sizeof(NiPointLight) == 0x190);
}
