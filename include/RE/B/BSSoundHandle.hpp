#pragma once

namespace RE
{
	class NiPoint3;
	class BSISoundOutputModel;

	class BSSoundHandle
	{
	public:
		enum class ASSUMED_STATE : std::int8_t
		{
			kInitialized = 0,
			kPlaying = 1,
			kStopped = 2,
			kPaused = 3
		};

		constexpr BSSoundHandle() noexcept = default;
		constexpr ~BSSoundHandle() noexcept = default;

		constexpr BSSoundHandle(const BSSoundHandle&) noexcept = default;
		constexpr BSSoundHandle(BSSoundHandle&&) noexcept = default;

		constexpr BSSoundHandle& operator=(const BSSoundHandle&) noexcept = default;
		constexpr BSSoundHandle& operator=(BSSoundHandle&&) noexcept = default;

		[[nodiscard]] bool IsValid() const noexcept { return soundID != std::numeric_limits<decltype(soundID)>::max(); }
		[[nodiscard]] bool IsPlaying() const noexcept { return state == ASSUMED_STATE::kPlaying; }
		[[nodiscard]] bool IsPaused() const noexcept { return state == ASSUMED_STATE::kPaused; }
		[[nodiscard]] bool IsStopped() const noexcept { return state == ASSUMED_STATE::kStopped; }

		[[nodiscard]] static BSSoundHandle& GetHolotapeSoundHandle()
		{
			static const auto HOLOTAPE_SOUND_HANDLE = REL::Relocation<BSSoundHandle*>{ ID::BSSoundHandle::HolotapeSoundHandle };
			return *HOLOTAPE_SOUND_HANDLE;
		}

		void ClearFollowedObject()
		{
			using FuncType = decltype(&BSSoundHandle::ClearFollowedObject);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BSSoundHandle::ClearFollowedObject };
			std::invoke(FUNC, this);
		}

		bool FadeInPlay(std::uint16_t a_delayMillis)
		{
			using FuncType = decltype(&BSSoundHandle::FadeInPlay);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BSSoundHandle::FadeInPlay };
			return std::invoke(FUNC, this, a_delayMillis);
		}

		bool FadeOutAndRelease(std::uint16_t a_delayMillis)
		{
			using FuncType = decltype(&BSSoundHandle::FadeOutAndRelease);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BSSoundHandle::FadeOutAndRelease };
			return std::invoke(FUNC, this, a_delayMillis);
		}

		[[nodiscard]] std::uint64_t GetDuration()
		{
			using FuncType = decltype(&BSSoundHandle::GetDuration);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BSSoundHandle::GetDuration };
			return std::invoke(FUNC, this);
		}

		bool FadeTo(std::uint16_t a_targetAttenuation, std::uint16_t a_milliseconds)
		{
			using FuncType = decltype(&BSSoundHandle::FadeTo);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BSSoundHandle::FadeTo };
			return std::invoke(FUNC, this, a_targetAttenuation, a_milliseconds);
		}

		[[nodiscard]] bool IsEnvelopeLoop()
		{
			using FuncType = decltype(&BSSoundHandle::IsEnvelopeLoop);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BSSoundHandle::IsEnvelopeLoop };
			return std::invoke(FUNC, this);
		}

		bool Play()
		{
			using FuncType = decltype(&BSSoundHandle::Play);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BSSoundHandle::Play };
			return std::invoke(FUNC, this);
		}

		bool PlayAfter(std::uint64_t a_delayMillis)
		{
			using FuncType = decltype(&BSSoundHandle::PlayAfter);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BSSoundHandle::PlayAfter };
			return std::invoke(FUNC, this, a_delayMillis);
		}

		bool Pause()
		{
			using FuncType = decltype(&BSSoundHandle::Pause);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BSSoundHandle::Pause };
			return std::invoke(FUNC, this);
		}

		bool SetOutputModel(const BSISoundOutputModel* a_outputModel)
		{
			using FuncType = decltype(&BSSoundHandle::SetOutputModel);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BSSoundHandle::SetOutputModel };
			return std::invoke(FUNC, this, a_outputModel);
		}

		bool SetPosition(const NiPoint3& a_position)
		{
			using FuncType = decltype(&BSSoundHandle::SetPosition);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BSSoundHandle::SetPosition };
			return std::invoke(FUNC, this, a_position);
		}

		bool SetStaticAttenuation(std::uint16_t a_attenuation)
		{
			using FuncType = decltype(&BSSoundHandle::SetStaticAttenuation);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BSSoundHandle::SetStaticAttenuation };
			return std::invoke(FUNC, this, a_attenuation);
		}

		bool Stop()
		{
			using FuncType = decltype(&BSSoundHandle::Stop);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BSSoundHandle::Stop };
			return std::invoke(FUNC, this);
		}

		// members
		std::uint32_t soundID{ 0 };					 // 00
		bool assumeSuccess{ false };				 // 04
		REX::Enum<ASSUMED_STATE, std::int8_t> state; // 05
	};
	static_assert(sizeof(BSSoundHandle) == 0x08);
}
