#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"

namespace RE::BSExternalAudioIO
{
	class ExternalLoad
		: public BSIntrusiveRefCounted // 00
	{
	public:
		// members
		std::uint32_t bufferSize{ 0 };	 // 04
		std::uint32_t sourceSize{ 0 };	 // 08
		std::uint32_t streamOffset{ 0 }; // 0C
		std::byte* buffer{ nullptr };	 // 10
	};
	static_assert(sizeof(ExternalLoad) == 0x18);
}
