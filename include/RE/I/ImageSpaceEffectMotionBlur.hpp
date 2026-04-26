#pragma once

#include "RE/I/ImageSpaceEffect.hpp"

namespace RE
{
	class __declspec(novtable) ImageSpaceEffectMotionBlur
		: public ImageSpaceEffect // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ImageSpaceEffectMotionBlur };
		inline static constexpr auto VTABLE{ VTABLE::ImageSpaceEffectMotionBlur };

		~ImageSpaceEffectMotionBlur() override; // 00

		// override (ImageSpaceEffect)
		void Setup(ImageSpaceManager* a_manager, ImageSpaceEffectParam* a_param) override; // 03
		bool IsActive() override;														   // 08
		bool UpdateParams(ImageSpaceEffectParam* a_param) override;						   // 09
	};
	static_assert(sizeof(ImageSpaceEffectMotionBlur) == 0xB0);
}
