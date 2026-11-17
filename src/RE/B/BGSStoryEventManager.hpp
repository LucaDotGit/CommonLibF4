#pragma once

#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BSTSingleton.hpp"

namespace RE
{
	class BGSRegisteredStoryEvent;
	class BGSStoryEvent;

	class BGSStoryEventManager : public BSTSingletonImplicit<BGSStoryEventManager> // 0x00
	{
	public:
		[[nodiscard]]
		static auto GetSingleton() noexcept -> BGSStoryEventManager*
		{
			static const auto SINGLETON = REL::Relocation<BGSStoryEventManager**>(ID::BGSStoryEventManager::Singleton);
			return *SINGLETON;
		}

		auto AddEvent(std::uint32_t a_index, const void* a_event) -> std::uint32_t
		{
			using FuncType = std::uint32_t (BGSStoryEventManager::*)(std::uint32_t, const void*);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSStoryEventManager::AddEvent);
			return std::invoke(FUNC, this, a_index, a_event);
		}

		template <class T>
		auto AddEvent(const T& a_event) -> std::uint32_t
			requires(std::is_invocable_r_v<std::uint32_t, decltype(&T::GetEventIndex), const T&>)
		{
			return AddEvent(T::GetEventIndex(), std::addressof(a_event));
		}

		// members
		BSTArray<BGSRegisteredStoryEvent> registeredEvents;			   // 0x00
		BSTHashMap<std::uint32_t, std::uint32_t> registeredEventIDMap; // 0x18
		BSTArray<BGSStoryEvent> events;								   // 0x48
		mutable BSSpinLock eventsLock;								   // 0x60
	};

	static_assert(sizeof(BGSStoryEventManager) == 0x68);
}
