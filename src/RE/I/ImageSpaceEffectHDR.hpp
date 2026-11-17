#pragma once

#include "RE/I/ImageSpaceEffect.hpp"

namespace RE
{
	class __declspec(novtable) ImageSpaceEffectHDR : public ImageSpaceEffect // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ImageSpaceEffectHDR;
		inline static constexpr const auto& VTABLE = VTABLE::ImageSpaceEffectHDR;

		~ImageSpaceEffectHDR() override; // 0x00

		// override (ImageSpaceEffect)
		void Render(BSTriShape* a_geometry, ImageSpaceEffectParam* a_param) override;	   // 0x01
		void Setup(ImageSpaceManager* a_manager, ImageSpaceEffectParam* a_param) override; // 0x03
		void Shutdown() override;														   // 0x04
		auto UpdateParams(ImageSpaceEffectParam* a_param) -> bool override;				   // 0x09

		[[nodiscard]]
		static auto GetUsePipboyScreenMask() noexcept -> bool&
		{
			static const auto USE_PIPBOY_SCREEN_MASK =
				REL::Relocation<bool*>{ID::ImageSpaceEffectHDR::UsePipboyScreenMask};
			return *USE_PIPBOY_SCREEN_MASK;
		}
	};

	static_assert(sizeof(ImageSpaceEffectHDR) == 0xB0);
}
