#pragma once

namespace RE
{
	class hknpContactSolverType
	{
	public:
		enum class Enum : std::int32_t
		{
			kStream = 0,
			kMX = 1,

			kTotal = 2
		};
	};
	static_assert(std::is_empty_v<hknpContactSolverType>);
}
