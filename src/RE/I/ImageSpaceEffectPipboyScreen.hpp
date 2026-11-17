#pragma once

#include "RE/I/ImageSpaceEffect.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class NiTexture;

	class __declspec(novtable) ImageSpaceEffectPipboyScreen : public ImageSpaceEffect // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ImageSpaceEffectPipboyScreen;
		inline static constexpr const auto& VTABLE = VTABLE::ImageSpaceEffectPipboyScreen;

		~ImageSpaceEffectPipboyScreen() override; // 0x00

		// override (ImageSpaceEffect)
		void Setup(ImageSpaceManager* a_manager, ImageSpaceEffectParam* a_param) override; // 0x03
		void ReturnTextures() override;													   // 0x06
		auto UpdateParams(ImageSpaceEffectParam* a_param) -> bool override;				   // 0x09

		[[nodiscard]]
		static auto GetIsPowerArmorPipboy() noexcept -> bool&
		{
			static const auto IS_POWER_ARMOR_PIPBOY =
				REL::Relocation<bool*>{ID::ImageSpaceEffectPipboyScreen::IsPowerArmorPipboy};
			return *IS_POWER_ARMOR_PIPBOY;
		}

		// members
		NiPointer<NiTexture> scanlineTexture; // 0xB0
		NiPointer<NiTexture> vScanTexture;	  // 0xB8
	};

	static_assert(sizeof(ImageSpaceEffectPipboyScreen) == 0xC0);
}
