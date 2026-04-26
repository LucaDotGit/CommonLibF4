#pragma once

#include "RE/I/IUIMessageData.hpp"

namespace Scaleform::GFx
{
	class Event;
}

namespace RE
{
	class __declspec(novtable) BSUIScaleformData
		: public IUIMessageData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSUIScaleformData };
		inline static constexpr auto VTABLE{ VTABLE::BSUIScaleformData };

		// members
		::Scaleform::GFx::Event* scaleformEvent{ nullptr }; // 18
	};
	static_assert(sizeof(BSUIScaleformData) == 0x20);
}
