#pragma once

#include "RE/B/BSFixedString.hpp"

#include "Scaleform/G/GFx_FunctionHandler.hpp"
#include "Scaleform/G/GFx_Value.hpp"

namespace RE
{
	class BSGFxFunctionBase;

	class __declspec(novtable) BSGFxFunctionHandler
		: public ::Scaleform::GFx::FunctionHandler // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSGFxFunctionHandler };
		inline static constexpr auto VTABLE{ VTABLE::BSGFxFunctionHandler };

		~BSGFxFunctionHandler() override; // 00

		// override (::Scaleform::GFx::FunctionHandler)
		void Call(const ::Scaleform::GFx::FunctionHandler::Params& a_params) override; // 01

		// members
		::Scaleform::GFx::Value flashTarget;				// 10
		::Scaleform::GFx::Value originalFunctionDefinition; // 30
		BSFixedStringCS funcName;							// 50
		BSGFxFunctionBase* owner;							// 58
	};
	static_assert(sizeof(BSGFxFunctionHandler) == 0x60);
}
