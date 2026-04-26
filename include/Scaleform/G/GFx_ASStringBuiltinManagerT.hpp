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
		std::array<ASStringNodeHolder, STAT> builtins; // 00
		ASStringManager* stringManager;				   // ??
		const char** staticStrings;					   // ??+08
	};
	static_assert(sizeof(ASStringBuiltinManagerT<void, 65>) == 0x218);
}
