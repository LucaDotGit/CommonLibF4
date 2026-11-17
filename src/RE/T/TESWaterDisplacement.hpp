#pragma once

#include "RE/B/BSTSmartPointer.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/N/NiRefObject.hpp"

namespace RE
{
	class BSWaterShaderMaterial;
	class NiAVObject;

	class __declspec(novtable) TESWaterDisplacement : public NiRefObject // 0x00
	{
	public:
		enum class Flags : std::uint8_t
		{
			None = 0,
			Dirty = 1 << 0
		};

		// members
		BSTSmartPointer<BSWaterShaderMaterial> waterMaterial; // 0x10
		TESWaterForm* waterType;							  // 0x18
		REX::Float32 height;								  // 0x20
		std::uint32_t stencilBits;							  // 0x24
		REX::EnumSet<Flags, std::uint8_t> flags;			  // 0x28
		NiPointer<NiAVObject> displacementGeometry;			  // 0x30
	};

	static_assert(sizeof(TESWaterDisplacement) == 0x38);
}
