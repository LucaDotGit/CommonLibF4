#pragma once

#include "RE/B/BSString.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/I/IMessageBoxCallback.hpp"
#include "RE/I/IUIMessageData.hpp"

namespace RE
{
	enum class UI_DEPTH_PRIORITY : std::int32_t;
	enum class WARNING_TYPES : std::int32_t;

	class __declspec(novtable) MessageBoxData : public IUIMessageData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::MessageBoxData;
		inline static constexpr const auto& VTABLE = VTABLE::MessageBoxData;

		MessageBoxData(BSFixedString a_menuName, UI_MESSAGE_TYPE a_type) :
			IUIMessageData(std::move(a_menuName), a_type)
		{
			REL::EmplaceVtable(this);
		}

		~MessageBoxData() override = default; // 0x00

		// members
		BSString headerText;								   // 0x18
		BSString bodyText;									   // 0x28
		BSTArray<BSString> buttonText;						   // 0x38
		REX::Enum<WARNING_TYPES, std::int32_t> warningContext; // 0x50
		BSTSmartPointer<IMessageBoxCallback> callback;		   // 0x58
		REX::Enum<UI_DEPTH_PRIORITY, std::int32_t> menuDepth;  // 0x60
		bool modal{false};									   // 0x64
		bool ensureUnique{false};							   // 0x65
	};

	static_assert(sizeof(MessageBoxData) == 0x68);
}
