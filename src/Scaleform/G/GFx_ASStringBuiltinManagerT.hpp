#pragma once

#include "Scaleform/G/GFx_ASStringNodeHolder.hpp"

namespace Scaleform::GFx
{
	class ASStringManager;

	template <class T, std::int32_t STAT>
	class ASStringBuiltinManagerT
	{
	public:
		// members
		std::array<ASStringNodeHolder, STAT> builtins; // 0x00
		ASStringManager* stringManager;				   // 0x??
		const char** staticStrings;					   // 0x??
	};

	static_assert(sizeof(ASStringBuiltinManagerT<void, 65>) == 0x218);
}
