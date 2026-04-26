#pragma once

namespace RE
{
	class NiCamera;

	class NiUpdateData
	{
	public:
		enum class Flags : std::uint32_t; // TODO

		// members
		REX::Float32 time;						  // 00
		NiCamera* camera;						  // 08
		REX::EnumSet<Flags, std::uint32_t> flags; // 10
		std::uint32_t renderObjects;			  // 14
		std::uint32_t fadeNodeDepth;			  // 18
	};
	static_assert(sizeof(NiUpdateData) == 0x20);
}
