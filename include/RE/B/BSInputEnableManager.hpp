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

	class BSInputEnableManager
		: public BSTSingletonSDM<BSInputEnableManager>,			// 000
		  public BSTEventSource<UserEventEnabledEvent>,			// 008
		  public BSTEventSource<OtherEventEnabledEvent>,		// 060
		  public BSTEventSource<InputEnableLayerDestroyedEvent> // 0B8
	{
	public:
		class ActiveDisableLayerInfo
		{
		public:
			// members
			std::uint32_t layerID;															 // 00
			BSFixedString debugName;														 // 08
			REX::EnumSet<UserEvents::USER_EVENT_FLAG, std::uint32_t> userEventFlags;		 // 10
			REX::EnumSet<OtherInputEvents::OTHER_EVENT_FLAG, std::uint32_t> otherEventFlags; // 14
		};
		static_assert(sizeof(ActiveDisableLayerInfo) == 0x18);

		class EnableLayer
		{
		public:
			// members
			REX::EnumSet<UserEvents::USER_EVENT_FLAG, std::uint32_t> inputUserEvents;		  // 00
			REX::EnumSet<OtherInputEvents::OTHER_EVENT_FLAG, std::uint32_t> otherInputEvents; // 04
		};
		static_assert(sizeof(EnableLayer) == 0x08);

		[[nodiscard]] static BSInputEnableManager* GetSingleton();

		bool AllocateNewLayer(BSTSmartPointer<BSInputEnableLayer>& a_layer, const char* a_debugName = "");
		[[nodiscard]] bool UserEventEnabled(UserEvents::USER_EVENT_FLAG a_userEventFlags) const;
		[[nodiscard]] bool OtherEventEnabled(OtherInputEvents::OTHER_EVENT_FLAG a_otherEventFlag) const;
		bool EnableUserEvent(std::uint32_t a_layerID, UserEvents::USER_EVENT_FLAG a_userEventFlags, bool a_enable, UserEvents::SENDER_ID a_senderID);
		bool EnableOtherEvent(std::uint32_t a_layerID, OtherInputEvents::OTHER_EVENT_FLAG a_otherEventFlags, bool a_enable, UserEvents::SENDER_ID a_senderID);
		void ForceUserEventEnabled(UserEvents::USER_EVENT_FLAG a_userEventFlags, bool a_enable);
		void ForceOtherEventEnabled(OtherInputEvents::OTHER_EVENT_FLAG a_otherEventFlags, bool a_enable);
		[[nodiscard]] BSFixedString GetLayerDebugName(std::uint32_t a_layerID) const;
		[[nodiscard]] BSTSmartPointer<BSInputEnableLayer> GetLayerByID(std::uint32_t a_layerID) const;
		void ClearForcedState();

		// members
		mutable BSSpinLock cacheLock;																 // 110
		REX::EnumSet<UserEvents::USER_EVENT_FLAG, std::uint32_t> cachedInputUserEventsFlags;		 // 118
		REX::EnumSet<OtherInputEvents::OTHER_EVENT_FLAG, std::uint32_t> cachedOtherInputEventsFlags; // 11C
		REX::EnumSet<UserEvents::USER_EVENT_FLAG, std::uint32_t> forceEnableInputUserEventsFlags;	 // 120
		REX::EnumSet<OtherInputEvents::OTHER_EVENT_FLAG, std::uint32_t> forceOtherInputEventsFlags;	 // 124
		mutable BSSpinLock layerLock;																 // 128
		BSTArray<EnableLayer> layers;																 // 130
		BSTArray<BSTSmartPointer<BSInputEnableLayer>> layerWrappers;								 // 148
		BSTArray<BSFixedString> debugNames;															 // 160
		bool isCurrentlyInSaveLoad;																	 // 178
	};
	static_assert(sizeof(BSInputEnableManager) == 0x180);
}
