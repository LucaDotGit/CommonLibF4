#pragma once

namespace RE
{
	class hknpContactSolverType
	{
	public:
		enum class Enum : std::int32_t
		{
			Stream = 0,
			MX = 1,

			_Count = 2
		};
	};

	static_assert(std::is_empty_v<hknpContactSolverType>);
}
