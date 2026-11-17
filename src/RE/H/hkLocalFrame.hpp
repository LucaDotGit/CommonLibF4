#pragma once

#include "RE/H/hkReferencedObject.hpp"

namespace RE
{
	class __declspec(novtable) hkLocalFrame : public hkReferencedObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::hkLocalFrame;
		inline static constexpr const auto& VTABLE = VTABLE::hkLocalFrame;

		~hkLocalFrame() override; // 0x00
	};

	static_assert(sizeof(hkLocalFrame) == 0x10);
}
