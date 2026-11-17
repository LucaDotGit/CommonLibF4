#pragma once

#include "RE/N/NiObject.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BSMultiBoundShape;

	class __declspec(novtable) BSMultiBound : public NiObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSMultiBound;
		inline static constexpr const auto& VTABLE = VTABLE::BSMultiBound;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::BSMultiBound;

		// members
		std::uint32_t boundFrameCount;		// 0x10
		NiPointer<BSMultiBoundShape> shape; // 0x18
	};

	static_assert(sizeof(BSMultiBound) == 0x20);
}
