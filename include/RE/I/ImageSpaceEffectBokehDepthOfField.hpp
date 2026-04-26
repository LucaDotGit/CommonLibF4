#pragma once

#include "RE/I/ImageSpaceEffectOption.hpp"

namespace RE
{
	class __declspec(novtable) ImageSpaceEffectBokehDepthOfField
		: public ImageSpaceEffectOption // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ImageSpaceEffectBokehDepthOfField };
		inline static constexpr auto VTABLE{ VTABLE::ImageSpaceEffectBokehDepthOfField };

		~ImageSpaceEffectBokehDepthOfField() override; // 00

		// override (ImageSpaceEffect)
		void Render(BSTriShape* a_geometry, ImageSpaceEffectParam* a_param) override;	   // 01
		void Setup(ImageSpaceManager* a_manager, ImageSpaceEffectParam* a_param) override; // 03
		bool IsActive() override;														   // 08
	};
	static_assert(sizeof(ImageSpaceEffectBokehDepthOfField) == 0xC8);
}
