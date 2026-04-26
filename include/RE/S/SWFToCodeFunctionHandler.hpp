#pragma once

#include "Scaleform/G/GFx_FunctionHandler.hpp"
#include "Scaleform/G/GFx_Movie.hpp"
#include "Scaleform/G/GFx_Value.hpp"

namespace RE
{
	class __declspec(novtable) SWFToCodeFunctionHandler
		: public ::Scaleform::GFx::FunctionHandler // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::SWFToCodeFunctionHandler };
		inline static constexpr auto VTABLE{ VTABLE::SWFToCodeFunctionHandler };

		~SWFToCodeFunctionHandler() override = default; // 00

		// override (::Scaleform::GFx::FunctionHandler)
		void Call([[maybe_unused]] const Params& a_params) override { return; } // 01

		// add
		virtual void MapCodeObjectFunctions() { return; } // 02

		void MapCodeMethodToASFunction(const char* a_functionName, std::int32_t a_functionID);
		void RegisterCodeObject(::Scaleform::GFx::Movie& a_movie, ::Scaleform::GFx::Value& a_menuObj);
	};
	static_assert(sizeof(SWFToCodeFunctionHandler) == 0x10);
}
