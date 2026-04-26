#pragma once

namespace RE::BGSMod
{
	class ObjectIndexData
	{
	public:
		TESFormID objectID;	   // 00
		std::uint8_t index;	   // 04
		std::uint8_t rank;	   // 05
		std::uint8_t disabled; // 06
	};
	static_assert(sizeof(ObjectIndexData) == 0x08);
}
