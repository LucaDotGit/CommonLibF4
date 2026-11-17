#pragma once

#include "RE/N/NiPointer.hpp"

namespace RE
{
	class NiNode;
	class Sky;

	class __declspec(novtable) SkyObject
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::SkyObject;
		inline static constexpr const auto& VTABLE = VTABLE::SkyObject;

		virtual ~SkyObject(); // 0x00

		// add
		virtual auto GetRoot() -> NiNode*;						 // 0x01
		virtual void Update(Sky* a_arg01, REX::Float32 a_arg02); // 0x02

		// members
		NiPointer<NiNode> root; // 0x08
	};

	static_assert(sizeof(SkyObject) == 0x10);
}
