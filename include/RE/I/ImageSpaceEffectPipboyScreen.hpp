#pragma once

#include "RE/I/ImageSpaceEffect.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class NiTexture;

	class __declspec(novtable) ImageSpaceEffectPipboyScreen
		: public ImageSpaceEffect // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ImageSpaceEffectPipboyScreen };
		inline static constexpr auto VTABLE{ VTABLE::ImageSpaceEffectPipboyScreen };

		~ImageSpaceEffectPipboyScreen() override; // 00

		// override (ImageSpaceEffect)
		void Setup(ImageSpaceManager* a_manager, ImageSpaceEffectParam* a_param) override; // 03
		void ReturnTextures() override;													   // 06
		bool UpdateParams(ImageSpaceEffectParam* a_param) override;						   // 09

		[[nodiscard]] static bool& GetIsPowerArmorPipboy()
		{
			static const auto IS_POWER_ARMOR_PIPBOY = REL::Relocation<bool*>{ ID::ImageSpaceEffectPipboyScreen::IsPowerArmorPipboy };
			return *IS_POWER_ARMOR_PIPBOY;
		}

		// members
		NiPointer<NiTexture> scanlineTexture; // B0
		NiPointer<NiTexture> vScanTexture;	  // B8
	};
	static_assert(sizeof(ImageSpaceEffectPipboyScreen) == 0xC0);
}
