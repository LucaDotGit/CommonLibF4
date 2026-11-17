#pragma once

namespace RE::SPECIALMenuEvent
{
	class NameChangedEvent
	{
	public:
		// members
		const char* fullName; // 0x00
		bool committed;		  // 0x08
	};

	static_assert(sizeof(NameChangedEvent) == 0x10);
}
