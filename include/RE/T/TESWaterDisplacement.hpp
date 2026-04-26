#pragma once

#include "RE/B/BSTSmartPointer.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/N/NiRefObject.hpp"

namespace RE
{
	class BSWaterShaderMaterial;
	class NiAVObject;

	class __declspec(novtable) TESWaterDisplacement
		: public NiRefObject // 00
	{
	public:
		enum class Flags : std::uint8_t
		{
			kNone = 0,
			kDirty = 1 << 0
		};

		// members
		BSTSmartPointer<BSWaterShaderMaterial> waterMaterial; // 10
		TESWaterForm* waterType;							  // 18
		REX::Float32 height;								  // 20
		std::uint32_t stencilBits;							  // 24
		REX::EnumSet<Flags, std::uint8_t> flags;			  // 28
		NiPointer<NiAVObject> displacementGeometry;			  // 30
	};
	static_assert(sizeof(TESWaterDisplacement) == 0x38);
}
