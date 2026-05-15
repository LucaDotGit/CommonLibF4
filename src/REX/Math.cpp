#include "REX/Math.hpp"

namespace REX::Impl
{
	[[nodiscard]] auto GetLgammaMutex() noexcept
		-> REX::NotAssignable<std::mutex>&
	{
		static constinit auto Mutex = REX::NotAssignable<std::mutex>();
		return Mutex;
	}
}

namespace REX
{
	template std::int32_t Fib(std::int32_t) noexcept;
	template std::uint32_t Fib(std::uint32_t) noexcept;
	template std::int64_t Fib(std::int64_t) noexcept;
	template std::uint64_t Fib(std::uint64_t) noexcept;

	template std::int32_t Fact(std::int32_t) noexcept;
	template std::uint32_t Fact(std::uint32_t) noexcept;
	template std::int64_t Fact(std::int64_t) noexcept;
	template std::uint64_t Fact(std::uint64_t) noexcept;

	template std::int32_t Perm(std::int32_t, std::int32_t) noexcept;
	template std::uint32_t Perm(std::uint32_t, std::uint32_t) noexcept;
	template std::int64_t Perm(std::int64_t, std::int64_t) noexcept;
	template std::uint64_t Perm(std::uint64_t, std::uint64_t) noexcept;

	template std::int32_t Comb(std::int32_t, std::int32_t) noexcept;
	template std::uint32_t Comb(std::uint32_t, std::uint32_t) noexcept;
	template std::int64_t Comb(std::int64_t, std::int64_t) noexcept;
	template std::uint64_t Comb(std::uint64_t, std::uint64_t) noexcept;

	template std::int32_t Mod(std::int32_t, std::int32_t) noexcept;
	template std::uint32_t Mod(std::uint32_t, std::uint32_t) noexcept;
	template std::int64_t Mod(std::int64_t, std::int64_t) noexcept;
	template std::uint64_t Mod(std::uint64_t, std::uint64_t) noexcept;

	template REX::Float32 Mod(REX::Float32, REX::Float32) noexcept;
	template REX::Float64 Mod(REX::Float64, REX::Float64) noexcept;
	template REX::Float128 Mod(REX::Float128, REX::Float128) noexcept;

	template REX::Float32 Round(REX::Float32, std::int32_t) noexcept;
	template REX::Float64 Round(REX::Float64, std::int32_t) noexcept;
	template REX::Float128 Round(REX::Float128, std::int32_t) noexcept;

	template REX::Float32 DegToRad(REX::Float32) noexcept;
	template REX::Float64 DegToRad(REX::Float64) noexcept;
	template REX::Float128 DegToRad(REX::Float128) noexcept;

	template REX::Float32 RadToDeg(REX::Float32) noexcept;
	template REX::Float64 RadToDeg(REX::Float64) noexcept;
	template REX::Float128 RadToDeg(REX::Float128) noexcept;

	template REX::Float32 ClampDeg(REX::Float32) noexcept;
	template REX::Float64 ClampDeg(REX::Float64) noexcept;
	template REX::Float128 ClampDeg(REX::Float128) noexcept;

	template bool NearEq(REX::Float32, REX::Float32, REX::Float32) noexcept;
	template bool NearEq(REX::Float64, REX::Float64, REX::Float64) noexcept;
	template bool NearEq(REX::Float128, REX::Float128, REX::Float128) noexcept;

	template bool CloseEq(REX::Float32, REX::Float32, REX::Float32) noexcept;
	template bool CloseEq(REX::Float64, REX::Float64, REX::Float64) noexcept;
	template bool CloseEq(REX::Float128, REX::Float128, REX::Float128) noexcept;

	template bool FuzzyGt(REX::Float32, REX::Float32, REX::Float32) noexcept;
	template bool FuzzyGt(REX::Float64, REX::Float64, REX::Float64) noexcept;
	template bool FuzzyGt(REX::Float128, REX::Float128, REX::Float128) noexcept;

	template bool FuzzyLt(REX::Float32, REX::Float32, REX::Float32) noexcept;
	template bool FuzzyLt(REX::Float64, REX::Float64, REX::Float64) noexcept;
	template bool FuzzyLt(REX::Float128, REX::Float128, REX::Float128) noexcept;

	template std::pair<std::uint32_t, std::int32_t> SplitFromX64(std::int64_t) noexcept;
	template std::int64_t CombineToX64(std::uint32_t, std::int32_t) noexcept;

	template std::pair<std::uint32_t, std::int32_t> SplitFromX64(std::uint64_t) noexcept;
	template std::uint64_t CombineToX64(std::uint32_t, std::int32_t) noexcept;

	template std::pair<std::uint32_t, std::int32_t> SplitFromX64(REX::Float64) noexcept;
	template REX::Float64 CombineToX64(std::uint32_t, std::int32_t) noexcept;

	static_assert(SplitFromX64(0x1122334455667788i64) == std::make_pair(0x55667788i32, 0x11223344i32));
	static_assert(CombineToX64<std::int64_t>(0x55667788i32, 0x11223344i32) == 0x1122334455667788i64);

	static_assert(SplitFromX64(0x1122334455667788ui64) == std::make_pair(0x55667788i32, 0x11223344i32));
	static_assert(CombineToX64<std::uint64_t>(0x55667788i32, 0x11223344i32) == 0x1122334455667788ui64);
}
