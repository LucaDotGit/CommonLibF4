#pragma once

namespace RE::BooksRead
{
	class Event
	{
	public:
		// members
		TESObjectBOOK* book;
		bool advancedActorValue;
		bool addedPerk;
	};
	static_assert(sizeof(Event) == 0x10);
}
