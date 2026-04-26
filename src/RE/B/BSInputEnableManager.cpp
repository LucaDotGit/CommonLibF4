#include "RE/B/BSInputEnableManager.hpp"

#include "RE/B/BSInputEnableLayer.hpp"

namespace RE
{
	BSInputEnableManager* BSInputEnableManager::GetSingleton()
	{
		static const auto SINGLETON = REL::Relocation<BSInputEnableManager**>{ ID::BSInputEnableManager::Singleton };
		return *SINGLETON;
	}

	bool BSInputEnableManager::AllocateNewLayer(BSTSmartPointer<BSInputEnableLayer>& a_layer, const char* a_debugName)
	{
		using FuncType = decltype(&BSInputEnableManager::AllocateNewLayer);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BSInputEnableManager::AllocateNewLayer };
		return std::invoke(FUNC, this, a_layer, a_debugName);
	}

	bool BSInputEnableManager::UserEventEnabled(UserEvents::USER_EVENT_FLAG a_userEventFlags) const
	{
		const auto inputFlagsLock = BSAutoLock(cacheLock);
		return forceEnableInputUserEventsFlags.any(a_userEventFlags) ||
			   cachedInputUserEventsFlags.any(a_userEventFlags);
	}

	bool BSInputEnableManager::OtherEventEnabled(OtherInputEvents::OTHER_EVENT_FLAG a_otherEventFlag) const
	{
		const auto inputFlagsLock = BSAutoLock(cacheLock);
		return forceOtherInputEventsFlags.any(a_otherEventFlag) ||
			   cachedOtherInputEventsFlags.any(a_otherEventFlag);
	}

	bool BSInputEnableManager::EnableUserEvent(std::uint32_t a_layerID, UserEvents::USER_EVENT_FLAG a_userEventFlags, bool a_enable, UserEvents::SENDER_ID a_senderID)
	{
		using FuncType = decltype(&BSInputEnableManager::EnableUserEvent);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BSInputEnableManager::EnableUserEvent };
		return std::invoke(FUNC, this, a_layerID, a_userEventFlags, a_enable, a_senderID);
	}

	bool BSInputEnableManager::EnableOtherEvent(std::uint32_t a_layerID, OtherInputEvents::OTHER_EVENT_FLAG a_otherEventFlags, bool a_enable, UserEvents::SENDER_ID a_senderID)
	{
		using FuncType = decltype(&BSInputEnableManager::EnableOtherEvent);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BSInputEnableManager::EnableOtherEvent };
		return std::invoke(FUNC, this, a_layerID, a_otherEventFlags, a_enable, a_senderID);
	}

	void BSInputEnableManager::ForceUserEventEnabled(UserEvents::USER_EVENT_FLAG a_userEventFlags, bool a_enable)
	{
		const auto inputFlagsLock = BSAutoLock(cacheLock);
		forceEnableInputUserEventsFlags.set(a_enable, a_userEventFlags);
	}

	void BSInputEnableManager::ForceOtherEventEnabled(OtherInputEvents::OTHER_EVENT_FLAG a_otherEventFlags, bool a_enable)
	{
		const auto inputFlagsLock = BSAutoLock(cacheLock);
		forceOtherInputEventsFlags.set(a_enable, a_otherEventFlags);
	}

	BSFixedString BSInputEnableManager::GetLayerDebugName(std::uint32_t a_layerID) const
	{
		const auto inputLayerLock = BSAutoLock(layerLock);
		if (a_layerID >= debugNames.size()) {
			return {};
		}

		return debugNames[a_layerID];
	}

	BSTSmartPointer<BSInputEnableLayer> BSInputEnableManager::GetLayerByID(std::uint32_t a_layerID) const
	{
		const auto inputLayerLock = BSAutoLock(layerLock);
		if (a_layerID >= layerWrappers.size()) {
			return {};
		}

		return layerWrappers[a_layerID];
	}

	void BSInputEnableManager::ClearForcedState()
	{
		const auto inputFlagsLock = BSAutoLock(cacheLock);

		forceEnableInputUserEventsFlags.reset();
		forceOtherInputEventsFlags.reset();
	}
}
