#pragma once

#include "RE/NetImmerse/NiMatrix3.hpp"
#include "RE/NetImmerse/NiPoint.hpp"

namespace RE
{
	class NiTransform
	{
	public:
		void MakeIdentity() noexcept
		{
			rotate.MakeIdentity();
			translate = NiPoint3{};
			scale = 1.0F;
		}

		// members
		NiMatrix3 rotate;	 // 00
		NiPoint3 translate;	 // 30
		float scale{ 1.0F }; // 3C
	};
	static_assert(sizeof(NiTransform) == 0x40);
}
