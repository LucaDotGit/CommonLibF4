#include "RE/B/BSTPoint.hpp"

namespace RE
{
	template class BSTPoint2<std::int8_t>;
	static_assert(sizeof(BSTPoint2<std::int8_t>) == 0x02);

	template class BSTPoint2<std::uint8_t>;
	static_assert(sizeof(BSTPoint2<std::uint8_t>) == 0x02);

	template class BSTPoint2<std::int16_t>;
	static_assert(sizeof(BSTPoint2<std::int16_t>) == 0x04);

	template class BSTPoint2<std::uint16_t>;
	static_assert(sizeof(BSTPoint2<std::uint16_t>) == 0x04);

	template class BSTPoint2<std::int32_t>;
	static_assert(sizeof(BSTPoint2<std::int32_t>) == 0x08);

	template class BSTPoint2<std::uint32_t>;
	static_assert(sizeof(BSTPoint2<std::uint32_t>) == 0x08);

	template class BSTPoint2<REX::Float32>;
	static_assert(sizeof(BSTPoint2<REX::Float32>) == 0x08);

	template class BSTPoint2<REX::Float64>;
	static_assert(sizeof(BSTPoint2<REX::Float64>) == 0x10);

	template class BSTPoint2Base<std::int8_t>;
	static_assert(sizeof(BSTPoint2Base<std::int8_t>) == 0x02);

	template class BSTPoint2Base<std::uint8_t>;
	static_assert(sizeof(BSTPoint2Base<std::uint8_t>) == 0x02);

	template class BSTPoint2Base<std::int16_t>;
	static_assert(sizeof(BSTPoint2Base<std::int16_t>) == 0x04);

	template class BSTPoint2Base<std::uint16_t>;
	static_assert(sizeof(BSTPoint2Base<std::uint16_t>) == 0x04);

	template class BSTPoint2Base<std::int32_t>;
	static_assert(sizeof(BSTPoint2Base<std::int32_t>) == 0x08);

	template class BSTPoint2Base<std::uint32_t>;
	static_assert(sizeof(BSTPoint2Base<std::uint32_t>) == 0x08);

	template class BSTPoint2Base<REX::Float32>;
	static_assert(sizeof(BSTPoint2Base<REX::Float32>) == 0x08);

	template class BSTPoint2Base<REX::Float64>;
	static_assert(sizeof(BSTPoint2Base<REX::Float64>) == 0x10);

	template void swap(BSTPoint2Base<std::int8_t>&, BSTPoint2Base<std::int8_t>&) noexcept;
	template void swap(BSTPoint2Base<std::uint8_t>&, BSTPoint2Base<std::uint8_t>&) noexcept;
	template void swap(BSTPoint2Base<std::int16_t>&, BSTPoint2Base<std::int16_t>&) noexcept;
	template void swap(BSTPoint2Base<std::uint16_t>&, BSTPoint2Base<std::uint16_t>&) noexcept;
	template void swap(BSTPoint2Base<std::int32_t>&, BSTPoint2Base<std::int32_t>&) noexcept;
	template void swap(BSTPoint2Base<std::uint32_t>&, BSTPoint2Base<std::uint32_t>&) noexcept;
	template void swap(BSTPoint2Base<REX::Float32>&, BSTPoint2Base<REX::Float32>&) noexcept;
	template void swap(BSTPoint2Base<REX::Float64>&, BSTPoint2Base<REX::Float64>&) noexcept;

	template class BSTPoint3<std::int8_t>;
	static_assert(sizeof(BSTPoint3<std::int8_t>) == 0x03);

	template class BSTPoint3<std::uint8_t>;
	static_assert(sizeof(BSTPoint3<std::uint8_t>) == 0x03);

	template class BSTPoint3<std::int16_t>;
	static_assert(sizeof(BSTPoint3<std::int16_t>) == 0x06);

	template class BSTPoint3<std::uint16_t>;
	static_assert(sizeof(BSTPoint3<std::uint16_t>) == 0x06);

	template class BSTPoint3<std::int32_t>;
	static_assert(sizeof(BSTPoint3<std::int32_t>) == 0x0C);

	template class BSTPoint3<std::uint32_t>;
	static_assert(sizeof(BSTPoint3<std::uint32_t>) == 0x0C);

	template class BSTPoint3<REX::Float32>;
	static_assert(sizeof(BSTPoint3<REX::Float32>) == 0x0C);

	template class BSTPoint3<REX::Float64>;
	static_assert(sizeof(BSTPoint3<REX::Float64>) == 0x18);

	template class BSTPoint3Base<std::int8_t>;
	static_assert(sizeof(BSTPoint3Base<std::int8_t>) == 0x03);

	template class BSTPoint3Base<std::uint8_t>;
	static_assert(sizeof(BSTPoint3Base<std::uint8_t>) == 0x03);

	template class BSTPoint3Base<std::int16_t>;
	static_assert(sizeof(BSTPoint3Base<std::int16_t>) == 0x06);

	template class BSTPoint3Base<std::uint16_t>;
	static_assert(sizeof(BSTPoint3Base<std::uint16_t>) == 0x06);

	template class BSTPoint3Base<std::int32_t>;
	static_assert(sizeof(BSTPoint3Base<std::int32_t>) == 0x0C);

