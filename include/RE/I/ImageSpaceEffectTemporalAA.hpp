#pragma once

#include "RE/I/ImageSpaceEffect.hpp"

namespace RE
{
	class __declspec(novtable) ImageSpaceEffectTemporalAA
		: public ImageSpaceEffect // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ImageSpaceEffectTemporalAA };
		inline static constexpr auto VTABLE{ VTABLE::ImageSpaceEffectTemporalAA };

		~ImageSpaceEffectTemporalAA() override; // 00

		// override (ImageSpaceEffect)
		void Render(BSTriShape* a_geometry, ImageSpaceEffectParam* a_param) override;	   // 01
		void Setup(ImageSpaceManager* a_manager, ImageSpaceEffectParam* a_param) override; // 03
		bool IsActive() override;														   // 08
		bool UpdateParams(ImageSpaceEffectParam* a_param) override;						   // 09

		[[nodiscard]] static std::uint32_t& GetMaskS()
		{
			static const auto MASK_S = REL::Relocation<std::uint32_t*>{ ID::ImageSpaceEffectTemporalAA::MaskS };
			return *MASK_S;
		}

		// members
		REX::Float32 previousInvTexSizeX;		 // B0
		REX::Float32 previousInvTexSizeY;		 // B4
		REX::Float32 previousDynamicWidthRatio;	 // B8
		REX::Float32 previousDynamicHeightRatio; // BC
	};
	static_assert(sizeof(ImageSpaceEffectTemporalAA) == 0xC0);
}
