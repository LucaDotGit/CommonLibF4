#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSGFxFunctionHandler.hpp"
#include "RE/M/MemoryManager.hpp"

#include "Scaleform/P/Ptr.hpp"

namespace RE
{
	class UsesBSGFXFunctionHandler;

	class __declspec(novtable) BSGFxFunctionBase
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSGFxFunctionBase };
		inline static constexpr auto VTABLE{ VTABLE::BSGFxFunctionBase };

		virtual ~BSGFxFunctionBase(); // 00

		// add
		virtual void CallFlashFunction(const ::Scaleform::GFx::FunctionHandler::Params& a_params) = 0;

		GAME_HEAP_REDEFINE_NEW(BSGFxFunctionBase);

		// members
		::Scaleform::Ptr<BSGFxFunctionHandler> handler; // 08
		BSFixedStringCS funcName;						// 10
		UsesBSGFXFunctionHandler* owner;				// 18
	};
	static_assert(sizeof(BSGFxFunctionBase) == 0x20);
}
