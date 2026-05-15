#include "RE/C/Console.hpp"

#include "Scaleform/G/GFx_ASMovieRootBase.hpp"
#include "Scaleform/G/GFx_Movie.hpp"
#include "Scaleform/G/GFx_Value.hpp"
#include "Scaleform/P/Ptr.hpp"

namespace RE
{
	void Console::ExecuteCommand(const char* a_command)
	{
		using FuncType = decltype(&Console::ExecuteCommand);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::Console::ExecuteCommand };
		std::invoke(FUNC, a_command);
	}

	std::int32_t& Console::GetCurrentPickIndex()
	{
		static const auto CURRENT_PICK_INDEX = REL::Relocation<std::int32_t*>{ ID::Console::CurrentPickIndex };
		return *CURRENT_PICK_INDEX;
	}

	ObjectRefHandle& Console::GetPickRef()
	{
		static const auto REF = REL::Relocation<ObjectRefHandle*>{ ID::Console::PickRef };
		return *REF;
	}

	BSTArray<ObjectRefHandle>& Console::GetPickRefs()
	{
		static const auto PICK_REFS = REL::Relocation<BSTArray<ObjectRefHandle>*>{ ID::Console::PickRefs };
		return *PICK_REFS;
	}

	ObjectRefHandle Console::GetCurrentPickREFR()
	{
		const auto index = GetCurrentPickIndex();
		if (index < 0) {
			return {};
		}

		const auto& refs = GetPickRefs();
		if (std::cmp_greater_equal(index, refs.size())) {
			return {};
		}

		return refs[index];
	}

	void Console::SetCurrentPickREFR(ObjectRefHandle& a_ref)
	{
		using FuncType = decltype(&Console::SetCurrentPickREFR);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::Console::SetCurrentPickREFR };
		std::invoke(FUNC, this, a_ref);
	}

	auto Console::GetHistory() const
		-> std::optional<std::string>
	{
		if (!uiMovie) {
			return std::nullopt;
		}

		auto movieRoot = uiMovie->asMovieRoot;
		if (!movieRoot) {
			return std::nullopt;
		}

		auto history = ::Scaleform::GFx::Value();
		if (!movieRoot->GetVariable(std::addressof(history), HISTORY_PATH.data()) || !history.IsString()) {
			return std::nullopt;
		}

		const auto* string = history.GetString();
		if (!string) {
			return {};
		}

		return std::string(string);
	}

	bool Console::SetHistory(REX::zstring_view a_history)
	{
		if (!uiMovie) {
			return false;
		}

		auto movieRoot = uiMovie->asMovieRoot;
		if (!movieRoot) {
			return false;
		}

		auto history = ::Scaleform::GFx::Value(a_history);
		return movieRoot->SetVariable(HISTORY_PATH.data(), history);
	}

	bool Console::Clear()
	{
		if (!uiMovie) {
			return false;
		}

		auto movieRoot = uiMovie->asMovieRoot;
		if (!movieRoot) {
			return false;
		}

		auto history = ::Scaleform::GFx::Value("");
		return movieRoot->SetVariable(HISTORY_PATH.data(), history);
	}
}
