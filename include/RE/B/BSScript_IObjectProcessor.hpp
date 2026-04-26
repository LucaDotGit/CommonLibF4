#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE::BSScript
{
	class ILoader;

	class __declspec(novtable) IObjectProcessor
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSScript__IObjectProcessor };
		inline static constexpr auto VTABLE{ VTABLE::BSScript__IObjectProcessor };

		virtual ~IObjectProcessor() = default; // 00

		// add
		virtual IObjectProcessor* Clone() = 0;						// 01
		virtual void SetLoader(ILoader* a_loader) = 0;				// 02
		virtual bool Process(const BSFixedString& a_className) = 0; // 03
	};
	static_assert(sizeof(IObjectProcessor) == 0x08);
}
