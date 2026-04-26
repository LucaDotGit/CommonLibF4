#pragma once

#include "RE/I/ImageSpaceModifierInstance.hpp"

namespace RE
{
	class __declspec(novtable) ImageSpaceModifierInstanceTemp
		: public ImageSpaceModifierInstance // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ImageSpaceModifierInstanceTemp };
		inline static constexpr auto VTABLE{ VTABLE::ImageSpaceModifierInstanceTemp };

		~ImageSpaceModifierInstanceTemp() override; // 00

		// override (ImageSpaceModifierInstance)
		bool IsExpired() override;				 // 28
		void PrintInfo(char* a_buffer) override; // 2A

		// members
		REX::Float32 duration; // 28
	};
	static_assert(sizeof(ImageSpaceModifierInstanceTemp) == 0x30);
}
