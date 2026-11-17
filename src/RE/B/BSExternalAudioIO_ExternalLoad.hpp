#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"

namespace RE::BSExternalAudioIO
{
	class ExternalLoad : public BSIntrusiveRefCounted // 0x00
	{
	public:
		// members
		std::uint32_t bufferSize{0};   // 0x04
		std::uint32_t sourceSize{0};   // 0x08
		std::uint32_t streamOffset{0}; // 0x0C
		std::byte* buffer{nullptr};	   // 0x10
	};

	static_assert(sizeof(ExternalLoad) == 0x18);
}
