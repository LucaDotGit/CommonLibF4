#pragma once

namespace RE::BSExternalAudioIO
{
	class LipVoiceHeader
	{
	public:
		// members
		std::uint32_t magic;   // 0x00
		std::uint32_t version; // 0x04
		std::uint32_t lipSize; // 0x08
	};

	static_assert(sizeof(LipVoiceHeader) == 0x0C);
}
