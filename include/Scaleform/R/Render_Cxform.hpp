#pragma once

namespace Scaleform::Render
{
	class Cxform
	{
	public:
		static const Cxform IDENTITY;

		enum class Format : std::int32_t
		{
			kR = 0,
			kG = 1,
			kB = 2,
			kA = 3,

			kTotal = 4
		};

		enum class Type : std::int32_t
		{
			kMult = 0,
			kAdd = 1,

			kTotal = 2
		};

		// members
		std::array<std::array<REX::Float32, std::to_underlying(Format::kTotal)>, std::to_underlying(Type::kTotal)> data; // 00
	};
	static_assert(sizeof(Cxform) == 0x20);

	inline constexpr auto Cxform::IDENTITY = Cxform{ { { { 1.0_f32, 1.0_f32, 1.0_f32, 1.0_f32 }, { 0.0_f32, 0.0_f32, 0.0_f32, 0.0_f32 } } } };
}
