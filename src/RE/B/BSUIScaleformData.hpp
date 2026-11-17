#pragma once

#include "RE/I/IUIMessageData.hpp"

namespace Scaleform::GFx
{
	class Event;
}

namespace RE
{
	class __declspec(novtable) BSUIScaleformData : public IUIMessageData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSUIScaleformData;
		inline static constexpr const auto& VTABLE = VTABLE::BSUIScaleformData;

		BSUIScaleformData(BSFixedString a_menuName, UI_MESSAGE_TYPE a_type) :
			IUIMessageData(std::move(a_menuName), a_type)
		{
			REL::EmplaceVtable(this);
		}

		~BSUIScaleformData() override = default; // 0x00

		// members
		Scaleform::GFx::Event* scaleformEvent{nullptr}; // 0x18
	};

	static_assert(sizeof(BSUIScaleformData) == 0x20);
}
