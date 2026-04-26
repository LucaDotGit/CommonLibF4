#include "RE/B/BSPointerHandleSmartPointer.hpp"

namespace RE
{
	template class BSPointerHandleSmartPointer<BSPointerHandleManagerInterface<Actor>>;
	static_assert(sizeof(BSPointerHandleSmartPointer<BSPointerHandleManagerInterface<Actor>>) == 0x08);

	template class BSPointerHandleSmartPointer<BSPointerHandleManagerInterface<Projectile>>;
	static_assert(sizeof(BSPointerHandleSmartPointer<BSPointerHandleManagerInterface<Projectile>>) == 0x08);

	template class BSPointerHandleSmartPointer<BSPointerHandleManagerInterface<TESObjectREFR>>;
	static_assert(sizeof(BSPointerHandleSmartPointer<BSPointerHandleManagerInterface<TESObjectREFR>>) == 0x08);
}
