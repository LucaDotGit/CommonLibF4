#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/G/GameMenuBase.hpp"
#include "RE/R/Rumble.hpp"

namespace RE
{
	class __declspec(novtable) Console
		: public GameMenuBase // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::Console };
		inline static constexpr auto VTABLE{ VTABLE::Console };
		inline static constexpr auto MENU_NAME{ "Console"sv };
		inline static constexpr auto MENU_DEPTH{ UI_DEPTH_PRIORITY::kConsole };

		inline static constexpr auto HISTORY_PATH = "root1.AnimHolder_mc.Menu_mc.CommandHistory.text"sv;

		~Console() override; // 00

		static void ExecuteCommand(const char* a_command);
		[[nodiscard]] static std::int32_t& GetCurrentPickIndex();
		[[nodiscard]] static ObjectRefHandle& GetPickRef();
		[[nodiscard]] static BSTArray<ObjectRefHandle>& GetPickRefs();
		[[nodiscard]] static ObjectRefHandle GetCurrentPickREFR();
		void SetCurrentPickREFR(ObjectRefHandle& a_ref);

		[[nodiscard]] auto GetHistory() const -> std::optional<std::string>;
		bool SetHistory(REX::zstring_view a_history);
		bool Clear();

		// members
		Rumble::AutoRumblePause* rumbleLock; // E0
		bool minimized;						 // E8
	};
	static_assert(sizeof(Console) == 0xF0);
}
