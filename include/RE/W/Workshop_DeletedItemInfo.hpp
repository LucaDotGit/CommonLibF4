#pragma once

namespace RE::Workshop
{
	class DeletedItemInfo
	{
	public:
		// members
		TESFormID formID;	 // 00
		std::uint32_t count; // 04
	};
	static_assert(sizeof(DeletedItemInfo) == 0x08);
}
