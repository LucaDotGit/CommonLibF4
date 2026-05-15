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
		hkTransform transform;			   // 00
		hkVector4 scale;				   // 40
		hkRefPtr<const hknpShape> shape;   // 50
		std::uint16_t shapeTag;			   // 58
		std::uint16_t destructionTag;	   // 5A
		std::array<std::byte, 0x24> pad5C; // 5C
	};
	static_assert(sizeof(hknpShapeInstance) == 0x80);
}
