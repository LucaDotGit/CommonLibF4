#pragma once

namespace RE
{
	class ReverbSendData
	{
	public:
		// members
		REX::W32::XAUDIO2FX_REVERB_I3DL2_PARAMETERS currentParams{REX::W32::XAUDIO2FX_I3DL2_PRESET_DEFAULT}; // 0x00
		REX::W32::XAUDIO2FX_REVERB_I3DL2_PARAMETERS targetParams{REX::W32::XAUDIO2FX_I3DL2_PRESET_DEFAULT};	 // 0x34
		REX::W32::IUnknown* effectAPO{nullptr};																 // 0x68
		REX::W32::IXAudio27SubmixVoice* reverbVoice{nullptr};												 // 0x70
		std::uint64_t transitionStart{0};																	 // 0x78
		std::uint64_t transitionEnd{0};																		 // 0x80
	};

	static_assert(sizeof(ReverbSendData) == 0x88);
}
