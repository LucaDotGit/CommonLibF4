#pragma once

namespace RE::BSExternalAudioIO
{
	class LipVoiceHeader
	{
	public:
		// members
		std::uint32_t magic;   // 00
		std::uint32_t version; // 04
		std::uint32_t lipSize; // 08
	};
	static_assert(sizeof(LipVoiceHeader) == 0x0C);
}
