#pragma once

#include "RE/B/BSAudioListener.hpp"

namespace RE
{
	class __declspec(novtable) BSXAudio2AudioListener : public BSAudioListener // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSXAudio2AudioListener;
		inline static constexpr const auto& VTABLE = VTABLE::BSXAudio2AudioListener;

		~BSXAudio2AudioListener() override; // 0x00

		// members
		REX::W32::X3DAUDIO_LISTENER x3DListener; // 0x48
	};
}
