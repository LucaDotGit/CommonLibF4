#pragma once

#include "RE/B/BGSLocalizedString.hpp"
#include "RE/B/BGSTypedKeywordValue.hpp"

namespace RE
{
	class TESResponse
	{
	public:
		class RespData
		{
		public:
			std::uint16_t percent;
			std::uint8_t responseID;
			bool useEmotion;
		};
		static_assert(sizeof(RespData) == 0x04);

		[[nodiscard]] const char* GetResponseText()
		{
			using FuncType = decltype(&TESResponse::GetResponseText);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESResponse::GetResponseText };
			return std::invoke(FUNC, this);
		}

		[[nodiscard]] TESIdleForm* GetSpeakerIdle()
		{
			using FuncType = decltype(&TESResponse::GetSpeakerIdle);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESResponse::GetSpeakerIdle };
			return std::invoke(FUNC, this);
		}

		// members
		BGSLocalizedString responseText;
		TESResponse* pNext;
		RespData data;
		BGSTypedKeywordValue<KeywordType::kAnimFaceArchetype> faceArcheType;
	};
	static_assert(sizeof(TESResponse) == 0x18);
}
