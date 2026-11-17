#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTextureSet.hpp"

namespace RE
{
	class __declspec(novtable) BSShaderTextureSet : public BSTextureSet // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSShaderTextureSet;
		inline static constexpr const auto& VTABLE = VTABLE::BSShaderTextureSet;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::BSShaderTextureSet;

		[[nodiscard]]
		static auto CreateObject() -> BSShaderTextureSet*
		{
			using FuncType = decltype(&BSShaderTextureSet::CreateObject);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSShaderTextureSet::CreateObject);
			return std::invoke(FUNC);
		}

		// members
		std::array<BSFixedString, 10> textureNames; // 0x10
	};

	static_assert(sizeof(BSShaderTextureSet) == 0x60);
}
