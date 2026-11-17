#pragma once

#include "RE/I/ImageSpaceEffect.hpp"

namespace RE
{
	class __declspec(novtable) ImageSpaceEffectRadialBlur : public ImageSpaceEffect // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ImageSpaceEffectRadialBlur;
		inline static constexpr const auto& VTABLE = VTABLE::ImageSpaceEffectRadialBlur;

		~ImageSpaceEffectRadialBlur() override; // 0x00

		// override (ImageSpaceEffect)
		void Setup(ImageSpaceManager* a_manager, ImageSpaceEffectParam* a_param) override; // 0x03
		auto IsActive() -> bool override;												   // 0x08
		auto UpdateParams(ImageSpaceEffectParam* a_param) -> bool override;				   // 0x09

		[[nodiscard]]
		static auto GetIsDisabled() noexcept -> bool&
		{
			static const auto IS_DISABLED = REL::Relocation<bool*>(ID::ImageSpaceEffectRadialBlur::IsDisabled);
			return *IS_DISABLED;
		}
	};

	static_assert(sizeof(ImageSpaceEffectRadialBlur) == 0xB0);
}
