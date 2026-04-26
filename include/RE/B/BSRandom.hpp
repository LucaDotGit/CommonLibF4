#pragma once

namespace RE::BSRandom
{
	[[nodiscard]] std::mt19937& GetGenerator();

	[[nodiscard]] bool Bool();

	[[nodiscard]] std::int32_t Int();
	[[nodiscard]] std::int32_t Int(std::int32_t a_maxInclusive);
	[[nodiscard]] std::int32_t Int(std::int32_t a_minInclusive, std::int32_t a_maxInclusive);

	[[nodiscard]] std::uint32_t UnsignedInt();
	[[nodiscard]] std::uint32_t UnsignedInt(std::uint32_t a_maxInclusive);
	[[nodiscard]] std::uint32_t UnsignedInt(std::uint32_t a_minInclusive, std::uint32_t a_maxInclusive);

	[[nodiscard]] REX::Float32 Float();
	[[nodiscard]] REX::Float32 Float(REX::Float32 a_maxExclusive);
	[[nodiscard]] REX::Float32 Float(REX::Float32 a_minInclusive, REX::Float32 a_maxExclusive);

	[[nodiscard]] REX::Float32 Float0To1();
	[[nodiscard]] REX::Float32 FloatNeg1To1();
	[[nodiscard]] REX::Float32 FloatTwoPi();
	[[nodiscard]] REX::Float32 FloatNegPiToPi();
}
