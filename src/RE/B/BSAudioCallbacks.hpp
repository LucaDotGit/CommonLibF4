#pragma once

namespace RE
{
	class BSISoundDescriptor;

	class BSAudioCallbacks
	{
	public:
		using IDCallbackType = bool (*)(std::uint32_t, const BSISoundDescriptor**);
		using NameCallbackType = bool (*)(const char*, const BSISoundDescriptor**);
		using PostProcessCallbackType = void (*)();

		// members
		IDCallbackType* idCallback;					  // 0x00
		NameCallbackType* nameCallback;				  // 0x08
		PostProcessCallbackType* postProcessCallback; // 0x10
	};

	static_assert(sizeof(BSAudioCallbacks) == 0x18);
}
