#pragma once

#include "RE/B/BSShader.hpp"

namespace RE
{
	class __declspec(novtable) BSUtilityShader : public BSShader // 0x000
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSUtilityShader;
		inline static constexpr const auto& VTABLE = VTABLE::BSUtilityShader;

		// members
		std::uint32_t currentTechniqueID; // 0x118
		std::uint32_t currentDecl;		  // 0x11C
	};

	static_assert(sizeof(BSUtilityShader) == 0x120);
}
