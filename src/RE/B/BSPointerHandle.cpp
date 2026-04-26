#include "RE/B/BSPointerHandle.hpp"

#include "RE/A/Actor.hpp"
#include "RE/B/BSCRC32.hpp"
#include "RE/P/Projectile.hpp"
#include "RE/T/TESObjectREFR.hpp"

namespace RE
{
	template class BSPointerHandle<Actor>;
	static_assert(sizeof(BSPointerHandle<Actor>) == 0x04);

	template class BSPointerHandle<Projectile>;
	static_assert(sizeof(BSPointerHandle<Projectile>) == 0x04);

	template class BSPointerHandle<TESObjectREFR>;
	static_assert(sizeof(BSPointerHandle<TESObjectREFR>) == 0x04);

	template bool operator== <Actor>(const BSPointerHandle<Actor>&, const BSPointerHandle<Actor>&) noexcept;
	template bool operator== <Actor>(const BSPointerHandle<Actor>&, std::nullptr_t) noexcept;
	template bool operator== <Actor>(std::nullptr_t, const BSPointerHandle<Actor>&) noexcept;
	template bool operator== <Actor>(const BSPointerHandle<Actor>&, const NiPointer<Actor>&) noexcept;
	template bool operator== <Actor>(const NiPointer<Actor>&, const BSPointerHandle<Actor>&) noexcept;
	template bool operator== <Actor>(const BSPointerHandle<Actor>&, const Actor*) noexcept;
	template bool operator== <Actor>(const Actor*, const BSPointerHandle<Actor>&) noexcept;
	template auto operator<=> <Actor>(const BSPointerHandle<Actor>&, const BSPointerHandle<Actor>&) noexcept;
	template auto operator<=> <Actor>(const BSPointerHandle<Actor>&, std::nullptr_t) noexcept;
	template auto operator<=> <Actor>(std::nullptr_t, const BSPointerHandle<Actor>&) noexcept;
	template auto operator<=> <Actor>(const BSPointerHandle<Actor>&, const NiPointer<Actor>&) noexcept;
	template auto operator<=> <Actor>(const NiPointer<Actor>&, const BSPointerHandle<Actor>&) noexcept;
	template auto operator<=> <Actor>(const BSPointerHandle<Actor>&, const Actor*) noexcept;
	template auto operator<=> <Actor>(const Actor*, const BSPointerHandle<Actor>&) noexcept;

	template bool operator== <Projectile>(const BSPointerHandle<Projectile>&, const BSPointerHandle<Projectile>&) noexcept;
	template bool operator== <Projectile>(const BSPointerHandle<Projectile>&, std::nullptr_t) noexcept;
	template bool operator== <Projectile>(std::nullptr_t, const BSPointerHandle<Projectile>&) noexcept;
	template bool operator== <Projectile>(const BSPointerHandle<Projectile>&, const NiPointer<Projectile>&) noexcept;
	template bool operator== <Projectile>(const NiPointer<Projectile>&, const BSPointerHandle<Projectile>&) noexcept;
	template bool operator== <Projectile>(const BSPointerHandle<Projectile>&, const Projectile*) noexcept;
	template bool operator== <Projectile>(const Projectile*, const BSPointerHandle<Projectile>&) noexcept;
	template auto operator<=> <Projectile>(const BSPointerHandle<Projectile>&, const BSPointerHandle<Projectile>&) noexcept;
	template auto operator<=> <Projectile>(const BSPointerHandle<Projectile>&, std::nullptr_t) noexcept;
	template auto operator<=> <Projectile>(std::nullptr_t, const BSPointerHandle<Projectile>&) noexcept;
	template auto operator<=> <Projectile>(const BSPointerHandle<Projectile>&, const NiPointer<Projectile>&) noexcept;
	template auto operator<=> <Projectile>(const NiPointer<Projectile>&, const BSPointerHandle<Projectile>&) noexcept;
	template auto operator<=> <Projectile>(const BSPointerHandle<Projectile>&, const Projectile*) noexcept;
	template auto operator<=> <Projectile>(const Projectile*, const BSPointerHandle<Projectile>&) noexcept;

	template bool operator== <TESObjectREFR>(const BSPointerHandle<TESObjectREFR>&, const BSPointerHandle<TESObjectREFR>&) noexcept;
	template bool operator== <TESObjectREFR>(const BSPointerHandle<TESObjectREFR>&, std::nullptr_t) noexcept;
	template bool operator== <TESObjectREFR>(std::nullptr_t, const BSPointerHandle<TESObjectREFR>&) noexcept;
	template bool operator== <TESObjectREFR>(const BSPointerHandle<TESObjectREFR>&, const NiPointer<TESObjectREFR>&) noexcept;
	template bool operator== <TESObjectREFR>(const NiPointer<TESObjectREFR>&, const BSPointerHandle<TESObjectREFR>&) noexcept;
	template bool operator== <TESObjectREFR>(const BSPointerHandle<TESObjectREFR>&, const TESObjectREFR*) noexcept;
	template bool operator== <TESObjectREFR>(const TESObjectREFR*, const BSPointerHandle<TESObjectREFR>&) noexcept;
	template auto operator<=> <TESObjectREFR>(const BSPointerHandle<TESObjectREFR>&, const BSPointerHandle<TESObjectREFR>&) noexcept;
	template auto operator<=> <TESObjectREFR>(const BSPointerHandle<TESObjectREFR>&, std::nullptr_t) noexcept;
	template auto operator<=> <TESObjectREFR>(std::nullptr_t, const BSPointerHandle<TESObjectREFR>&) noexcept;
	template auto operator<=> <TESObjectREFR>(const BSPointerHandle<TESObjectREFR>&, const NiPointer<TESObjectREFR>&) noexcept;
	template auto operator<=> <TESObjectREFR>(const NiPointer<TESObjectREFR>&, const BSPointerHandle<TESObjectREFR>&) noexcept;
	template auto operator<=> <TESObjectREFR>(const BSPointerHandle<TESObjectREFR>&, const TESObjectREFR*) noexcept;
	template auto operator<=> <TESObjectREFR>(const TESObjectREFR*, const BSPointerHandle<TESObjectREFR>&) noexcept;

	template void swap<Actor>(BSPointerHandle<Actor>&, BSPointerHandle<Actor>&) noexcept;
	template void swap<Projectile>(BSPointerHandle<Projectile>&, BSPointerHandle<Projectile>&) noexcept;
	template void swap<TESObjectREFR>(BSPointerHandle<TESObjectREFR>&, BSPointerHandle<TESObjectREFR>&) noexcept;

	template class BSPointerHandleManagerInterface<Actor>;
	static_assert(std::is_empty_v<BSPointerHandleManagerInterface<Actor>>);

	template class BSPointerHandleManagerInterface<Projectile>;
	static_assert(std::is_empty_v<BSPointerHandleManagerInterface<Projectile>>);

	template class BSPointerHandleManagerInterface<TESObjectREFR>;
	static_assert(std::is_empty_v<BSPointerHandleManagerInterface<TESObjectREFR>>);
}

namespace RE
{
	template struct BSCRC32<RE::BSPointerHandle<Actor>>;
	template struct BSCRC32<RE::BSPointerHandle<Projectile>>;
	template struct BSCRC32<RE::BSPointerHandle<TESObjectREFR>>;
}

namespace std
{
	template struct hash<RE::BSPointerHandle<RE::Actor>>;
	template struct hash<RE::BSPointerHandle<RE::Projectile>>;
	template struct hash<RE::BSPointerHandle<RE::TESObjectREFR>>;
}
