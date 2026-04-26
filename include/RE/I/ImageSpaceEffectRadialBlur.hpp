#pragma once

#include "RE/I/ImageSpaceEffect.hpp"

namespace RE
{
	class __declspec(novtable) ImageSpaceEffectRadialBlur
		: public ImageSpaceEffect // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ImageSpaceEffectRadialBlur };
		inline static constexpr auto VTABLE{ VTABLE::ImageSpaceEffectRadialBlur };

		~ImageSpaceEffectRadialBlur() override; // 00

		// override (ImageSpaceEffect)
		void Setup(ImageSpaceManager* a_manager, ImageSpaceEffectParam* a_param) override; // 03
		bool IsActive() override;														   // 08
		bool UpdateParams(ImageSpaceEffectParam* a_param) override;						   // 09

		[[nodiscard]] static bool& GetIsDisabled()
		{
			static const auto IS_DISABLED = REL::Relocation<bool*>{ ID::ImageSpaceEffectRadialBlur::IsDisabled };
			return *IS_DISABLED;
		}
	};
	static_assert(sizeof(ImageSpaceEffectRadialBlur) == 0xB0);
}
