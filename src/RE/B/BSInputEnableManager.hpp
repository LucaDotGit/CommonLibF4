#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::OtherInputEvents
{
	enum class OTHER_EVENT_FLAG : std::uint32_t;
}

namespace RE::UserEvents
{
	enum class SENDER_ID : std::int32_t;
	enum class USER_EVENT_FLAG : std::uint32_t;
}

namespace RE
{
	class InputEnableLayerDestroyedEvent;
	class OtherEventEnabledEvent;
	class UserEventEnabledEvent;

	class BSInputEnableManager :
		public BSTSingletonSDM<BSInputEnableManager>,		  // 0x000
		public BSTEventSource<UserEventEnabledEvent>,		  // 0x008
		public BSTEventSource<OtherEventEnabledEvent>,		  // 0x060
		public BSTEventSource<InputEnableLayerDestroyedEvent> // 0x0B8
	{
	public:
		class ActiveDisableLayerInfo
		{
		public:
			// members
			std::uint32_t layerID;															 // 0x00
			BSFixedString debugName;														 // 0x08
			REX::EnumSet<UserEvents::USER_EVENT_FLAG, std::uint32_t> userEventFlags;		 // 0x10
			REX::EnumSet<OtherInputEvents::OTHER_EVENT_FLAG, std::uint32_t> otherEventFlags; // 0x14
		};

		static_assert(sizeof(ActiveDisableLayerInfo) == 0x18);

		class EnableLayer
		{
		public:
			// members
			REX::EnumSet<UserEvents::USER_EVENT_FLAG, std::uint32_t> inputUserEvents;		  // 0x00
			REX::EnumSet<OtherInputEvents::OTHER_EVENT_FLAG, std::uint32_t> otherInputEvents; // 0x04
		};

		static_assert(sizeof(EnableLayer) == 0x08);

		[[nodiscard]]
		static auto GetSingleton() noexcept -> BSInputEnableManager*;

		auto AllocateNewLayer(BSTSmartPointer<BSInputEnableLayer>& a_layer, const char* a_debugName = "") -> bool;
		[[nodiscard]]
		auto UserEventEnabled(UserEvents::USER_EVENT_FLAG a_userEventFlags) const -> bool;
		[[nodiscard]]
		auto OtherEventEnabled(OtherInputEvents::OTHER_EVENT_FLAG a_otherEventFlag) const -> bool;
		auto EnableUserEvent(
			std::uint32_t a_layerID,
			UserEvents::USER_EVENT_FLAG a_userEventFlags,
			bool a_enable,
			UserEvents::SENDER_ID a_senderID) -> bool;
		auto EnableOtherEvent(
			std::uint32_t a_layerID,
			OtherInputEvents::OTHER_EVENT_FLAG a_otherEventFlags,
			bool a_enable,
			UserEvents::SENDER_ID a_senderID) -> bool;
		void ForceUserEventEnabled(UserEvents::USER_EVENT_FLAG a_userEventFlags, bool a_enable);
		void ForceOtherEventEnabled(OtherInputEvents::OTHER_EVENT_FLAG a_otherEventFlags, bool a_enable);
		[[nodiscard]]
		auto GetLayerDebugName(std::uint32_t a_layerID) const -> BSFixedString;
		[[nodiscard]]
		auto GetLayerByID(std::uint32_t a_layerID) const -> BSTSmartPointer<BSInputEnableLayer>;
		void ClearForcedState();

		// members
		mutable BSSpinLock cacheLock;																 // 0x110
		REX::EnumSet<UserEvents::USER_EVENT_FLAG, std::uint32_t> cachedInputUserEventsFlags;		 // 0x118
		REX::EnumSet<OtherInputEvents::OTHER_EVENT_FLAG, std::uint32_t> cachedOtherInputEventsFlags; // 0x11C
		REX::EnumSet<UserEvents::USER_EVENT_FLAG, std::uint32_t> forceEnableInputUserEventsFlags;	 // 0x120
		REX::EnumSet<OtherInputEvents::OTHER_EVENT_FLAG, std::uint32_t> forceOtherInputEventsFlags;	 // 0x124
		mutable BSSpinLock layerLock;																 // 0x128
		BSTArray<EnableLayer> layers;																 // 0x130
		BSTArray<BSTSmartPointer<BSInputEnableLayer>> layerWrappers;								 // 0x148
		BSTArray<BSFixedString> debugNames;															 // 0x160
		bool isCurrentlyInSaveLoad;																	 // 0x178
	};

	static_assert(sizeof(BSInputEnableManager) == 0x180);
}
