#pragma once

#include "RE/B/BSTEvent.hpp"
#include "Scaleform/G/GFx_Value.hpp"

namespace RE
{
	class PipboyValueChangedEvent;

	class __declspec(novtable) PipboySubMenu : public BSTEventSink<PipboyValueChangedEvent> // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::PipboySubMenu;
		inline static constexpr const auto& VTABLE = VTABLE::PipboySubMenu;

		PipboySubMenu(Scaleform::GFx::Value& a_dataObj, Scaleform::GFx::Value& a_menuObj) :
			dataObj(a_dataObj),
			menuObj(a_menuObj)
		{
			REL::EmplaceVtable(this);
		}

		~PipboySubMenu() override; // 0x00

		// override (BSTEventSink<PipboyValueChangedEvent>)
		auto ProcessEvent(
			const PipboyValueChangedEvent& a_event,
			BSTEventSource<PipboyValueChangedEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// add
		virtual void UpdateData() = 0; // 0x02

		// members
		Scaleform::GFx::Value& dataObj; // 0x08
		Scaleform::GFx::Value& menuObj; // 0x10
	};

	static_assert(sizeof(PipboySubMenu) == 0x18);
}
