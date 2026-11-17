#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE::BSScript
{
	class ILoader;

	class __declspec(novtable) IObjectProcessor
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSScript__IObjectProcessor;
		inline static constexpr const auto& VTABLE = VTABLE::BSScript__IObjectProcessor;

		virtual ~IObjectProcessor() = default; // 0x00

		// add
		virtual auto Clone() -> IObjectProcessor* = 0;						// 0x01
		virtual void SetLoader(ILoader* a_loader) = 0;						// 0x02
		virtual auto Process(const BSFixedString& a_className) -> bool = 0; // 0x03

		GAME_HEAP_REDEFINE_NEW(IObjectProcessor);
	};

	static_assert(sizeof(IObjectProcessor) == 0x08);
}
