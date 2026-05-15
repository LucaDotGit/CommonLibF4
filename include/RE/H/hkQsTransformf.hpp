#pragma once

#include "RE/H/hkQuaternionf.hpp"
#include "RE/H/hkVector4.hpp"

namespace RE
{
	class hkQsTransformf
	{
	public:
		// members
		hkVector4 translation;	// 00
		hkQuaternionf rotation; // 10
		hkVector4 scale;		// 20
	};
	static_assert(sizeof(hkQsTransformf) == 0x30);
}
