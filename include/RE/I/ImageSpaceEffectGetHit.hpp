#pragma once

#include "RE/I/ImageSpaceEffect.hpp"
#include "RE/I/ImageSpaceTexture.hpp"

namespace RE
{
	class __declspec(novtable) ImageSpaceEffectGetHit
		: public ImageSpaceEffect // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ImageSpaceEffectGetHit };
		inline static constexpr auto VTABLE{ VTABLE::ImageSpaceEffectGetHit };

		~ImageSpaceEffectGetHit() override; // 00

		// override (ImageSpaceEffect)
		void Render(BSTriShape* a_geometry, ImageSpaceEffectParam* a_param) override;	   // 01
		void Setup(ImageSpaceManager* a_manager, ImageSpaceEffectParam* a_param) override; // 03
		void BorrowTextures(ImageSpaceEffectParam* a_param) override;					   // 05
		void ReturnTextures() override;													   // 06
		bool IsActive() override;														   // 08
		bool UpdateParams(ImageSpaceEffectParam* a_param) override;						   // 09

		[[nodiscard]] static bool& GetIsDisabled()
		{
			static const auto IS_DISABLED = REL::Relocation<bool*>{ ID::ImageSpaceEffectGetHit::IsDisabled };
			return *IS_DISABLED;
		}

		// members
		REX::Float32* data;						 // B0
		std::array<ImageSpaceTexture, 2> buffer; // B8
	};
	static_assert(sizeof(ImageSpaceEffectGetHit) == 0x108);
}
