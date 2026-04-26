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

	class ControlMap
		: public BSTSingletonSDM<ControlMap> // 00
	{
	private:
		using INPUT_CONTEXT = UserEvents::INPUT_CONTEXT_ID;

	public:
		class UserEventMapping
		{
		public:
			// members
			BSFixedString eventID;														 // 00
			std::int32_t inputKey;														 // 08
			std::int8_t byIndexInContext;												 // 0C
			bool remappable;															 // 0D
			bool linked;																 // 0E
			REX::EnumSet<UserEvents::USER_EVENT_FLAG, std::uint32_t> userEventGroupFlag; // 10
		};
		static_assert(sizeof(UserEventMapping) == 0x18);

		class InputContext
		{
		public:
			GAME_HEAP_REDEFINE_NEW(InputContext);

			// members
			std::array<BSTArray<UserEventMapping>, std::to_underlying(INPUT_DEVICE::kSupported)> deviceMappings; // 00
		};
		static_assert(sizeof(InputContext) == 0x48);

		class LinkedMapping
		{
		public:
			// members
			BSFixedString linkedMappingName;							 // 00
			REX::Enum<INPUT_CONTEXT, std::int32_t> linkedMappingContext; // 08
			REX::Enum<INPUT_DEVICE, std::int32_t> device;				 // 0C
			REX::Enum<INPUT_CONTEXT, std::int32_t> linkFromContext;		 // 10
			BSFixedString linkFromName;									 // 18
		};
		static_assert(sizeof(LinkedMapping) == 0x20);

		[[nodiscard]] static ControlMap* GetSingleton();

		[[nodiscard]] bool ContainsControlName(const BSFixedString& a_controlName, INPUT_DEVICE a_deviceType, INPUT_CONTEXT a_inputContext = INPUT_CONTEXT::kMainGameplay) const;
		[[nodiscard]] auto GetControlNameByKeyCode(std::uint32_t a_keyCode, INPUT_DEVICE a_deviceType, INPUT_CONTEXT a_inputContext = INPUT_CONTEXT::kMainGameplay) const
			-> std::optional<BSFixedString>;
		[[nodiscard]] auto GetKeyCodeByControlName(const BSFixedString& a_controlName, INPUT_DEVICE a_deviceType, INPUT_CONTEXT a_inputContext = INPUT_CONTEXT::kMainGameplay) const
			-> std::optional<std::uint32_t>;
		bool PopInputContext(INPUT_CONTEXT a_inputContext);
		void PushInputContext(INPUT_CONTEXT a_inputContext);
		bool RemapButton(const BSFixedString& a_id, INPUT_DEVICE a_deviceType, std::int32_t a_buttonID);
		void SaveRemappings();
		void SetTextEntryMode(bool a_enable);

		// members
		std::array<InputContext*, std::to_underlying(INPUT_CONTEXT::kTotal)> controlMaps; // 008
		BSTArray<LinkedMapping> linkedMappings;											  // 110
		BSTArray<REX::Enum<INPUT_CONTEXT, std::int32_t>> contextPriorityStack;			  // 128
		std::int8_t byTextEntryCount;													  // 140
		bool ignoreKeyboardMouse;														  // 141
		bool ignoreActivateDisabledEvents;												  // 142
		REX::Enum<PC_GAMEPAD_TYPE, std::int32_t> pcGamepadMapType;						  // 144
	};
	static_assert(sizeof(ControlMap) == 0x148);
}
