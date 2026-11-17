#pragma once

namespace RE
{
	class NiCamera;

	class NiUpdateData
	{
	public:
		enum class Flags : std::uint32_t; // To-Do

		// members
		REX::Float32 time;						  // 0x00
		NiCamera* camera;						  // 0x08
		REX::EnumSet<Flags, std::uint32_t> flags; // 0x10
		std::uint32_t renderObjects;			  // 0x14
		std::uint32_t fadeNodeDepth;			  // 0x18
	};

	static_assert(sizeof(NiUpdateData) == 0x20);
}
