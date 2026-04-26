#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTextureSet.hpp"

namespace RE
{
	class __declspec(novtable) BSShaderTextureSet
		: public BSTextureSet // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSShaderTextureSet };
		inline static constexpr auto VTABLE{ VTABLE::BSShaderTextureSet };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::BSShaderTextureSet };

		[[nodiscard]] static BSShaderTextureSet* CreateObject()
		{
			using FuncType = decltype(&BSShaderTextureSet::CreateObject);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BSShaderTextureSet::CreateObject };
			return std::invoke(FUNC);
		}

		// members
		std::array<BSFixedString, 10> textureNames; // 10
	};
	static_assert(sizeof(BSShaderTextureSet) == 0x60);
}
