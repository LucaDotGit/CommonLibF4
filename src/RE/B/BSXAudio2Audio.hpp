#pragma once

#include "RE/B/BSAudio.hpp"

namespace RE
{
	class __declspec(novtable) BSXAudio2Audio : public BSAudio // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSXAudio2Audio;
		inline static constexpr const auto& VTABLE = VTABLE::BSXAudio2Audio;

		~BSXAudio2Audio() override; // 0x00

		[[nodiscard]]
		static auto GetSingleton() noexcept -> BSXAudio2Audio*
		{
			static const auto SINGLETON = REL::Relocation<BSXAudio2Audio**>(ID::BSXAudio2Audio::Singleton);
			return *SINGLETON;
		}

		// members
		REX::W32::X3DAUDIO_HANDLE x3DHandle; // 0x18
	};

	static_assert(sizeof(BSXAudio2Audio) == 0x30);
}
