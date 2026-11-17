#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/I/INPUT_DEVICE.hpp"
#include "RE/M/MemoryManager.hpp"
#include "RE/U/UserEvents.hpp"

namespace RE
{
	enum class PC_GAMEPAD_TYPE : std::int32_t;

	class ControlMap : public BSTSingletonSDM<ControlMap> // 0x00
	{
	private:
		using INPUT_CONTEXT = UserEvents::INPUT_CONTEXT_ID;

	public:
		class UserEventMapping
		{
		public:
			// members
			BSFixedString eventID;														 // 0x00
			std::int32_t inputKey;														 // 0x08
			std::int8_t byIndexInContext;												 // 0x0C
			bool remappable;															 // 0x0D
			bool linked;																 // 0x0E
			REX::EnumSet<UserEvents::USER_EVENT_FLAG, std::uint32_t> userEventGroupFlag; // 0x10
		};

		static_assert(sizeof(UserEventMapping) == 0x18);

		class InputContext
		{
		public:
			GAME_HEAP_REDEFINE_NEW(InputContext);

			// members
			std::array<BSTArray<UserEventMapping>, std::to_underlying(INPUT_DEVICE::Supported)> deviceMappings; // 0x00
		};

		static_assert(sizeof(InputContext) == 0x48);

		class LinkedMapping
		{
		public:
			// members
			BSFixedString linkedMappingName;							 // 0x00
			REX::Enum<INPUT_CONTEXT, std::int32_t> linkedMappingContext; // 0x08
			REX::Enum<INPUT_DEVICE, std::int32_t> device;				 // 0x0C
			REX::Enum<INPUT_CONTEXT, std::int32_t> linkFromContext;		 // 0x10
			BSFixedString linkFromName;									 // 0x18
		};

		static_assert(sizeof(LinkedMapping) == 0x20);

		[[nodiscard]]
		static auto GetSingleton() noexcept -> ControlMap*;

		[[nodiscard]]
		auto ContainsControlName(
			const BSFixedString& a_controlName,
			INPUT_DEVICE a_deviceType,
			INPUT_CONTEXT a_inputContext = INPUT_CONTEXT::MainGameplay) const -> bool;
		[[nodiscard]]
		auto GetControlNameByKeyCode(
			std::uint32_t a_keyCode,
			INPUT_DEVICE a_deviceType,
			INPUT_CONTEXT a_inputContext = INPUT_CONTEXT::MainGameplay) const -> std::optional<BSFixedString>;
		[[nodiscard]]
		auto GetKeyCodeByControlName(
			const BSFixedString& a_controlName,
			INPUT_DEVICE a_deviceType,
			INPUT_CONTEXT a_inputContext = INPUT_CONTEXT::MainGameplay) const -> std::optional<std::uint32_t>;
		auto PopInputContext(INPUT_CONTEXT a_inputContext) -> bool;
		void PushInputContext(INPUT_CONTEXT a_inputContext);
		auto RemapButton(const BSFixedString& a_id, INPUT_DEVICE a_deviceType, std::int32_t a_buttonID) -> bool;
		void SaveRemappings();
		void SetTextEntryMode(bool a_enable);

		// members
		std::array<InputContext*, std::to_underlying(INPUT_CONTEXT::_Count)> controlMaps; // 0x008
		BSTArray<LinkedMapping> linkedMappings;											  // 0x110
		BSTArray<REX::Enum<INPUT_CONTEXT, std::int32_t>> contextPriorityStack;			  // 0x128
		std::int8_t byTextEntryCount;													  // 0x140
		bool ignoreKeyboardMouse;														  // 0x141
		bool ignoreActivateDisabledEvents;												  // 0x142
		REX::Enum<PC_GAMEPAD_TYPE, std::int32_t> pcGamepadMapType;						  // 0x144
	};

	static_assert(sizeof(ControlMap) == 0x148);
}
