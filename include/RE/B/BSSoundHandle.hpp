#pragma once

namespace RE
{
	class BSISoundOutputModel;

	class BSSoundHandle
	{
	public:
		enum class ASSUMED_STATE : std::int32_t
		{
			kInitialized = 0,
			kPlaying = 1,
			kStopped = 2,
			kPaused = 3
		};

		enum class LOOP_TYPE : std::int32_t
		{
			kNone = 0,
			kWholeFile = 1,
			kEnvFast = 2,
			kEnvSlow = 3
		};

		constexpr BSSoundHandle() noexcept = default;
		constexpr ~BSSoundHandle() noexcept = default;

		constexpr BSSoundHandle(const BSSoundHandle&) noexcept = default;
		constexpr BSSoundHandle(BSSoundHandle&&) noexcept = default;

		constexpr BSSoundHandle& operator=(const BSSoundHandle&) noexcept = default;
		constexpr BSSoundHandle& operator=(BSSoundHandle&&) noexcept = default;

		[[nodiscard]] static BSSoundHandle& GetHolotapeSoundHandle()
		{
			static const auto HOLOTAPE_SOUND_HANDLE = REL::Relocation<BSSoundHandle*>{ ID::BSSoundHandle::HolotapeSoundHandle };
			return *HOLOTAPE_SOUND_HANDLE;
		}

		[[nodiscard]] bool IsValid() const noexcept
		{
			return soundID != std::numeric_limits<decltype(soundID)>::max();
		}

		[[nodiscard]] bool IsPlaying() const noexcept
		{
			return state == ASSUMED_STATE ::kPlaying;
		}

		[[nodiscard]] bool IsPaused() const noexcept
		{
			return state == ASSUMED_STATE ::kPaused;
		}

		[[nodiscard]] bool IsStopped() const noexcept
		{
			return state == ASSUMED_STATE ::kStopped;
		}

		bool Play()
		{
			using FuncType = decltype(&BSSoundHandle::Play);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BSSoundHandle::Play };
			return std::invoke(FUNC, this);
		}

		bool PlayAfter(std::int64_t a_delayMillis)
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

		bool Stop()
		{
			using FuncType = decltype(&BSSoundHandle::Stop);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BSSoundHandle::Stop };
			return std::invoke(FUNC, this);
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

		bool SetOutputModel(const BSISoundOutputModel* a_outputModel)
		{
			using FuncType = decltype(&BSSoundHandle::SetOutputModel);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BSSoundHandle::SetOutputModel };
			return std::invoke(FUNC, this, a_outputModel);
		}

		// members
		std::uint32_t soundID{ 0 };					 // 00
		bool assumeSuccess{ false };				 // 04
		REX::Enum<ASSUMED_STATE, std::int8_t> state; // 05
	};
	static_assert(sizeof(BSSoundHandle) == 0x08);
}
