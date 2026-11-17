#pragma once

#include "RE/I/ImageSpaceEffect.hpp"

namespace RE
{
	class __declspec(novtable) ImageSpaceEffectMotionBlur : public ImageSpaceEffect // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ImageSpaceEffectMotionBlur;
		inline static constexpr const auto& VTABLE = VTABLE::ImageSpaceEffectMotionBlur;

		~ImageSpaceEffectMotionBlur() override; // 0x00

		// override (ImageSpaceEffect)
		void Setup(ImageSpaceManager* a_manager, ImageSpaceEffectParam* a_param) override; // 0x03
		auto IsActive() -> bool override;												   // 0x08
		auto UpdateParams(ImageSpaceEffectParam* a_param) -> bool override;				   // 0x09
	};

	static_assert(sizeof(ImageSpaceEffectMotionBlur) == 0xB0);
}
