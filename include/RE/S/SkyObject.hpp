#pragma once

#include "RE/N/NiPointer.hpp"

namespace RE
{
	class NiNode;
	class Sky;

	class __declspec(novtable) SkyObject
	{
	public:
		inline static constexpr auto RTTI{ RTTI::SkyObject };
		inline static constexpr auto VTABLE{ VTABLE::SkyObject };

		virtual ~SkyObject(); // 00

		// add
		virtual NiNode* GetRoot();								 // 01
		virtual void Update(Sky* a_arg01, REX::Float32 a_arg02); // 02

		// members
		NiPointer<NiNode> root; // 08
	};
	static_assert(sizeof(SkyObject) == 0x10);
}
