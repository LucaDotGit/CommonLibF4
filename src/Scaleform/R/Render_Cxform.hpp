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

			_Count = 4
		};

		enum class Type : std::int32_t
		{
			Mult = 0,
			Add = 1,

			_Count = 2
		};

		// members
		std::array<std::array<REX::Float32, std::to_underlying(Format::_Count)>, std::to_underlying(Type::_Count)>
			data; // 0x00
	};

	static_assert(sizeof(Cxform) == 0x20);

	inline constexpr auto Cxform::IDENTITY = Cxform{
		{{{static_cast<REX::Float32>(1.0),
		   static_cast<REX::Float32>(1.0),
		   static_cast<REX::Float32>(1.0),
		   static_cast<REX::Float32>(1.0)},
		  {static_cast<REX::Float32>(0.0),
		   static_cast<REX::Float32>(0.0),
		   static_cast<REX::Float32>(0.0),
		   static_cast<REX::Float32>(0.0)}}}
	};
}
