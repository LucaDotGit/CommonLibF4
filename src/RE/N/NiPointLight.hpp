#pragma once

#include "RE/N/NiLight.hpp"

namespace RE
{
	class __declspec(novtable) NiPointLight : public NiLight // 0x000
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NiPointLight;
		inline static constexpr const auto& VTABLE = VTABLE::NiPointLight;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::NiPointLight;

		~NiPointLight() override; // 0x00

		// members
		REX::Float32 constAttenuation;				 // 0x170
		REX::Float32 linearAttenuation;				 // 0x174
		REX::Float32 quadraticAttenuation;			 // 0x178
		std::array<REX::Float32, 3> animationOffset; // 0x17C
	};

	static_assert(sizeof(NiPointLight) == 0x190);
}
