#pragma once

namespace RE
{
	class NiPoint3;
	class BSISoundCategory;
	class BSISoundOutputModel;

	class BSSoundHandle
	{
	public:
		using value_type = std::uint32_t;

		using Milliseconds = std::chrono::duration<std::uint64_t, std::milli>;
		using ShortMilliseconds = std::chrono::duration<std::uint16_t, std::milli>;

		enum class ASSUMED_STATE : std::int8_t
		{
			Initialized = 0,
			Playing = 1,
			Stopped = 2,
			Paused = 3
		};

		constexpr BSSoundHandle() noexcept = default;
		constexpr ~BSSoundHandle() noexcept = default;

		constexpr BSSoundHandle(value_type a_soundID) :
			_soundID(a_soundID)
		{
		}

		constexpr BSSoundHandle(const BSSoundHandle&) noexcept = default;
		constexpr BSSoundHandle(BSSoundHandle&&) noexcept = default;

		constexpr auto operator=(const BSSoundHandle&) noexcept -> BSSoundHandle& = default;
		constexpr auto operator=(BSSoundHandle&&) noexcept -> BSSoundHandle& = default;

		[[nodiscard]]
		constexpr auto operator==(const BSSoundHandle& a_rhs) const noexcept -> bool
		{
			return _soundID == a_rhs._soundID;
		}

		[[nodiscard]]
		constexpr auto operator<=>(const BSSoundHandle& a_rhs) const noexcept -> auto
		{
			return _soundID <=> a_rhs._soundID;
		}

		[[nodiscard]]
		auto IsValid() const noexcept -> bool
		{
			return _soundID != std::numeric_limits<decltype(_soundID)>::max();
		}

		[[nodiscard]]
		auto IsInitialized() const noexcept -> bool
		{
			return _state == ASSUMED_STATE::Initialized;
		}

		[[nodiscard]]
		auto IsPlaying() const noexcept -> bool
		{
			return _state == ASSUMED_STATE::Playing;
		}

		[[nodiscard]]
		auto IsPaused() const noexcept -> bool
		{
			return _state == ASSUMED_STATE::Paused;
		}

		[[nodiscard]]
		auto IsStopped() const noexcept -> bool
		{
			return _state == ASSUMED_STATE::Stopped;
		}

		[[nodiscard]]
		auto GetSoundID() const noexcept -> value_type
		{
			return _soundID;
		}

		[[nodiscard]]
		auto GetAssumeSuccess() const noexcept -> bool
		{
			return _assumeSuccess;
		}

		[[nodiscard]]
		auto GetState() const noexcept -> ASSUMED_STATE
		{
			return _state.get();
		}

		[[nodiscard]]
		static auto GetHolotapeSoundHandle() noexcept -> BSSoundHandle&
		{
			static const auto HOLOTAPE_SOUND_HANDLE =
				REL::Relocation<BSSoundHandle*>{ID::BSSoundHandle::HolotapeSoundHandle};
			return *HOLOTAPE_SOUND_HANDLE;
		}

		void ClearFollowedObject() const
		{
			using FuncType = decltype(&BSSoundHandle::ClearFollowedObject);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSSoundHandle::ClearFollowedObject);
			std::invoke(FUNC, this);
		}

