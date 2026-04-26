#pragma once

#include "RE/I/ImageSpaceEffect.hpp"

namespace RE
{
	class __declspec(novtable) ImageSpaceEffectHDR
		: public ImageSpaceEffect // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ImageSpaceEffectHDR };
		inline static constexpr auto VTABLE{ VTABLE::ImageSpaceEffectHDR };

		~ImageSpaceEffectHDR() override; // 00

		// override (ImageSpaceEffect)
		void Render(BSTriShape* a_geometry, ImageSpaceEffectParam* a_param) override;	   // 01
		void Setup(ImageSpaceManager* a_manager, ImageSpaceEffectParam* a_param) override; // 03
		void Shutdown() override;														   // 04
		bool UpdateParams(ImageSpaceEffectParam* a_param) override;						   // 09

		[[nodiscard]] static bool& GetUsePipboyScreenMask()
		{
			static const auto USE_PIPBOY_SCREEN_MASK = REL::Relocation<bool*>{ ID::ImageSpaceEffectHDR::UsePipboyScreenMask };
			return *USE_PIPBOY_SCREEN_MASK;
		}
	};
	static_assert(sizeof(ImageSpaceEffectHDR) == 0xB0);
}
