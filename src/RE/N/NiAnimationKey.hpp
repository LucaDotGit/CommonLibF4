#pragma once

namespace RE
{
	class NiAnimationKey
	{
	public:
		enum class KeyContent : std::int32_t
		{
			Float = 0,
			Position = 1,
			Rotation = 2,
			Color = 3,
			Text = 4,
			Bool = 5,

			_Count = 6
		};

		enum class KeyType : std::int32_t
		{
			None = 0,
			Linear = 1,
			Bezier = 2,
			TCB = 3,
			Euler = 4,
			Step = 5,

			_Count = 6
		};

		// members
		REX::Float32 time; // 0x00
	};

	static_assert(sizeof(NiAnimationKey) == 0x04);
}
