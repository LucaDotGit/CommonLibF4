#pragma once

#include "RE/H/hkQuaternionf.hpp"
#include "RE/H/hkVector4f.hpp"

namespace RE
{
	class hkQsTransformf
	{
	public:
		// members
		hkVector4f translation; // 00
		hkQuaternionf rotation; // 10
		hkVector4f scale;		// 20
	};
	static_assert(sizeof(hkQsTransformf) == 0x30);
}
