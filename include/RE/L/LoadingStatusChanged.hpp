#pragma once

namespace RE::LoadingStatusChanged
{
	class Event
	{
	public:
		// members
		bool isLoading; // 00
	};
	static_assert(sizeof(Event) == 0x01);
}
