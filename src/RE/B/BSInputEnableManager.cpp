#include "RE/B/BSInputEnableManager.hpp"

#include "RE/B/BSInputEnableLayer.hpp"
#include "RE/B/BSSpinLock.hpp"

namespace RE
{
	auto BSInputEnableManager::GetSingleton() noexcept -> BSInputEnableManager*
	{
		static const auto SINGLETON = REL::Relocation<BSInputEnableManager**>(ID::BSInputEnableManager::Singleton);
		return *SINGLETON;
	}

	auto BSInputEnableManager::AllocateNewLayer(BSTSmartPointer<BSInputEnableLayer>& a_layer, const char* a_debugName)
		-> bool
	{
		using FuncType = decltype(&BSInputEnableManager::AllocateNewLayer);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BSInputEnableManager::AllocateNewLayer);
		return std::invoke(FUNC, this, a_layer, a_debugName);
	}

	auto BSInputEnableManager::UserEventEnabled(UserEvents::USER_EVENT_FLAG a_userEventFlags) const -> bool
	{
		const auto inputFlagsLock = BSAutoSpinLock(cacheLock);
		return forceEnableInputUserEventsFlags.any(a_userEventFlags) ||
			   cachedInputUserEventsFlags.any(a_userEventFlags);
	}

	auto BSInputEnableManager::OtherEventEnabled(OtherInputEvents::OTHER_EVENT_FLAG a_otherEventFlag) const -> bool
	{
		const auto inputFlagsLock = BSAutoSpinLock(cacheLock);
		return forceOtherInputEventsFlags.any(a_otherEventFlag) || cachedOtherInputEventsFlags.any(a_otherEventFlag);
	}

	auto BSInputEnableManager::EnableUserEvent(
		std::uint32_t a_layerID,
		UserEvents::USER_EVENT_FLAG a_userEventFlags,
		bool a_enable,
		UserEvents::SENDER_ID a_senderID) -> bool
	{
		using FuncType = decltype(&BSInputEnableManager::EnableUserEvent);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BSInputEnableManager::EnableUserEvent);
		return std::invoke(FUNC, this, a_layerID, a_userEventFlags, a_enable, a_senderID);
	}

	auto BSInputEnableManager::EnableOtherEvent(
		std::uint32_t a_layerID,
		OtherInputEvents::OTHER_EVENT_FLAG a_otherEventFlags,
		bool a_enable,
		UserEvents::SENDER_ID a_senderID) -> bool
	{
		using FuncType = decltype(&BSInputEnableManager::EnableOtherEvent);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BSInputEnableManager::EnableOtherEvent);
		return std::invoke(FUNC, this, a_layerID, a_otherEventFlags, a_enable, a_senderID);
	}

	void BSInputEnableManager::ForceUserEventEnabled(UserEvents::USER_EVENT_FLAG a_userEventFlags, bool a_enable)
	{
		const auto inputFlagsLock = BSAutoSpinLock(cacheLock);
		forceEnableInputUserEventsFlags.set(a_enable, a_userEventFlags);
	}

	void BSInputEnableManager::ForceOtherEventEnabled(
		OtherInputEvents::OTHER_EVENT_FLAG a_otherEventFlags,
		bool a_enable)
	{
		const auto inputFlagsLock = BSAutoSpinLock(cacheLock);
		forceOtherInputEventsFlags.set(a_enable, a_otherEventFlags);
	}

	auto BSInputEnableManager::GetLayerDebugName(std::uint32_t a_layerID) const -> BSFixedString
	{
		const auto inputLayerLock = BSAutoSpinLock(layerLock);
		if (a_layerID >= debugNames.size()) {
			return {};
		}

		return debugNames[a_layerID];
	}

	auto BSInputEnableManager::GetLayerByID(std::uint32_t a_layerID) const -> BSTSmartPointer<BSInputEnableLayer>
	{
		const auto inputLayerLock = BSAutoSpinLock(layerLock);
		if (a_layerID >= layerWrappers.size()) {
			return {};
		}

		return layerWrappers[a_layerID];
	}

	void BSInputEnableManager::ClearForcedState()
	{
		const auto inputFlagsLock = BSAutoSpinLock(cacheLock);

		forceEnableInputUserEventsFlags.reset();
		forceOtherInputEventsFlags.reset();
	}
}
