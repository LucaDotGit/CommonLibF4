#pragma once

#include "RE/I/ImageSpaceModifierInstance.hpp"

namespace RE
{
	class __declspec(novtable) ImageSpaceModifierInstanceTemp : public ImageSpaceModifierInstance // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ImageSpaceModifierInstanceTemp;
		inline static constexpr const auto& VTABLE = VTABLE::ImageSpaceModifierInstanceTemp;

		~ImageSpaceModifierInstanceTemp() override; // 0x00

		// override (ImageSpaceModifierInstance)
		auto IsExpired() -> bool override;		 // 0x28
		void PrintInfo(char* a_buffer) override; // 0x2A

		// members
		REX::Float32 duration; // 0x28
	};

	static_assert(sizeof(ImageSpaceModifierInstanceTemp) == 0x30);
}
