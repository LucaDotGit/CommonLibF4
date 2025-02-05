#pragma once

#include "RE/Bethesda/BSFixedString.hpp"
#include "RE/Bethesda/BSLock.hpp"
#include "RE/Bethesda/BSTArray.hpp"
#include "RE/Bethesda/BSTSingleton.hpp"
#include "RE/Bethesda/BSTSmartPointer.hpp"
#include "RE/Bethesda/UserEvents.hpp"

namespace RE
{
	class InputEnableLayerDestroyedEvent;
	class OtherEventEnabledEvent;
	class UserEventEnabledEvent;

	namespace OtherInputEvents
	{
		enum class OTHER_EVENT_FLAGS
		{
			kAll = static_cast<std::underlying_type_t<OTHER_EVENT_FLAGS>>(-1),

			kJournalTabs = 1 << 0,
			kActivation = 1 << 1,
			kFastTravel = 1 << 2,
			kPOVChange = 1 << 3,
			kVATS = 1 << 4,
			kFavorites = 1 << 5,
			kPipboyLight = 1 << 6,
			kZKey = 1 << 7,
			kRunning = 1 << 8,
			kCursor = 1 << 9,
			kSprinting = 1 << 10,
		};
	}

	class BSInputEnableLayer
	{
	public:
		constexpr BSInputEnableLayer() noexcept {} // NOLINT(modernize-use-equals-default)

		[[nodiscard]] std::uint32_t DecRef() const
		{
			using func_t = decltype(&BSInputEnableLayer::DecRef);
			static REL::Relocation<func_t> func{ REL::RelocationID(659989, 2268272) };
			return func(this);
		}

		std::uint32_t IncRef() const
		{
			stl::atomic_ref myRefCount{ refCount };
			return ++myRefCount;
		}

		// members
		std::uint32_t layerID;			// 00
		mutable std::uint32_t refCount; // 04
	};
	static_assert(sizeof(BSInputEnableLayer) == 0x08);

	class BSInputEnableManager
		: public BSTEventSource<UserEventEnabledEvent>,			 // 000
		  public BSTEventSource<OtherEventEnabledEvent>,		 // 058
		  public BSTEventSource<InputEnableLayerDestroyedEvent>, // 0B0
		  public BSTSingletonSDM<BSInputEnableManager>			 // 108
	{
	public:
		struct EnableLayer
		{
		public:
			// members
			REX::EnumSet<UserEvents::USER_EVENT_FLAGS, std::uint32_t> inputUserEvents;		   // 00
			REX::EnumSet<OtherInputEvents::OTHER_EVENT_FLAGS, std::uint32_t> otherInputEvents; // 04
		};
		static_assert(sizeof(EnableLayer) == 0x08);

		[[nodiscard]] static BSInputEnableManager* GetSingleton()
		{
			static REL::Relocation<BSInputEnableManager**> singleton{ REL::RelocationID(781703, 2689007) };
			return *singleton;
		}

		bool AllocateNewLayer(BSTSmartPointer<BSInputEnableLayer>& a_layer, const char* a_debugName)
		{
			using func_t = decltype(&BSInputEnableManager::AllocateNewLayer);
			static REL::Relocation<func_t> func{ REL::RelocationID(537494, 2268244) };
			return func(this, a_layer, a_debugName);
		}

		void ClearForcedState()
		{
			BSAutoLock locker(cacheLock);
			forceEnableInputUserEventsFlags.reset();
			forceOtherInputEventsFlags.reset();
		}

		bool EnableUserEvent(std::uint32_t a_layerID, UserEvents::USER_EVENT_FLAGS a_userEventFlags, bool a_enable, UserEvents::SENDER_ID a_senderID)
		{
			using func_t = decltype(&BSInputEnableManager::EnableUserEvent);
			static REL::Relocation<func_t> func{ REL::RelocationID(1432984, 2268263) };
			return func(this, a_layerID, a_userEventFlags, a_enable, a_senderID);
		}

		bool EnableOtherEvent(std::uint32_t a_layerID, OtherInputEvents::OTHER_EVENT_FLAGS a_otherEventFlags, bool a_enable, UserEvents::SENDER_ID a_senderID)
		{
			using func_t = decltype(&BSInputEnableManager::EnableOtherEvent);
			static REL::Relocation<func_t> func{ REL::RelocationID(1419268, 2268265) };
			return func(this, a_layerID, a_otherEventFlags, a_enable, a_senderID);
		}

		void ForceUserEventEnabled(UserEvents::USER_EVENT_FLAGS a_userEventFlags, bool a_enable)
		{
			BSAutoLock locker(cacheLock);
			if (a_enable) {
				forceEnableInputUserEventsFlags.set(a_userEventFlags);
			}
			else {
				forceEnableInputUserEventsFlags.reset(a_userEventFlags);
			}
		}

		void ForceOtherEventEnabled(OtherInputEvents::OTHER_EVENT_FLAGS a_otherEventFlags, bool a_enable)
		{
			BSAutoLock locker(cacheLock);
			if (a_enable) {
				forceOtherInputEventsFlags.set(a_otherEventFlags);
			}
			else {
				forceOtherInputEventsFlags.reset(a_otherEventFlags);
			}
		}

		// members
		mutable BSSpinLock cacheLock;																  // 110
		REX::EnumSet<UserEvents::USER_EVENT_FLAGS, std::uint32_t> cachedInputUserEventsFlags;		  // 118
		REX::EnumSet<OtherInputEvents::OTHER_EVENT_FLAGS, std::uint32_t> cachedOtherInputEventsFlags; // 11C
		REX::EnumSet<UserEvents::USER_EVENT_FLAGS, std::uint32_t> forceEnableInputUserEventsFlags;	  // 120
		REX::EnumSet<OtherInputEvents::OTHER_EVENT_FLAGS, std::uint32_t> forceOtherInputEventsFlags;  // 124
		mutable BSSpinLock layerLock;																  // 128
		BSTArray<BSInputEnableManager::EnableLayer> layers;											  // 130
		BSTArray<BSTSmartPointer<BSInputEnableLayer>> layerWrappers;								  // 148
		BSTArray<BSFixedString> debugNames;															  // 160
		bool isCurrentlyInSaveLoad;																	  // 178
	};
	static_assert(sizeof(BSInputEnableManager) == 0x180);
}
