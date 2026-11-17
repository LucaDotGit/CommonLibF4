#pragma once

#include "RE/N/NiAVObject.hpp"
#include "RE/N/NiBound.hpp"
#include "RE/N/NiColor.hpp"

namespace RE
{
	class __declspec(novtable) NiLight : public NiAVObject // 0x000
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NiLight;
		inline static constexpr const auto& VTABLE = VTABLE::NiLight;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::NiLight;

		~NiLight() override; // 0x00

		// members
		NiColor ambient;				  // 0x120
		NiColor diffuse;				  // 0x12C
		NiColor specular;				  // 0x138
		REX::Float32 dimmer;			  // 0x144
		alignas(0x10) NiBound modelBound; // 0x150
		void* rendererData;				  // 0x160
	};

	static_assert(sizeof(NiLight) == 0x170);
}
