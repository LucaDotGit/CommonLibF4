#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/R/ResponseListWrapper.hpp"
#include "RE/T/TESCondition.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TOPIC_INFO_DATA.hpp"

namespace RE
{
	class __declspec(novtable) TESTopicInfo : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESTopicInfo;
		inline static constexpr const auto& VTABLE = VTABLE::TESTopicInfo;
		inline static constexpr auto FORM_TYPE = FormType::TopicInfo;

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				SaidPlayer = 1 << 30,
				SaidOnce = static_cast<std::uint32_t>(1) << 31
			};
		};

		using ChangeFlags = ChangeFlag::ChangeFlags;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				InfoGroup = 1 << 6,
				ExcludeFromExpert = 1 << 7,
				Ignored = 1 << 12,
				ActorChanged = 1 << 13
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint32_t
		{
			None,
			InfoGroup = 1 << 6
		};

		enum class CHARISMA_CHALLENGE_DIFFICULTY : std::int32_t
		{
			None = 0,
			Easy = 1,
			Medium = 2,
			Hard = 3,
			AlwaysSucceeds = 4,
			EasyRepeatable = 5,
			MediumRepeatable = 6,
			HardRepeatable = 7,

			_Count = 8
		};

		enum class CHARISMA_CHALLENGE_SUCCESS : std::int32_t
		{
			None = -1,
			Fail = 0,
			Succeed = 1,

			_Count = 3
		};

		[[nodiscard]]
		auto GetChallengeLevel() const -> CHARISMA_CHALLENGE_DIFFICULTY
		{
			using FuncType = decltype(&TESTopicInfo::GetChallengeLevel);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESTopicInfo::GetChallengeLevel);
			return std::invoke(FUNC, this);
		}

		[[nodiscard]]
		auto GetParentInfoGroup() const -> TESTopicInfo*
		{
			using FuncType = decltype(&TESTopicInfo::GetParentInfoGroup);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESTopicInfo::GetParentInfoGroup);
			return std::invoke(FUNC, this);
		}

		[[nodiscard]]
		auto GetScene() const -> BGSScene*
		{
			using FuncType = decltype(&TESTopicInfo::GetScene);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESTopicInfo::GetScene);
			return std::invoke(FUNC, this);
		}

		[[nodiscard]]
		auto GetSpeaker() const -> TESActorBase*
		{
			using FuncType = decltype(&TESTopicInfo::GetSpeaker);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESTopicInfo::GetSpeaker);
			return std::invoke(FUNC, this);
		}

		[[nodiscard]]
		auto GetSuccessLevel() const -> CHARISMA_CHALLENGE_SUCCESS
		{
			using FuncType = decltype(&TESTopicInfo::GetSuccessLevel);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESTopicInfo::GetSuccessLevel);
			return std::invoke(FUNC, this);
		}

		void StartScene(TESObjectREFR* a_ref)
		{
			using FuncType = decltype(&TESTopicInfo::StartScene);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESTopicInfo::StartScene);
			std::invoke(FUNC, this, a_ref);
		}

		auto StartSceneOnEnd(ObjectRefHandle a_ref) -> BGSScene*
		{
			using FuncType = decltype(&TESTopicInfo::StartSceneOnEnd);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESTopicInfo::StartSceneOnEnd);
			return std::invoke(FUNC, this, a_ref);
		}

		// members
		TESTopic* parentTopic;		   // 0x20
		TESGlobal* resetGlobal;		   // 0x28
		TESTopicInfo* dataInfo;		   // 0x30
		TESCondition objConditions;	   // 0x38
		std::uint16_t infoIndex;	   // 0x40
		std::int8_t subtitlePriority;  // 0x42
		bool saidOnce;				   // 0x43
		TOPIC_INFO_DATA data;		   // 0x44
		ResponseListWrapper responses; // 0x48
	};

	static_assert(sizeof(TESTopicInfo) == 0x50);
}
