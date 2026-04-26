#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/R/ResponseListWrapper.hpp"
#include "RE/T/TESCondition.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TOPIC_INFO_DATA.hpp"

namespace RE
{
	class __declspec(novtable) TESTopicInfo
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESTopicInfo };
		inline static constexpr auto VTABLE{ VTABLE::TESTopicInfo };
		inline static constexpr auto FORM_TYPE{ FormType::kTopicInfo };

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				kSaidPlayer = 1 << 30,
				kSaidOnce = 1ui32 << 31
			};
		};
		using ChangeFlags = ChangeFlag::ChangeFlags;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kInfoGroup = 1 << 6,
				kExcludeFromExpert = 1 << 7,
				kIgnored = 1 << 12,
				kActorChanged = 1 << 13
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint32_t
		{
			kNone,
			kInfoGroup = 1 << 6
		};

		enum class CHARISMA_CHALLENGE_DIFFICULTY : std::int32_t
		{
			kNone = 0,
			kEasy = 1,
			kMedium = 2,
			kHard = 3,
			kAlwaysSucceeds = 4,
			kEasyRepeatable = 5,
			kMediumRepeatable = 6,
			kHardRepeatable = 7,

			kTotal = 8
		};

		enum class CHARISMA_CHALLENGE_SUCCESS : std::int32_t
		{
			kNone = -1,
			kFail = 0,
			kSucceed = 1,

			kTotal = 3
		};

		[[nodiscard]] CHARISMA_CHALLENGE_DIFFICULTY GetChallengeLevel() const
		{
			using FuncType = decltype(&TESTopicInfo::GetChallengeLevel);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESTopicInfo::GetChallengeLevel };
			return std::invoke(FUNC, this);
		}

		[[nodiscard]] TESTopicInfo* GetParentInfoGroup() const
		{
			using FuncType = decltype(&TESTopicInfo::GetParentInfoGroup);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESTopicInfo::GetParentInfoGroup };
			return std::invoke(FUNC, this);
		}

		[[nodiscard]] BGSScene* GetScene() const
		{
			using FuncType = decltype(&TESTopicInfo::GetScene);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESTopicInfo::GetScene };
			return std::invoke(FUNC, this);
		}

		[[nodiscard]] TESActorBase* GetSpeaker() const
		{
			using FuncType = decltype(&TESTopicInfo::GetSpeaker);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESTopicInfo::GetSpeaker };
			return std::invoke(FUNC, this);
		}

		[[nodiscard]] CHARISMA_CHALLENGE_SUCCESS GetSuccessLevel() const
		{
			using FuncType = decltype(&TESTopicInfo::GetSuccessLevel);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESTopicInfo::GetSuccessLevel };
			return std::invoke(FUNC, this);
		}

		void StartScene(TESObjectREFR* a_ref)
		{
			using FuncType = decltype(&TESTopicInfo::StartScene);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESTopicInfo::StartScene };
			FUNC(this, a_ref);
		}

		BGSScene* StartSceneOnEnd(ObjectRefHandle a_ref)
		{
			using FuncType = decltype(&TESTopicInfo::StartSceneOnEnd);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESTopicInfo::StartSceneOnEnd };
			return std::invoke(FUNC, this, a_ref);
		}

		// members
		TESTopic* parentTopic;		   // 20
		TESGlobal* resetGlobal;		   // 28
		TESTopicInfo* dataInfo;		   // 30
		TESCondition objConditions;	   // 38
		std::uint16_t infoIndex;	   // 40
		std::int8_t subtitlePriority;  // 42
		bool saidOnce;				   // 43
		TOPIC_INFO_DATA data;		   // 44
		ResponseListWrapper responses; // 48
	};
	static_assert(sizeof(TESTopicInfo) == 0x50);
}
