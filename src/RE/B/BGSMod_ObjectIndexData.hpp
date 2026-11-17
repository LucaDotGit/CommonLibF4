#pragma once

namespace RE::BGSMod
{
	class ObjectIndexData
	{
	public:
		TESFormID objectID;	   // 0x00
		std::uint8_t index;	   // 0x04
		std::uint8_t rank;	   // 0x05
		std::uint8_t disabled; // 0x06
	};

	static_assert(sizeof(ObjectIndexData) == 0x08);
}