	template class BSTPoint3Base<std::uint32_t>;
	static_assert(sizeof(BSTPoint3Base<std::uint32_t>) == 0x0C);

	template class BSTPoint3Base<REX::Float32>;
	static_assert(sizeof(BSTPoint3Base<REX::Float32>) == 0x0C);

	template class BSTPoint3Base<REX::Float64>;
	static_assert(sizeof(BSTPoint3Base<REX::Float64>) == 0x18);

	template void swap(BSTPoint3Base<std::int8_t>&, BSTPoint3Base<std::int8_t>&) noexcept;
	template void swap(BSTPoint3Base<std::uint8_t>&, BSTPoint3Base<std::uint8_t>&) noexcept;
	template void swap(BSTPoint3Base<std::int16_t>&, BSTPoint3Base<std::int16_t>&) noexcept;
	template void swap(BSTPoint3Base<std::uint16_t>&, BSTPoint3Base<std::uint16_t>&) noexcept;
	template void swap(BSTPoint3Base<std::int32_t>&, BSTPoint3Base<std::int32_t>&) noexcept;
	template void swap(BSTPoint3Base<std::uint32_t>&, BSTPoint3Base<std::uint32_t>&) noexcept;
	template void swap(BSTPoint3Base<REX::Float32>&, BSTPoint3Base<REX::Float32>&) noexcept;
	template void swap(BSTPoint3Base<REX::Float64>&, BSTPoint3Base<REX::Float64>&) noexcept;

	template class BSTPointDefaultOps<std::int8_t>;
	static_assert(std::is_empty_v<BSTPointDefaultOps<std::int8_t>>);

	template class BSTPointDefaultOps<std::uint8_t>;
	static_assert(std::is_empty_v<BSTPointDefaultOps<std::uint8_t>>);

	template class BSTPointDefaultOps<std::int16_t>;
	static_assert(std::is_empty_v<BSTPointDefaultOps<std::int16_t>>);

	template class BSTPointDefaultOps<std::uint16_t>;
	static_assert(std::is_empty_v<BSTPointDefaultOps<std::uint16_t>>);

	template class BSTPointDefaultOps<std::int32_t>;
	static_assert(std::is_empty_v<BSTPointDefaultOps<std::int32_t>>);

	template class BSTPointDefaultOps<std::uint32_t>;
	static_assert(std::is_empty_v<BSTPointDefaultOps<std::uint32_t>>);

	template class BSTPointDefaultOps<REX::Float32>;
	static_assert(std::is_empty_v<BSTPointDefaultOps<REX::Float32>>);

	template class BSTPointDefaultOps<REX::Float64>;
	static_assert(std::is_empty_v<BSTPointDefaultOps<REX::Float64>>);
}

#if __cpp_lib_format > 0l
namespace std
{
	template struct formatter<RE::BSTPoint2<std::int8_t>>;
	template struct formatter<RE::BSTPoint2<std::uint8_t>>;
	template struct formatter<RE::BSTPoint2<std::int16_t>>;
	template struct formatter<RE::BSTPoint2<std::uint16_t>>;
	template struct formatter<RE::BSTPoint2<std::int32_t>>;
	template struct formatter<RE::BSTPoint2<std::uint32_t>>;
	template struct formatter<RE::BSTPoint2<REX::Float32>>;
	template struct formatter<RE::BSTPoint2<REX::Float64>>;

	template struct formatter<RE::BSTPoint3<std::int8_t>>;
	template struct formatter<RE::BSTPoint3<std::uint8_t>>;
	template struct formatter<RE::BSTPoint3<std::int16_t>>;
	template struct formatter<RE::BSTPoint3<std::uint16_t>>;
	template struct formatter<RE::BSTPoint3<std::int32_t>>;
	template struct formatter<RE::BSTPoint3<std::uint32_t>>;
	template struct formatter<RE::BSTPoint3<REX::Float32>>;
	template struct formatter<RE::BSTPoint3<REX::Float64>>;
}
#endif

#if FMT_VERSION > 0l
namespace fmt
{
	template struct formatter<RE::BSTPoint2<std::int8_t>>;
	template struct formatter<RE::BSTPoint2<std::uint8_t>>;
	template struct formatter<RE::BSTPoint2<std::int16_t>>;
	template struct formatter<RE::BSTPoint2<std::uint16_t>>;
	template struct formatter<RE::BSTPoint2<std::int32_t>>;
	template struct formatter<RE::BSTPoint2<std::uint32_t>>;
	template struct formatter<RE::BSTPoint2<REX::Float32>>;
	template struct formatter<RE::BSTPoint2<REX::Float64>>;

	template struct formatter<RE::BSTPoint3<std::int8_t>>;
	template struct formatter<RE::BSTPoint3<std::uint8_t>>;
	template struct formatter<RE::BSTPoint3<std::int16_t>>;
	template struct formatter<RE::BSTPoint3<std::uint16_t>>;
	template struct formatter<RE::BSTPoint3<std::int32_t>>;
	template struct formatter<RE::BSTPoint3<std::uint32_t>>;
	template struct formatter<RE::BSTPoint3<REX::Float32>>;
	template struct formatter<RE::BSTPoint3<REX::Float64>>;
}
#endif
