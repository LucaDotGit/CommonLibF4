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
		static const auto FUNC = REL::Relocation<FuncType>(ID::Console::ExecuteCommand);
		std::invoke(FUNC, a_command);
	}

	void Console::ExecuteQueuedCommand()
	{
		using FuncType = decltype(&Console::ExecuteQueuedCommand);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Console::ExecuteQueuedCommand);
		std::invoke(FUNC);
	}

	auto Console::GetCurrentPickIndex() noexcept -> std::int32_t&
	{
		static const auto CURRENT_PICK_INDEX = REL::Relocation<std::int32_t*>(ID::Console::CurrentPickIndex);
		return *CURRENT_PICK_INDEX;
	}

	auto Console::GetPickRef() noexcept -> ObjectRefHandle&
	{
		static const auto PICK_REF = REL::Relocation<ObjectRefHandle*>(ID::Console::PickRef);
		return *PICK_REF;
	}

	auto Console::GetPickRefs() noexcept -> BSTArray<ObjectRefHandle>&
	{
		static const auto PICK_REFS = REL::Relocation<BSTArray<ObjectRefHandle>*>(ID::Console::PickRefs);
		return *PICK_REFS;
	}

	auto Console::GetCurrentPickRef() noexcept -> ObjectRefHandle
	{
		const auto index = GetCurrentPickIndex();
		if (index < 0) {
			return {};
		}

		const auto& refs = GetPickRefs();
		if (std::cmp_greater_equal(index, refs.size())) {
			return {};
		}

		return refs[REX::ToUnsigned(index)];
	}

	void Console::SetCurrentPickRef(ObjectRefHandle& a_ref)
	{
		using FuncType = decltype(&Console::SetCurrentPickRef);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Console::SetCurrentPickRef);
		std::invoke(FUNC, this, a_ref);
	}

	auto Console::GetHistory() const -> std::optional<std::string>
	{
		if (!uiMovie) {
			return std::nullopt;
		}

		const auto movieRoot = uiMovie->asMovieRoot;
		if (!movieRoot) {
			return std::nullopt;
		}

		auto history = Scaleform::GFx::Value();
		if (!movieRoot->GetVariable(std::addressof(history), HISTORY_PATH.data()) || !history.IsString()) {
			return std::nullopt;
		}

		const auto* string = history.GetString();
		if (!string) {
			return {};
		}

		return std::string(string);
	}

	auto Console::SetHistory(REX::ZStringView a_history) -> bool
	{
		if (!uiMovie) {
			return false;
		}

		const auto movieRoot = uiMovie->asMovieRoot;
		if (!movieRoot) {
			return false;
		}

		const auto history = Scaleform::GFx::Value(a_history);
		return movieRoot->SetVariable(HISTORY_PATH.data(), history);
	}

	auto Console::Clear() -> bool
	{
		if (!uiMovie) {
			return false;
		}

		const auto movieRoot = uiMovie->asMovieRoot;
		if (!movieRoot) {
			return false;
		}

		const auto history = Scaleform::GFx::Value("");
		return movieRoot->SetVariable(HISTORY_PATH.data(), history);
	}
}
