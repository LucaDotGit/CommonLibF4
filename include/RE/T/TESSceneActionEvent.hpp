#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::REFREventCallbacks
{
	class IEventCallback;
}

namespace RE
{
	class TESSceneActionEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESSceneActionEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESSceneActionEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESSceneActionEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		TESFormID sceneFormID;										  // 00
		std::uint32_t actionID;										  // 04
		TESFormID questFormID;										  // 08
		std::uint32_t refAliasID;									  // 0C
		std::uint16_t questStageID;									  // 10
		BSTSmartPointer<REFREventCallbacks::IEventCallback> callback; // 18
	};
	static_assert(sizeof(TESSceneActionEvent) == 0x20);
}
