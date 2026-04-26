#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	template <class T>
	class BSPointerHandleSmartPointer
		: public NiPointer<typename T::value_type> // 00
	{
	public:
	};

	extern template class BSPointerHandleSmartPointer<BSPointerHandleManagerInterface<Actor>>;
	extern template class BSPointerHandleSmartPointer<BSPointerHandleManagerInterface<Projectile>>;
	extern template class BSPointerHandleSmartPointer<BSPointerHandleManagerInterface<TESObjectREFR>>;

	using ActorHandlePtr = BSPointerHandleSmartPointer<BSPointerHandleManagerInterface<Actor>>;
	using ProjectileHandlePtr = BSPointerHandleSmartPointer<BSPointerHandleManagerInterface<Projectile>>;
	using ObjectRefHandlePtr = BSPointerHandleSmartPointer<BSPointerHandleManagerInterface<TESObjectREFR>>;
}
