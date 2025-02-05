#pragma once

#include "RE/Bethesda/BSFixedString.hpp"
#include "RE/Bethesda/BSString.hpp"
#include "RE/Bethesda/MemoryManager.hpp"

namespace RE
{
	namespace Scaleform::GFx
	{
		class Event;
	}

	enum class UI_MESSAGE_RESULTS
	{
		kHandled,
		kIgnore,
		kPassOn
	};

	enum class UI_MESSAGE_TYPE
	{
		kUpdate,
		kShow,
		kReshow,
		kHide,
		kForceHide,
		kScaleformEvent,
		kUserEvent,
		kInventoryUpdate,
		kUserProfileChange,
		kMUStatusChange,
		kResumeCaching,
		kUpdateController,
		kChatterEvent,
		kTotal
	};

	class IUIMessageData;

	class __declspec(novtable) UIMessage
	{
	public:
		inline static constexpr auto RTTI{ RTTI::UIMessage };
		inline static constexpr auto VTABLE{ VTABLE::UIMessage };

		virtual ~UIMessage() = default; // 00

		virtual IUIMessageData* QData() { return nullptr; }				// 02
		virtual const IUIMessageData* QData() const { return nullptr; } // 01

		F4_HEAP_REDEFINE_NEW(UIMessage);

		// members
		BSFixedString menu;														   // 08
		REX::Enum<UI_MESSAGE_TYPE, std::uint32_t> type{ UI_MESSAGE_TYPE::kTotal }; // 10
	};
	static_assert(sizeof(UIMessage) == 0x18);

	class __declspec(novtable) IUIMessageData
		: public UIMessage // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::IUIMessageData };
		inline static constexpr auto VTABLE{ VTABLE::IUIMessageData };

		// override (UIMessage)
		IUIMessageData* QData() override { return this; }			  // 02
		const IUIMessageData* QData() const override { return this; } // 01
	};
	static_assert(sizeof(IUIMessageData) == 0x18);

	class __declspec(novtable) BSUIMessageData
		: public IUIMessageData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSUIMessageData };
		inline static constexpr auto VTABLE{ VTABLE::BSUIMessageData };

		static void SendUIBoolMessage(const BSFixedString& a_menuName, UI_MESSAGE_TYPE a_type, bool a_value)
		{
			using func_t = decltype(&BSUIMessageData::SendUIBoolMessage);
			static REL::Relocation<func_t> func{ REL::ID(1388308) };
			return func(a_menuName, a_type, a_value);
		}

		static void SendUIStringMessage(const BSFixedString& a_menuName, UI_MESSAGE_TYPE a_type, const BSFixedString& a_string)
		{
			using func_t = decltype(&BSUIMessageData::SendUIStringMessage);
			static REL::Relocation<func_t> func{ REL::ID(1270833) };
			return func(a_menuName, a_type, a_string);
		}

		static void SendUIPtrMessage(const BSFixedString& a_menuName, UI_MESSAGE_TYPE a_type, void* a_data)
		{
			using func_t = decltype(&BSUIMessageData::SendUIPtrMessage);
			static REL::Relocation<func_t> func{ REL::ID(1374542) };
			return func(a_menuName, a_type, a_data);
		}

		static void SendUIStringUIntMessage(const BSFixedString& a_menuName, UI_MESSAGE_TYPE a_type, const BSFixedString& a_fixedString, std::uint32_t a_data)
		{
			using func_t = decltype(&BSUIMessageData::SendUIStringUIntMessage);
			static REL::Relocation<func_t> func{ REL::ID(99795) };
			return func(a_menuName, a_type, a_fixedString, a_data);
		}

		// members
		BSString* string{ nullptr }; // 18
		BSFixedString fixedString;	 // 20
		union
		{
			std::uint32_t u;
			void* p{ nullptr };
			float f;
			bool b;
		} data; // 28
	};
	static_assert(sizeof(BSUIMessageData) == 0x30);

	class __declspec(novtable) BSUIScaleformData
		: public IUIMessageData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSUIScaleformData };
		inline static constexpr auto VTABLE{ VTABLE::BSUIScaleformData };

		// members
		Scaleform::GFx::Event* scaleformEvent{ nullptr }; // 18
	};
	static_assert(sizeof(BSUIScaleformData) == 0x20);
}
