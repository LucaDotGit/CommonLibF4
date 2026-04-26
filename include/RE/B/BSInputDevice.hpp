#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE
{
	enum class INPUT_DEVICE : std::int32_t;

	class __declspec(novtable) BSInputDevice
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSInputDevice };
		inline static constexpr auto VTABLE{ VTABLE::BSInputDevice };

		class InputButton
		{
		public:
			GAME_HEAP_REDEFINE_NEW(InputButton);

			// members
			BSFixedStringCS name;	   // 00
			REX::Float32 heldDownSecs; // 08
			std::uint32_t keyCode;	   // 0C
		};
		static_assert(sizeof(InputButton) == 0x10);

		using ButtonID = std::uint32_t;

		// add
		virtual void Initialize() = 0;					 // 00
		virtual void Poll(REX::Float32 a_deltaTime) = 0; // 01
		virtual void Shutdown() = 0;					 // 02
		virtual bool IsConnected() const;				 // 03 - { return true; }
		virtual ~BSInputDevice();						 // 04
		virtual void ClearInputState() = 0;				 // 05

		GAME_HEAP_REDEFINE_NEW(BSInputDevice);

		[[nodiscard]] bool ContainsButtonID(ButtonID a_buttonID) const;
		[[nodiscard]] bool ContainsButtonName(const BSFixedStringCS& a_name) const;

		[[nodiscard]] auto GetButtonInfoByID(ButtonID a_buttonID) const -> std::optional<std::pair<ButtonID, InputButton*>>;
		[[nodiscard]] auto GetButtonInfoByName(const BSFixedStringCS& a_name) const -> std::optional<std::pair<ButtonID, InputButton*>>;

		void CreateButtonEvent(ButtonID a_buttonID, REX::Float32 a_deltaTime, bool a_prevPressed, bool a_currPressed);

		// members
		REX::Enum<INPUT_DEVICE, std::int32_t> deviceType;	   // 08
		std::int32_t deviceID;								   // 0C
		BSTHashMap<ButtonID, InputButton*> deviceButtons;	   // 10
		BSTHashMap<BSFixedStringCS, ButtonID> buttonNameIDMap; // 40
	};
	static_assert(sizeof(BSInputDevice) == 0x70);
}
