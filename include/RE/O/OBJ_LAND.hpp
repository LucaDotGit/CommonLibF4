#pragma once

namespace RE
{
	class OBJ_LAND
	{
	public:
		enum class Flags : std::uint32_t
		{
			kNone = 0,
			kHeightAltered = 1 << 0,
			kCLRAltered = 1 << 1,
			kTexAltered = 1 << 2,
			kLoaded = 1 << 3,
			kGoodNormals = 1 << 4,
			kHiResHeightfield = 1 << 5,

			kRemapped = 1 << 10,

			kDataAltered = kHeightAltered | kCLRAltered | kTexAltered | kHiResHeightfield
		};

		// members
		REX::EnumSet<Flags, std::uint32_t> flags; // 00
	};
	static_assert(sizeof(OBJ_LAND) == 0x04);
}
