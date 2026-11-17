#pragma once

namespace RE
{
	class OBJ_LAND
	{
	public:
		enum class Flags : std::uint32_t
		{
			None = 0,
			HeightAltered = 1 << 0,
			CLRAltered = 1 << 1,
			TexAltered = 1 << 2,
			Loaded = 1 << 3,
			GoodNormals = 1 << 4,
			HiResHeightfield = 1 << 5,

			Remapped = 1 << 10,

			DataAltered = HeightAltered | CLRAltered | TexAltered | HiResHeightfield
		};

		// members
		REX::EnumSet<Flags, std::uint32_t> flags; // 0x00
	};

	static_assert(sizeof(OBJ_LAND) == 0x04);
}
