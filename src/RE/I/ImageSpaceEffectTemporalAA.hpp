#pragma once

#include "RE/I/ImageSpaceEffect.hpp"

namespace RE
{
	class __declspec(novtable) ImageSpaceEffectTemporalAA : public ImageSpaceEffect // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ImageSpaceEffectTemporalAA;
		inline static constexpr const auto& VTABLE = VTABLE::ImageSpaceEffectTemporalAA;

		~ImageSpaceEffectTemporalAA() override; // 0x00

		// override (ImageSpaceEffect)
		void Render(BSTriShape* a_geometry, ImageSpaceEffectParam* a_param) override;	   // 0x01
		void Setup(ImageSpaceManager* a_manager, ImageSpaceEffectParam* a_param) override; // 0x03
		auto IsActive() -> bool override;												   // 0x08
		auto UpdateParams(ImageSpaceEffectParam* a_param) -> bool override;				   // 0x09

		[[nodiscard]]
		static auto GetMaskS() -> std::uint32_t&
		{
			static const auto MASK_S = REL::Relocation<std::uint32_t*>(ID::ImageSpaceEffectTemporalAA::MaskS);
			return *MASK_S;
		}

		// members
		REX::Float32 previousInvTexSizeX;		 // 0xB0
		REX::Float32 previousInvTexSizeY;		 // 0xB4
		REX::Float32 previousDynamicWidthRatio;	 // 0xB8
		REX::Float32 previousDynamicHeightRatio; // 0xBC
	};

	static_assert(sizeof(ImageSpaceEffectTemporalAA) == 0xC0);
}
