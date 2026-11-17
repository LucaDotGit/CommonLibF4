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
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESSceneActionEvent>*
		{
			using FuncType = decltype(&TESSceneActionEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESSceneActionEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		TESFormID sceneFormID;										  // 0x00
		std::uint32_t actionID;										  // 0x04
		TESFormID questFormID;										  // 0x08
		std::uint32_t refAliasID;									  // 0x0C
		std::uint16_t questStageID;									  // 0x10
		BSTSmartPointer<REFREventCallbacks::IEventCallback> callback; // 0x18
	};

	static_assert(sizeof(TESSceneActionEvent) == 0x20);
}
