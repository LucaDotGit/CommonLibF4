#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSStringT.hpp"
#include "RE/I/IUIMessageData.hpp"

namespace RE
{
	class __declspec(novtable) BSUIMessageData
		: public IUIMessageData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSUIMessageData };
		inline static constexpr auto VTABLE{ VTABLE::BSUIMessageData };

		BSUIMessageData(BSFixedString a_menuName, UI_MESSAGE_TYPE a_type)
			: IUIMessageData(std::move(a_menuName), a_type)
		{
			REL::EmplaceVtable(this);
		}

		~BSUIMessageData() override = default; // 00

		static void SendUIBoolMessage(const BSFixedString& a_menuName, UI_MESSAGE_TYPE a_type, bool a_value)
		{
			using FuncType = decltype(&BSUIMessageData::SendUIBoolMessage);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BSUIMessageData::SendUIBoolMessage };
			std::invoke(FUNC, a_menuName, a_type, a_value);
		}

		static void SendUIStringMessage(const BSFixedString& a_menuName, UI_MESSAGE_TYPE a_type, const BSFixedString& a_string)
		{
			using FuncType = decltype(&BSUIMessageData::SendUIStringMessage);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BSUIMessageData::SendUIStringMessage };
			std::invoke(FUNC, a_menuName, a_type, a_string);
		}

		static void SendUIPtrMessage(const BSFixedString& a_menuName, UI_MESSAGE_TYPE a_type, void* a_data)
		{
			using FuncType = decltype(&BSUIMessageData::SendUIPtrMessage);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BSUIMessageData::SendUIPtrMessage };
			std::invoke(FUNC, a_menuName, a_type, a_data);
		}

		static void SendUIStringUIntMessage(const BSFixedString& a_menuName, UI_MESSAGE_TYPE a_type, const BSFixedString& a_fixedString, std::uint32_t a_data)
		{
			using FuncType = decltype(&BSUIMessageData::SendUIStringUIntMessage);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BSUIMessageData::SendUIStringUIntMessage };
			std::invoke(FUNC, a_menuName, a_type, a_fixedString, a_data);
		}

		// members
		BSString* string{ nullptr }; // 18
		BSFixedString fixedString;	 // 20
		union
		{
			bool boolean;
			std::uint32_t uint32;
			REX::Float32 float32;
			void* ptr{ nullptr };
		} data; // 28
	};
	static_assert(sizeof(BSUIMessageData) == 0x30);
}
