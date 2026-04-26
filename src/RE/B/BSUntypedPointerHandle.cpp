#include "RE/B/BSUntypedPointerHandle.hpp"

namespace RE
{
	template class BSUntypedPointerHandle<>;
	static_assert(sizeof(BSUntypedPointerHandle<>) == 0x04);

	template bool operator==(const BSUntypedPointerHandle<>&, const BSUntypedPointerHandle<>&) noexcept;
	template auto operator<=>(const BSUntypedPointerHandle<>&, const BSUntypedPointerHandle<>&) noexcept;

	template void swap(BSUntypedPointerHandle<>&, BSUntypedPointerHandle<>&) noexcept;
}

namespace std
{
	template struct hash<RE::BSUntypedPointerHandle<>>;
}
