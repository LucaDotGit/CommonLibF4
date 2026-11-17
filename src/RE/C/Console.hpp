#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/G/GameMenuBase.hpp"
#include "RE/R/Rumble.hpp"
#include "RE/U/UI_DEPTH_PRIORITY.hpp"

namespace RE
{
	class __declspec(novtable) Console : public GameMenuBase // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::Console;
		inline static constexpr const auto& VTABLE = VTABLE::Console;
		inline static constexpr auto MENU_NAME = "Console"sv;
		inline static constexpr auto MENU_DEPTH = UI_DEPTH_PRIORITY::Console;

		inline static constexpr auto HISTORY_PATH = "root1.AnimHolder_mc.Menu_mc.CommandHistory.text"sv;

		~Console() override; // 0x00

		static void ExecuteCommand(const char* a_command);
		static void ExecuteQueuedCommand();

		[[nodiscard]]
		static auto GetCurrentPickIndex() noexcept -> std::int32_t&;
		[[nodiscard]]
		static auto GetPickRef() noexcept -> ObjectRefHandle&;
		[[nodiscard]]
		static auto GetPickRefs() noexcept -> BSTArray<ObjectRefHandle>&;
		[[nodiscard]]
		static auto GetCurrentPickRef() noexcept -> ObjectRefHandle;
		void SetCurrentPickRef(ObjectRefHandle& a_ref);

		[[nodiscard]]
		auto GetHistory() const -> std::optional<std::string>;
		auto SetHistory(REX::ZStringView a_history) -> bool;
		auto Clear() -> bool;

		// members
		Rumble::AutoRumblePause* rumbleLock; // 0xE0
		bool minimized;						 // 0xE8
	};

	static_assert(sizeof(Console) == 0xF0);
}
