#pragma once

#include "RE/NetImmerse/NiObject.hpp"

namespace RE
{
	struct hknpWorldCinfo;

	class bhkWorld
		: public NiObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::bhkWorld };
		inline static constexpr auto VTABLE{ VTABLE::bhkWorld };
		inline static constexpr auto Ni_RTTI{ Ni_RTTI::bhkWorld };

		// add
		virtual bool Update(std::uint32_t a_updateFlags); // 28
		virtual void Init(const hknpWorldCinfo& a_info);  // 29

		static bool RemoveObjects(NiAVObject* a_object, bool a_recurse, bool a_force)
		{
			using func_t = decltype(&RemoveObjects);
			static REL::Relocation<func_t> func{ REL::RelocationID(1514984, 2277721) };
			return func(a_object, a_recurse, a_force);
		}

		// members
		std::byte pad[0x180 - 0x10]; // 0x10 - To-Do
	};
	static_assert(sizeof(bhkWorld) == 0x180);
}
