#pragma once

#include "RE/R/ReverbSendData.hpp"

namespace RE
{
#if (__clang__ == 1)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"
#endif

#if (_MSC_VER > 0l)
#pragma warning(push)
#pragma warning(disable : 4'265)
#endif

	// NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor)
	class __declspec(novtable) BSXAudio2Graph : public REX::W32::IXAudio2EngineCallback // 0x000
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::__BSXAudio2Graph;
		inline static constexpr const auto& VTABLE = VTABLE::__BSXAudio2Graph;

		// override(REX::W32::IXAudio2EngineCallback)
		void OnProcessingPassStart() noexcept override = 0;					   // 0x00
		void OnProcessingPassEnd() noexcept override = 0;					   // 0x01
		void OnCriticalError(REX::W32::HRESULT a_error) noexcept override = 0; // 0x02

		[[nodiscard]]
		static auto GetSingleton() noexcept -> BSXAudio2Graph*
		{
			static const auto SINGLETON = REL::Relocation<BSXAudio2Graph**>(ID::BSXAudio2Graph::Singleton);
			return *SINGLETON;
		}

		// members
		REX::W32::IXAudio27* instance{nullptr};						// 0x008
		REX::W32::IXAudio27MasteringVoice* masteringVoice{nullptr}; // 0x010
		std::array<ReverbSendData, 2> reverbSendArray;				// 0x018
		std::uint32_t masterChannelMask{0};							// 0x128
		std::uint32_t outputChannels{0};							// 0x12C
		bool reverbInitialized{false};								// 0x130
		bool valid{false};											// 0x131
		bool canMonitor{false};										// 0x132
	};

	static_assert(sizeof(BSXAudio2Graph) == 0x138);

#if (_MSC_VER > 0l)
#pragma warning(pop)
#endif

#if (__clang__ == 1)
#pragma clang diagnostic pop
#endif
}
