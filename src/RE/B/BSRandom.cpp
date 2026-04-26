#include "RE/B/BSRandom.hpp"

namespace RE::BSRandom
{
	std::mt19937& GetGenerator()
	{
		static const auto GENERATOR = REL::Relocation<std::mt19937*>{ ID::BSRandom::Generator };
		return *GENERATOR;
	}

	bool Bool()
	{
		auto distributor = std::uniform_int_distribution(0ui32, 1ui32);
		return static_cast<bool>(distributor(GetGenerator()));
	}

	std::int32_t Int()
	{
		auto distributor = std::uniform_int_distribution(0i32, std::numeric_limits<std::int32_t>::max());
		return distributor(GetGenerator());
	}

	std::int32_t Int(std::int32_t a_maxInclusive)
	{
		auto distributor = std::uniform_int_distribution(0i32, a_maxInclusive);
		return distributor(GetGenerator());
	}

	std::int32_t Int(std::int32_t a_min, std::int32_t a_maxInclusive)
	{
		auto distributor = std::uniform_int_distribution(a_min, a_maxInclusive);
		return distributor(GetGenerator());
	}

	std::uint32_t UnsignedInt()
	{
		auto distributor = std::uniform_int_distribution(0ui32, std::numeric_limits<std::uint32_t>::max());
		return distributor(GetGenerator());
	}

	std::uint32_t UnsignedInt(std::uint32_t a_maxInclusive)
	{
		auto distributor = std::uniform_int_distribution(0ui32, a_maxInclusive);
		return distributor(GetGenerator());
	}

	std::uint32_t UnsignedInt(std::uint32_t a_min, std::uint32_t a_maxInclusive)
	{
		auto distributor = std::uniform_int_distribution(a_min, a_maxInclusive);
		return distributor(GetGenerator());
	}

	REX::Float32 Float()
	{
		auto distributor = std::uniform_real_distribution(0.0_f32, std::numeric_limits<REX::Float32>::max());
		return distributor(GetGenerator());
	}

	REX::Float32 Float(REX::Float32 a_maxExclusive)
	{
		auto distributor = std::uniform_real_distribution(0.0_f32, a_maxExclusive);
		return distributor(GetGenerator());
	}

	REX::Float32 Float(REX::Float32 a_min, REX::Float32 a_maxExclusive)
	{
		auto distributor = std::uniform_real_distribution(a_min, a_maxExclusive);
		return distributor(GetGenerator());
	}

	REX::Float32 Float0To1()
	{
		auto distributor = std::uniform_real_distribution(0.0_f32, 1.0_f32);
		return distributor(GetGenerator());
	}

	REX::Float32 FloatNeg1To1()
	{
		auto distributor = std::uniform_real_distribution(-1.0_f32, 1.0_f32);
		return distributor(GetGenerator());
	}

	REX::Float32 FloatTwoPi()
	{
		auto distributor = std::uniform_real_distribution(0.0_f32, REX::TAU<REX::Float32>);
		return distributor(GetGenerator());
	}

	REX::Float32 FloatNegPiToPi()
	{
		auto distributor = std::uniform_real_distribution(-std::numbers::pi_v<REX::Float32>, std::numbers::pi_v<REX::Float32>);
		return distributor(GetGenerator());
	}
}
