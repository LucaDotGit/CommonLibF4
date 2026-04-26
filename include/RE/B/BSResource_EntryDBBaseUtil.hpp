#pragma once

namespace RE::BSResource
{
	class EntryBase;
	class Location;

	class EntryDBBaseUtil
	{
	public:
		static bool ReleaseEntryAction(EntryBase* a_entry)
		{
			using FuncType = decltype(&EntryDBBaseUtil::ReleaseEntryAction);
			static const auto FUNC = REL::Relocation<FuncType>{ RE::ID::BSResource::EntryDBBaseUtil::ReleaseEntryAction };
			return std::invoke(FUNC, a_entry);
		}

		// members
		Location* rootLocation;				// 00
		std::uint32_t resourcePriorityBase; // 08
		bool allowDeadLoadSkipping;			// 0C
	};
	static_assert(sizeof(EntryDBBaseUtil) == 0x10);
}
