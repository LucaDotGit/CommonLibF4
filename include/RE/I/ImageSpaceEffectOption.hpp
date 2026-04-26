#pragma once

#include "RE/I/ImageSpaceEffect.hpp"

namespace RE
{
	class __declspec(novtable) ImageSpaceEffectOption
		: public ImageSpaceEffect // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ImageSpaceEffectOption };
		inline static constexpr auto VTABLE{ VTABLE::ImageSpaceEffectOption };

		// members
		NiTPrimitiveArray<bool> effectOn; // B0
	};
	static_assert(sizeof(ImageSpaceEffectOption) == 0xC8);
}
