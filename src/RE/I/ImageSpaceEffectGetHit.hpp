#pragma once

#include "RE/I/ImageSpaceEffect.hpp"
#include "RE/I/ImageSpaceTexture.hpp"

namespace RE
{
	class __declspec(novtable) ImageSpaceEffectGetHit : public ImageSpaceEffect // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ImageSpaceEffectGetHit;
		inline static constexpr const auto& VTABLE = VTABLE::ImageSpaceEffectGetHit;

		~ImageSpaceEffectGetHit() override; // 0x00

		// override (ImageSpaceEffect)
		void Render(BSTriShape* a_geometry, ImageSpaceEffectParam* a_param) override;	   // 0x01
		void Setup(ImageSpaceManager* a_manager, ImageSpaceEffectParam* a_param) override; // 0x03
		void BorrowTextures(ImageSpaceEffectParam* a_param) override;					   // 0x05
		void ReturnTextures() override;													   // 0x06
		auto IsActive() -> bool override;												   // 0x08
		auto UpdateParams(ImageSpaceEffectParam* a_param) -> bool override;				   // 0x09

		[[nodiscard]]
		static auto GetIsDisabled() noexcept -> bool&
		{
			static const auto IS_DISABLED = REL::Relocation<bool*>(ID::ImageSpaceEffectGetHit::IsDisabled);
			return *IS_DISABLED;
		}

		// members
		REX::Float32* data;						 // 0xB0
		std::array<ImageSpaceTexture, 2> buffer; // 0xB8
	};

	static_assert(sizeof(ImageSpaceEffectGetHit) == 0x108);
}
