#pragma once

#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/M/MessageBoxData.hpp"
#include "RE/W/WARNING_TYPES.hpp"

namespace RE
{
	class MessageMenuManager
		: public BSTSingletonSDM<MessageMenuManager> // 00
	{
	public:
		inline static constexpr auto MAX_BUTTON_COUNT = static_cast<std::uint32_t>(std::numeric_limits<std::uint8_t>::max());

		[[nodiscard]] static MessageMenuManager* GetSingleton();

		void CreateOKMessage(
			const char* a_bodyText,
			IMessageBoxCallback* a_callback = nullptr,
			WARNING_TYPES a_warningContext = WARNING_TYPES::kDefault,
			bool a_ensureUnique = false);

		void CreateYesNoMessage(
			const char* a_bodyText,
			IMessageBoxCallback* a_callback = nullptr,
			WARNING_TYPES a_warningContext = WARNING_TYPES::kDefault,
			bool a_ensureUnique = false);

		void CreateCustomMessage(
			const char* a_bodyText,
			IMessageBoxCallback* a_callback = nullptr,
			BSTArray<BSString> a_buttons = {},
			WARNING_TYPES a_warningContext = WARNING_TYPES::kDefault,
			bool a_ensureUnique = false);

		void CreateMessage(
			const char* a_bodyText,
			IMessageBoxCallback* a_callback = nullptr,
			const char* a_buttonText01 = nullptr,
			const char* a_buttonText02 = nullptr,
			const char* a_buttonText03 = nullptr,
			const char* a_buttonText04 = nullptr,
			WARNING_TYPES a_warningContext = WARNING_TYPES::kDefault,
			bool a_ensureUnique = false);

		void ShowMessages();

		void CreateImpl(
			const char* a_headerText,
			const char* a_bodyText,
			IMessageBoxCallback* a_callback = nullptr,
			WARNING_TYPES a_warningContext = WARNING_TYPES::kDefault,
			const char* a_buttonText01 = nullptr,
			const char* a_buttonText02 = nullptr,
			const char* a_buttonText03 = nullptr,
			const char* a_buttonText04 = nullptr,
			bool a_ensureUnique = false);

		// members
		mutable BSReadWriteLock messageRWLock;										  // 04
		BSTArray<MessageBoxData*> messages;											  // 10
		REX::Enum<WARNING_TYPES, std::int32_t> currentWarningContext;				  // 28
		std::array<bool, std::to_underlying(WARNING_TYPES::kTotal)> disabledWarnings; // 2C
	};
	static_assert(sizeof(MessageMenuManager) == 0x50);
}
