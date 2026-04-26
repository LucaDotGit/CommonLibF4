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
		IDCallbackType* idCallback;					  // 00
		NameCallbackType* nameCallback;				  // 08
		PostProcessCallbackType* postProcessCallback; // 10
	};
	static_assert(sizeof(BSAudioCallbacks) == 0x18);
}
