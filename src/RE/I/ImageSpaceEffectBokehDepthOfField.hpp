#pragma once

#include "RE/I/ImageSpaceEffectOption.hpp"

namespace RE
{
	class __declspec(novtable) ImageSpaceEffectBokehDepthOfField : public ImageSpaceEffectOption // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ImageSpaceEffectBokehDepthOfField;
		inline static constexpr const auto& VTABLE = VTABLE::ImageSpaceEffectBokehDepthOfField;

		~ImageSpaceEffectBokehDepthOfField() override; // 0x00

		// override (ImageSpaceEffect)
		void Render(BSTriShape* a_geometry, ImageSpaceEffectParam* a_param) override;	   // 0x01
		void Setup(ImageSpaceManager* a_manager, ImageSpaceEffectParam* a_param) override; // 0x03
		auto IsActive() -> bool override;												   // 0x08
	};

	static_assert(sizeof(ImageSpaceEffectBokehDepthOfField) == 0xC8);
}
