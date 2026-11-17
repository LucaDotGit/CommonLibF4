#pragma once

#include "RE/I/ImageSpaceEffectOption.hpp"
#include "RE/I/ImageSpaceTexture.hpp"

namespace RE
{
	class __declspec(novtable) ImageSpaceEffectDepthOfField : public ImageSpaceEffectOption // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ImageSpaceEffectDepthOfField;
		inline static constexpr const auto& VTABLE = VTABLE::ImageSpaceEffectDepthOfField;

		~ImageSpaceEffectDepthOfField() override; // 0x00

		// override (ImageSpaceEffect)
		void Setup(ImageSpaceManager* a_manager, ImageSpaceEffectParam* a_param) override; // 0x03
		void BorrowTextures(ImageSpaceEffectParam* a_param) override;					   // 0x05
		void ReturnTextures() override;													   // 0x06
		auto IsActive() -> bool override;												   // 0x08
		auto UpdateParams(ImageSpaceEffectParam* a_param) -> bool override;				   // 0x09

		// members
		ImageSpaceTexture maskBuffer;			 // 0xB0
		std::array<ImageSpaceTexture, 3> buffer; // 0xF0
		bool useFog;							 // 0x168
	};

	static_assert(sizeof(ImageSpaceEffectDepthOfField) == 0x170);
}
