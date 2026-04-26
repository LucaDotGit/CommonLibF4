#pragma once

#include "RE/I/ImageSpaceEffectOption.hpp"
#include "RE/I/ImageSpaceTexture.hpp"

namespace RE
{
	class __declspec(novtable) ImageSpaceEffectDepthOfField
		: public ImageSpaceEffectOption // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ImageSpaceEffectDepthOfField };
		inline static constexpr auto VTABLE{ VTABLE::ImageSpaceEffectDepthOfField };

		~ImageSpaceEffectDepthOfField() override; // 00

		// override (ImageSpaceEffect)
		void Setup(ImageSpaceManager* a_manager, ImageSpaceEffectParam* a_param) override; // 03
		void BorrowTextures(ImageSpaceEffectParam* a_param) override;					   // 05
		void ReturnTextures() override;													   // 06
		bool IsActive() override;														   // 08
		bool UpdateParams(ImageSpaceEffectParam* a_param) override;						   // 09

		// members
		ImageSpaceTexture maskBuffer;			 // B0
		std::array<ImageSpaceTexture, 3> buffer; // F0
		bool useFog;							 // 168
	};
	static_assert(sizeof(ImageSpaceEffectDepthOfField) == 0x170);
}
