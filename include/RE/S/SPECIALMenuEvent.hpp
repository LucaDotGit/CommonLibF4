#pragma once

namespace RE::SPECIALMenuEvent
{
	class NameChangedEvent
	{
	public:
		// members
		const char* fullName; // 00
		bool committed;		  // 08
	};
	static_assert(sizeof(NameChangedEvent) == 0x10);
}
