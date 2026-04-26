#pragma once

#include "RE/N/NiAVObject.hpp"
#include "RE/N/NiBound.hpp"
#include "RE/N/NiColor.hpp"

namespace RE
{
	class __declspec(novtable) NiLight
		: public NiAVObject // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NiLight };
		inline static constexpr auto VTABLE{ VTABLE::NiLight };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::NiLight };

		~NiLight() override; // 00

		// members
		NiColor ambient;				  // 120
		NiColor diffuse;				  // 12C
		NiColor specular;				  // 138
		REX::Float32 dimmer;			  // 144
		alignas(0x10) NiBound modelBound; // 150
		void* rendererData;				  // 160
	};
	static_assert(sizeof(NiLight) == 0x170);
}