		auto FadeInPlay(ShortMilliseconds a_delayMillis) const -> bool
		{
			using FuncType = decltype(&BSSoundHandle::FadeInPlay);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSSoundHandle::FadeInPlay);
			return std::invoke(FUNC, this, a_delayMillis);
		}

		auto FadeOutAndRelease(ShortMilliseconds a_delayMillis) const -> bool
		{
			using FuncType = decltype(&BSSoundHandle::FadeOutAndRelease);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSSoundHandle::FadeOutAndRelease);
			return std::invoke(FUNC, this, a_delayMillis);
		}

		[[nodiscard]]
		auto GetDuration() const -> Milliseconds
		{
			using FuncType = decltype(&BSSoundHandle::GetDuration);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSSoundHandle::GetDuration);
			return std::invoke(FUNC, this);
		}

		[[nodiscard]]
		auto GetVolume() const -> REX::Float32
		{
			using FuncType = decltype(&BSSoundHandle::GetVolume);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSSoundHandle::GetVolume);
			return std::invoke(FUNC, this);
		}

		auto FadeTo(std::uint16_t a_targetAttenuation, ShortMilliseconds a_milliseconds) const -> bool
		{
			using FuncType = decltype(&BSSoundHandle::FadeTo);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSSoundHandle::FadeTo);
			return std::invoke(FUNC, this, a_targetAttenuation, a_milliseconds);
		}

		[[nodiscard]]
		auto IsEnvelopeLoop() const -> bool
		{
			using FuncType = decltype(&BSSoundHandle::IsEnvelopeLoop);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSSoundHandle::IsEnvelopeLoop);
			return std::invoke(FUNC, this);
		}

		[[nodiscard]]
		auto IsReady() const -> bool
		{
			using FuncType = decltype(&BSSoundHandle::IsReady);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSSoundHandle::IsReady);
			return std::invoke(FUNC, this);
		}

		auto Pause() const -> bool
		{
			using FuncType = decltype(&BSSoundHandle::Pause);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSSoundHandle::Pause);
			return std::invoke(FUNC, this);
		}

		auto Play() const -> bool
		{
			using FuncType = decltype(&BSSoundHandle::Play);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSSoundHandle::Play);
			return std::invoke(FUNC, this);
		}

		auto PlayAfter(Milliseconds a_delayMillis) const -> bool
		{
			using FuncType = decltype(&BSSoundHandle::PlayAfter);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSSoundHandle::PlayAfter);
			return std::invoke(FUNC, this, a_delayMillis);
		}

		auto Release(bool a_immediate) const -> bool
		{
			using FuncType = decltype(&BSSoundHandle::Release);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSSoundHandle::Release);
			return std::invoke(FUNC, this, a_immediate);
		}

		auto SetOutputModel(const BSISoundOutputModel* a_outputModel) const -> bool
		{
			using FuncType = decltype(&BSSoundHandle::SetOutputModel);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSSoundHandle::SetOutputModel);
			return std::invoke(FUNC, this, a_outputModel);
		}

		auto SetPosition(const NiPoint3& a_position) const -> bool
		{
			using FuncType = decltype(&BSSoundHandle::SetPosition);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSSoundHandle::SetPosition);
			return std::invoke(FUNC, this, a_position);
		}

		auto SetSoundCategory(const BSISoundCategory* a_category, std::uint16_t a_transitionOver) const -> bool
		{
			using FuncType = decltype(&BSSoundHandle::SetSoundCategory);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSSoundHandle::SetSoundCategory);
			return std::invoke(FUNC, this, a_category, a_transitionOver);
		}

		auto SetStaticAttenuation(std::uint16_t a_attenuation) const -> bool
		{
			using FuncType = decltype(&BSSoundHandle::SetStaticAttenuation);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSSoundHandle::SetStaticAttenuation);
			return std::invoke(FUNC, this, a_attenuation);
		}

		auto SetVolume(REX::Float32 a_volume) const -> bool
		{
			using FuncType = decltype(&BSSoundHandle::SetVolume);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSSoundHandle::SetVolume);
			return std::invoke(FUNC, this, a_volume);
		}

		auto Stop() const -> bool
		{
			using FuncType = decltype(&BSSoundHandle::Stop);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSSoundHandle::Stop);
			return std::invoke(FUNC, this);
		}

	private:
		// members
		value_type _soundID{std::numeric_limits<value_type>::max()};			  // 0x00
		bool _assumeSuccess{false};												  // 0x04
		REX::Enum<ASSUMED_STATE, std::int8_t> _state{ASSUMED_STATE::Initialized}; // 0x05
	};

	static_assert(sizeof(BSSoundHandle) == 0x08);
}
