#pragma once

#include "RE/H/hkRefPtr.hpp"
#include "RE/H/hkTransform.hpp"
#include "RE/H/hkVector4.hpp"

namespace RE
{
	class hknpShape;

	class hknpShapeInstance
	{
	public:
		// members
		hkTransform transform;			   // 0x00
		hkVector4 scale;				   // 0x40
		hkRefPtr<const hknpShape> shape;   // 0x50
		std::uint16_t shapeTag;			   // 0x58
		std::uint16_t destructionTag;	   // 0x5A
		std::array<std::byte, 0x24> pad5C; // 0x5C
	};

	static_assert(sizeof(hknpShapeInstance) == 0x80);
}
