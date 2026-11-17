#pragma once

#include "RE/I/ImageSpaceEffect.hpp"

namespace RE
{
	class __declspec(novtable) ImageSpaceEffectOption : public ImageSpaceEffect // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ImageSpaceEffectOption;
		inline static constexpr const auto& VTABLE = VTABLE::ImageSpaceEffectOption;

		// members
		NiTPrimitiveArray<bool> effectOn; // 0xB0
	};

	static_assert(sizeof(ImageSpaceEffectOption) == 0xC8);
}
