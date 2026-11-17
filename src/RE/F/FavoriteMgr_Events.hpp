#pragma once

namespace RE::FavoriteMgr_Events
{
	class ComponentFavoriteEvent
	{
	public:
		// members
		BGSComponent* component; // 0x00
		bool isFavorited;		 // 0x08
	};

	static_assert(sizeof(ComponentFavoriteEvent) == 0x10);
}
