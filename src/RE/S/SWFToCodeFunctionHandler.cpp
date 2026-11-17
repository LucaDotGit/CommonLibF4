#include "RE/S/SWFToCodeFunctionHandler.hpp"

namespace RE
{
	// NOLINTNEXTLINE(modernize-use-equals-default)
	SWFToCodeFunctionHandler::SWFToCodeFunctionHandler()
	{
		// REL::EmplaceVtable(this);
	}

	void SWFToCodeFunctionHandler::Call([[maybe_unused]] const Params& a_params)
	{
	}

	void SWFToCodeFunctionHandler::MapCodeObjectFunctions()
	{
	}

	void SWFToCodeFunctionHandler::MapCodeMethodToASFunction(const char* a_functionName, std::int32_t a_functionID)
	{
		using FuncType = decltype(&SWFToCodeFunctionHandler::MapCodeMethodToASFunction);
		static const auto FUNC = REL::Relocation<FuncType>(ID::SWFToCodeFunctionHandler::MapCodeMethodToASFunction);
		std::invoke(FUNC, this, a_functionName, a_functionID);
	}

	void SWFToCodeFunctionHandler::RegisterCodeObject(Scaleform::GFx::Movie& a_movie, Scaleform::GFx::Value& a_menuObj)
	{
		using FuncType = decltype(&SWFToCodeFunctionHandler::RegisterCodeObject);
		static const auto FUNC = REL::Relocation<FuncType>(ID::SWFToCodeFunctionHandler::RegisterCodeObject);
		std::invoke(FUNC, this, a_movie, a_menuObj);
	}
}
