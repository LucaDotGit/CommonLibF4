#pragma once

#include "RE/Bethesda/BSFixedString.hpp"
#include "RE/Bethesda/BSScript/ILoader.hpp"

namespace RE::BSScript
{
	struct ILoader;

	class __declspec(novtable) IObjectProcessor
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSScript__IObjectProcessor };
		inline static constexpr auto VTABLE{ VTABLE::BSScript__IObjectProcessor };

		virtual ~IObjectProcessor(); // 00

		// add
		virtual IObjectProcessor* Clone() = 0;						// 01
		virtual void SetLoader(ILoader* a_loader) = 0;				// 02
		virtual bool Process(const BSFixedString& a_className) = 0; // 03
	};
	static_assert(sizeof(IObjectProcessor) == 0x8);
}
