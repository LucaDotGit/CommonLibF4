#pragma once

#include "RE/B/BSFixedString.hpp"
#include "Scaleform/G/GFx_FunctionHandler.hpp"
#include "Scaleform/G/GFx_Value.hpp"

namespace RE
{
	class BSGFxFunctionBase;

	class __declspec(novtable) BSGFxFunctionHandler : public Scaleform::GFx::FunctionHandler // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSGFxFunctionHandler;
		inline static constexpr const auto& VTABLE = VTABLE::BSGFxFunctionHandler;

		~BSGFxFunctionHandler() override; // 0x00

		// override (Scaleform::GFx::FunctionHandler)
		void Call(const Scaleform::GFx::FunctionHandler::Params& a_params) override; // 0x01

		// members
		Scaleform::GFx::Value flashTarget;				  // 0x10
		Scaleform::GFx::Value originalFunctionDefinition; // 0x30
		BSFixedStringCS funcName;						  // 0x50
		BSGFxFunctionBase* owner;						  // 0x58
	};

	static_assert(sizeof(BSGFxFunctionHandler) == 0x60);
}
