#pragma once

namespace RE::LoadingStatusChanged
{
	class Event
	{
	public:
		// members
		bool isLoading; // 0x00
	};

	static_assert(sizeof(Event) == 0x01);
}
