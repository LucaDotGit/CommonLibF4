#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	template <class T>
	using BSPointerHandleSmartPointer = NiPointer<typename T::value_type>;

	using ActorHandlePtr = BSPointerHandleSmartPointer<BSPointerHandleManagerInterface<Actor>>;
	static_assert(sizeof(ActorHandlePtr) == 0x08);

	using ProjectileHandlePtr = BSPointerHandleSmartPointer<BSPointerHandleManagerInterface<Projectile>>;
	static_assert(sizeof(ProjectileHandlePtr) == 0x08);

	using ObjectRefHandlePtr = BSPointerHandleSmartPointer<BSPointerHandleManagerInterface<TESObjectREFR>>;
	static_assert(sizeof(ObjectRefHandlePtr) == 0x08);
}
