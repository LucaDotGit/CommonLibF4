#pragma once

#include "RE/B/BSTEvent.hpp"
#include "Scaleform/G/GFx_Value.hpp"

namespace RE
{
	class PipboyValueChangedEvent;

	class __declspec(novtable) PipboySubMenu
		: public BSTEventSink<PipboyValueChangedEvent> // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PipboySubMenu };
		inline static constexpr auto VTABLE{ VTABLE::PipboySubMenu };

		PipboySubMenu(::Scaleform::GFx::Value& a_dataObj, ::Scaleform::GFx::Value& a_menuObj)
			: dataObj(a_dataObj),
			  menuObj(a_menuObj)
		{
			REL::EmplaceVtable(this);
		}

		~PipboySubMenu() override; // 00

		// override (BSTEventSink<PipboyValueChangedEvent>)
		BSEventNotifyControl ProcessEvent(const PipboyValueChangedEvent& a_event, BSTEventSource<PipboyValueChangedEvent>* a_eventSource) override; // 01

		// add
		virtual void UpdateData() = 0; // 02

		// members
		::Scaleform::GFx::Value& dataObj; // 08
		::Scaleform::GFx::Value& menuObj; // 10
	};
	static_assert(sizeof(PipboySubMenu) == 0x18);
}
