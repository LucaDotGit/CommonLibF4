#pragma once

namespace RE::Workshop
{
	class DeletedItemInfo
	{
	public:
		// members
		TESFormID formID;	 // 0x00
		std::uint32_t count; // 0x04
	};

	static_assert(sizeof(DeletedItemInfo) == 0x08);
}
