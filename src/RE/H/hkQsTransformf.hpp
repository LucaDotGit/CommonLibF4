#pragma once

#include "RE/H/hkQuaternionf.hpp"
#include "RE/H/hkVector4.hpp"

namespace RE
{
	class hkQsTransformf
	{
	public:
		// members
		hkVector4 translation;	// 0x00
		hkQuaternionf rotation; // 0x10
		hkVector4 scale;		// 0x20
	};

	static_assert(sizeof(hkQsTransformf) == 0x30);
}
