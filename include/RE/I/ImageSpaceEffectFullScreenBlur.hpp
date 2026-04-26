#pragma once

#include "RE/I/ImageSpaceEffect.hpp"
#include "RE/I/ImageSpaceTexture.hpp"

namespace RE
{
	class __declspec(novtable) ImageSpaceEffectFullScreenBlur
		: public ImageSpaceEffect // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ImageSpaceEffectFullScreenBlur };
		inline static constexpr auto VTABLE{ VTABLE::ImageSpaceEffectFullScreenBlur };

		~ImageSpaceEffectFullScreenBlur() override; // 00

		// override (ImageSpaceEffect)
		void Render(BSTriShape* a_geometry, ImageSpaceEffectParam* a_param) override;	   // 01
		void Setup(ImageSpaceManager* a_manager, ImageSpaceEffectParam* a_param) override; // 03
		void BorrowTextures(ImageSpaceEffectParam* a_param) override;					   // 05
		void ReturnTextures() override;													   // 06
		bool IsActive() override;														   // 08
		bool UpdateParams(ImageSpaceEffectParam* a_param) override;						   // 09

		[[nodiscard]] static bool& GetIsDisabled()
		{
			static const auto IS_DISABLED = REL::Relocation<bool*>{ ID::ImageSpaceEffectFullScreenBlur::IsDisabled };
			return *IS_DISABLED;
		}

		// members
		std::array<ImageSpaceTexture, 3> buffer; // B0
	};
	static_assert(sizeof(ImageSpaceEffectFullScreenBlur) == 0x128);
}
