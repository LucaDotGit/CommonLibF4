#pragma once

#include "RE/B/BGSSceneAction.hpp"
#include "RE/B/BSTArray.hpp"

namespace RE
{
	class __declspec(novtable) BGSSceneActionPackage
		: public BGSSceneAction // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSSceneActionPackage };
		inline static constexpr auto VTABlE{ VTABLE::BGSSceneActionPackage };

		~BGSSceneActionPackage() override; // 00

		std::uint32_t currentPackIndex; // 20
		BSTArray<TESPackage*> packages; // 28
	};
	static_assert(sizeof(BGSSceneActionPackage) == 0x40);
}
