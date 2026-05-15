#pragma once

#include "RE/B/BSStringT.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/I/IMessageBoxCallback.hpp"
#include "RE/I/IUIMessageData.hpp"

namespace RE
{
	enum class UI_DEPTH_PRIORITY : std::int32_t;
	enum class WARNING_TYPES : std::int32_t;

	class __declspec(novtable) MessageBoxData
		: public IUIMessageData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::MessageBoxData };
		inline static constexpr auto VTABLE{ VTABLE::MessageBoxData };

		MessageBoxData(BSFixedString a_menuName, UI_MESSAGE_TYPE a_type)
			: IUIMessageData(std::move(a_menuName), a_type)
		{
			REL::EmplaceVtable(this);
		}

		~MessageBoxData() override = default; // 00

		// members
		BSString headerText;								   // 18
		BSString bodyText;									   // 28
		BSTArray<BSString> buttonText;						   // 38
		REX::Enum<WARNING_TYPES, std::int32_t> warningContext; // 50
		BSTSmartPointer<IMessageBoxCallback> callback;		   // 58
		REX::Enum<UI_DEPTH_PRIORITY, std::int32_t> menuDepth;  // 60
		bool modal{ false };								   // 64
		bool ensureUnique{ false };							   // 65
	};
	static_assert(sizeof(MessageBoxData) == 0x68);
}
