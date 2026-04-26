#pragma once

#include "RE/I/ImageSpaceModData.hpp"
#include "RE/I/ImageSpaceModifierInstanceTemp.hpp"

namespace RE
{
	class __declspec(novtable) ImageSpaceModifierInstanceRB
		: public ImageSpaceModifierInstanceTemp // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ImageSpaceModifierInstanceRB };
		inline static constexpr auto VTABLE{ VTABLE::ImageSpaceModifierInstanceRB };

		~ImageSpaceModifierInstanceRB() override; // 00

		// override (ImageSpaceModifierInstanceTemp)
		void Apply() override;					 // 29
		void PrintInfo(char* a_buffer) override; // 2A

		// members
		ImageSpaceModData data; // 30
	};
	static_assert(sizeof(ImageSpaceModifierInstanceRB) == 0x80);
}
