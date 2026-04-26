#include "RE/S/SWFToCodeFunctionHandler.hpp"

namespace RE
{
	void SWFToCodeFunctionHandler::MapCodeMethodToASFunction(const char* a_functionName, std::int32_t a_functionID)
	{
		using FuncType = decltype(&SWFToCodeFunctionHandler::MapCodeMethodToASFunction);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::SWFToCodeFunctionHandler::MapCodeMethodToASFunction };
		FUNC(this, a_functionName, a_functionID);
	}

	void SWFToCodeFunctionHandler::RegisterCodeObject(::Scaleform::GFx::Movie& a_movie, ::Scaleform::GFx::Value& a_menuObj)
	{
		using FuncType = decltype(&SWFToCodeFunctionHandler::RegisterCodeObject);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::SWFToCodeFunctionHandler::RegisterCodeObject };
		FUNC(this, a_movie, a_menuObj);
	}
}
