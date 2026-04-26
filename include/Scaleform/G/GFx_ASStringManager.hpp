#pragma once

#include "Scaleform/R/RefCountBase.hpp"

namespace Scaleform::GFx
{
	class ASStringNode;

	class __declspec(novtable) ASStringManager
		: public RefCountBase<ASStringManager, 324> // 00
	{
	public:
		[[nodiscard]] ASStringNode* CreateStringNode(const char* a_str)
		{
			using FuncType = decltype(&ASStringManager::CreateStringNode);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::GFx::ASStringManager::CreateStringNode };
			return std::invoke(FUNC, this, a_str);
		}

		// members
		std::array<std::byte, 0xA0 - 0x10> unk10; // 10
	};
	static_assert(sizeof(ASStringManager) == 0xA0);
}
