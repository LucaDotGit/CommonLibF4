#pragma once

#include "RE/B/BSReadWriteLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/M/MessageBoxData.hpp"
#include "RE/W/WARNING_TYPES.hpp"

namespace RE
{
	class MessageMenuManager : public BSTSingletonSDM<MessageMenuManager> // 0x00
	{
	public:
		inline static constexpr auto MAX_BUTTON_COUNT =
			static_cast<std::uint32_t>(std::numeric_limits<std::uint8_t>::max());

		inline static constexpr auto OK_TRANSLATION_KEY = "$OK"sv;
		inline static constexpr auto YES_TRANSLATION_KEY = "$Yes"sv;
		inline static constexpr auto NO_TRANSLATION_KEY = "$No"sv;

		[[nodiscard]]
		static auto GetSingleton() noexcept -> MessageMenuManager*;

		void CreateOKMessage(
			const char* a_bodyText,
			const BSTSmartPointer<IMessageBoxCallback>& a_callback = nullptr,
			WARNING_TYPES a_warningContext = WARNING_TYPES::Default,
			bool a_ensureUnique = false);

		void CreateYesNoMessage(
			const char* a_bodyText,
			const BSTSmartPointer<IMessageBoxCallback>& a_callback = nullptr,
			WARNING_TYPES a_warningContext = WARNING_TYPES::Default,
			bool a_ensureUnique = false);

		void CreateCustomMessage(
			const char* a_bodyText,
			const BSTSmartPointer<IMessageBoxCallback>& a_callback = nullptr,
			BSTArray<BSString> a_buttons = {},
			WARNING_TYPES a_warningContext = WARNING_TYPES::Default,
			bool a_ensureUnique = false);

		void CreateMessage(
			const char* a_bodyText,
			const BSTSmartPointer<IMessageBoxCallback>& a_callback = nullptr,
			const char* a_buttonText01 = nullptr,
			const char* a_buttonText02 = nullptr,
			const char* a_buttonText03 = nullptr,
			const char* a_buttonText04 = nullptr,
			WARNING_TYPES a_warningContext = WARNING_TYPES::Default,
			bool a_ensureUnique = false);

		void ShowMessages();

		void CreateImpl(
			const char* a_headerText,
			const char* a_bodyText,
			IMessageBoxCallback* a_callback = nullptr,
			WARNING_TYPES a_warningContext = WARNING_TYPES::Default,
			const char* a_buttonText01 = nullptr,
			const char* a_buttonText02 = nullptr,
			const char* a_buttonText03 = nullptr,
			const char* a_buttonText04 = nullptr,
			bool a_ensureUnique = false);

		// members
		mutable BSReadWriteLock messageRWLock;										  // 0x04
		BSTArray<MessageBoxData*> messages;											  // 0x10
		REX::Enum<WARNING_TYPES, std::int32_t> currentWarningContext;				  // 0x28
		std::array<bool, std::to_underlying(WARNING_TYPES::_Count)> disabledWarnings; // 0x2C
	};

	static_assert(sizeof(MessageMenuManager) == 0x50);
}
