#include "RE/N/NiRect.hpp"

namespace RE
{

	template class NiRect<std::int32_t>;
	static_assert(sizeof(NiRect<std::int32_t>) == 0x10);

	template class NiRect<std::uint32_t>;
	static_assert(sizeof(NiRect<std::uint32_t>) == 0x10);

	template class NiRect<REX::Float32>;
	static_assert(sizeof(NiRect<REX::Float32>) == 0x10);

	template void swap<std::int32_t>(NiRect<std::int32_t>&, NiRect<std::int32_t>&) noexcept;
	template void swap<std::uint32_t>(NiRect<std::uint32_t>&, NiRect<std::uint32_t>&) noexcept;
	template void swap<REX::Float32>(NiRect<REX::Float32>&, NiRect<REX::Float32>&) noexcept;
}

#if __cpp_lib_format > 0l
namespace std
{
	template struct formatter<RE::NiRect<std::int32_t>>;
	template struct formatter<RE::NiRect<std::uint32_t>>;
	template struct formatter<RE::NiRect<REX::Float32>>;
}
#endif

#if FMT_VERSION > 0l
namespace fmt
{
	template struct formatter<RE::NiRect<std::int32_t>>;
	template struct formatter<RE::NiRect<std::uint32_t>>;
	template struct formatter<RE::NiRect<REX::Float32>>;
}
#endif
