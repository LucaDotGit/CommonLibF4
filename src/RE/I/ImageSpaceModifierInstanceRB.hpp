#pragma once

#include "RE/I/ImageSpaceModData.hpp"
#include "RE/I/ImageSpaceModifierInstanceTemp.hpp"

namespace RE
{
	class __declspec(novtable) ImageSpaceModifierInstanceRB : public ImageSpaceModifierInstanceTemp // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ImageSpaceModifierInstanceRB;
		inline static constexpr const auto& VTABLE = VTABLE::ImageSpaceModifierInstanceRB;

		~ImageSpaceModifierInstanceRB() override; // 0x00

		// override (ImageSpaceModifierInstanceTemp)
		void Apply() override;					 // 0x29
		void PrintInfo(char* a_buffer) override; // 0x2A

		// members
		ImageSpaceModData data; // 0x30
	};

	static_assert(sizeof(ImageSpaceModifierInstanceRB) == 0x80);
}
