#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class BSIAudioEffectChain;

	class __declspec(novtable) BSISoundOutputModel
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSISoundOutputModel;
		inline static constexpr const auto& VTABLE = VTABLE::BSISoundOutputModel;

		class BSIAttenuationCharacteristics;

		virtual ~BSISoundOutputModel() = default; // 0x00

		// add
		virtual auto DoGetUsesHRTF() const -> bool = 0;		  // 0x01
		virtual auto DoGetHasSpeakerBias() const -> bool = 0; // 0x02
		virtual auto DoGetSpeakerBias(
			std::uint32_t a_sourceChannels,
			std::uint32_t a_channel,
			const std::array<REX::Float32, 8>& a_levels) const -> bool = 0;				   // 0x03
		virtual auto DoGetAttenuatesWithDistance() const -> bool = 0;					   // 0x04
		virtual auto DoGetUseDoppler() const -> bool = 0;								   // 0x05
		virtual auto DoGetUseSoSDelay() const -> bool = 0;								   // 0x06
		virtual auto DoGetAudibility(REX::Float32 a_distance) const -> bool = 0;		   // 0x07
		virtual auto DoGetSupportedInputChannels() const -> std::uint32_t = 0;			   // 0x08
		virtual auto DoGetAttenuation() const -> const BSIAttenuationCharacteristics* = 0; // 0x09
		virtual auto DoGetReverbSendLevel() const -> REX::Float32 = 0;					   // 0x0A
		virtual auto DoGetSupportsMonitor(std::uint32_t a_monitorID) const -> bool = 0;	   // 0x0B
		virtual auto DoGetStaticAttenuation() const -> std::uint16_t = 0;				   // 0x0C
		virtual auto DoGetEffectChain() const -> const BSIAudioEffectChain* = 0;		   // 0x0D
		virtual auto DoGetDebugID() const -> const char* = 0;							   // 0x0E
		virtual auto DoGetTryPlayThroughController() const -> bool = 0;					   // 0x0F

		GAME_HEAP_REDEFINE_NEW(BSISoundOutputModel);
	};

	static_assert(sizeof(BSISoundOutputModel) == 0x08);
}
