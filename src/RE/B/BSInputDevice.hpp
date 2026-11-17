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
		inline static constexpr const auto& RTTI = RTTI::BSInputDevice;
		inline static constexpr const auto& VTABLE = VTABLE::BSInputDevice;

		class InputButton
		{
		public:
			GAME_HEAP_REDEFINE_NEW(InputButton);

			// members
			BSFixedStringCS name;	   // 0x00
			REX::Float32 heldDownSecs; // 0x08
			std::uint32_t keyCode;	   // 0x0C
		};

		static_assert(sizeof(InputButton) == 0x10);

		using ButtonID = std::uint32_t;
		using DeltaTime = REX::Float32;

		// add
		virtual void Initialize() = 0;				  // 0x00
		virtual void Poll(DeltaTime a_deltaTime) = 0; // 0x01
		virtual void Shutdown() = 0;				  // 0x02
		virtual auto IsConnected() const -> bool;	  // 0x03 - { return true; }
		virtual ~BSInputDevice();					  // 0x04
		virtual void ClearInputState() = 0;			  // 0x05

		GAME_HEAP_REDEFINE_NEW(BSInputDevice);

		[[nodiscard]]
		auto ContainsButtonID(ButtonID a_buttonID) const -> bool;
		[[nodiscard]]
		auto ContainsButtonName(const BSFixedStringCS& a_name) const -> bool;

		[[nodiscard]]
		auto GetButtonInfoByID(ButtonID a_buttonID) const -> std::optional<std::pair<ButtonID, InputButton*>>;
		[[nodiscard]]
		auto GetButtonInfoByName(const BSFixedStringCS& a_name) const
			-> std::optional<std::pair<ButtonID, InputButton*>>;

		void CreateButtonEvent(ButtonID a_buttonID, DeltaTime a_deltaTime, bool a_prevPressed, bool a_currPressed);

		// members
		REX::Enum<INPUT_DEVICE, std::int32_t> deviceType;	   // 0x08
		std::int32_t deviceID;								   // 0x0C
		BSTHashMap<ButtonID, InputButton*> deviceButtons;	   // 0x10
		BSTHashMap<BSFixedStringCS, ButtonID> buttonNameIDMap; // 0x40
	};

	static_assert(sizeof(BSInputDevice) == 0x70);
}
