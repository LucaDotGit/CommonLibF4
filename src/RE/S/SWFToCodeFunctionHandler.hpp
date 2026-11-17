#pragma once

#include "Scaleform/G/GFx_FunctionHandler.hpp"
#include "Scaleform/G/GFx_Movie.hpp"
#include "Scaleform/G/GFx_Value.hpp"

namespace RE
{
	class /*__declspec(novtable)*/ SWFToCodeFunctionHandler : public Scaleform::GFx::FunctionHandler // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::SWFToCodeFunctionHandler;
		inline static constexpr const auto& VTABLE = VTABLE::SWFToCodeFunctionHandler;

		SWFToCodeFunctionHandler();

		~SWFToCodeFunctionHandler() override = default; // 0x00

		// override (Scaleform::GFx::FunctionHandler)
		void Call(const Params& a_params) override; // 0x01

		// add
		virtual void MapCodeObjectFunctions(); // 0x02

		void MapCodeMethodToASFunction(const char* a_functionName, std::int32_t a_functionID);
		void RegisterCodeObject(Scaleform::GFx::Movie& a_movie, Scaleform::GFx::Value& a_menuObj);
	};

	static_assert(sizeof(SWFToCodeFunctionHandler) == 0x10);
}
