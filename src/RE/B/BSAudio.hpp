#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSResource_ID.hpp"
#include "RE/B/BSString.hpp"

namespace RE::BSAudioMonitor
{
	class Receiver;
}

namespace RE
{
	class BSAudioListener;
	class BSGameSound;
	class BSIReverbType;

	class __declspec(novtable) BSAudio
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSAudio;
		inline static constexpr const auto& VTABLE = VTABLE::BSAudio;

		virtual ~BSAudio(); // 0x00

		// add
		virtual auto Init() -> bool;													// 0x01
		virtual void Shutdown();														// 0x02
		virtual auto GetGameSound(const BSResource::ID& a_ressourceID) -> BSGameSound*; // 0x03
		virtual void ReleaseGameSound(BSGameSound* a_gameSound);						// 0x04
		virtual auto GetSystemName() -> const BSFixedString&;							// 0x05
		virtual void ApplyReverbType(
			std::uint8_t a_reverbIndex,
			const BSIReverbType* a_reverbType,
			std::chrono::milliseconds a_transitionTime);										// 0x06
		virtual void SetSpeedOfSound(REX::Float32 a_speed);										// 0x07
		virtual void PostGameSoundUpdates();													// 0x08
		virtual auto CreateMonitor(REX::Float32 a_volume) -> std::uint32_t;						// 0x09
		virtual void ReleaseMonitor(std::uint32_t a_monitorID);									// 0x0A
		virtual auto GetReceiver(std::uint32_t a_monitorID) -> const BSAudioMonitor::Receiver*; // 0x0B
		virtual void GetDeviceInfo(BSString& a_deviceInfo);										// 0x0C

		[[nodiscard]]
		static auto GetSoundDescriptor(TESFormID a_formID) -> BGSSoundDescriptorForm*;
		[[nodiscard]]
		static auto GetSoundDescriptor(const char* a_formEditorId) -> BGSSoundDescriptorForm*;
		[[nodiscard]]
		static auto GetUIOutputModel() -> const BGSSoundOutput*;

		// members
		BSAudioListener* listener{nullptr}; // 0x08
		std::uint32_t outputChannels{0};	// 0x10
		bool initialized{true};				// 0x14
	};

	static_assert(sizeof(BSAudio) == 0x18);
}
