#pragma once

#include "RE/B/BGSSceneAction.hpp"
#include "RE/B/BSTArray.hpp"

namespace RE
{
	class __declspec(novtable) BGSSceneActionPackage : public BGSSceneAction // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSSceneActionPackage;
		inline static constexpr auto VTABlE = VTABLE::BGSSceneActionPackage;

		~BGSSceneActionPackage() override; // 0x00

		std::uint32_t currentPackIndex; // 0x20
		BSTArray<TESPackage*> packages; // 0x28
	};

	static_assert(sizeof(BGSSceneActionPackage) == 0x40);
}
