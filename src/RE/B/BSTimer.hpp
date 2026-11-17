#pragma once

namespace RE
{
	class BSTimer
	{
	public:
		using Milliseconds = std::chrono::duration<std::int64_t, std::chrono::milliseconds::period>;
		using Seconds = std::chrono::duration<REX::Float32, std::chrono::seconds::period>;

		inline static constexpr auto MAX_DELTA_TIME =
			Seconds(static_cast<REX::Float32>(1.0) / static_cast<REX::Float32>(6.0));
		inline static constexpr auto DEFAULT_TIME_MULTIPLIER = static_cast<REX::Float32>(1.0);

#define RUNTIME_DATA_CONTENT                     \
	Milliseconds firstTime;				/* 00 */ \
	Milliseconds disabledLastTime;		/* 08 */ \
	Milliseconds disabledFirstTime;		/* 10 */ \
	std::uint32_t disableCounter;		/* 18 */ \
	bool useGlobalTimeMultiplierTarget; /* 1C */

		class RuntimeData
		{
		public:
			// members
			RUNTIME_DATA_CONTENT; // 0x00
		};

		static_assert(sizeof(RuntimeData) == 0x20);

		[[nodiscard]]
		static auto GetSingleton() noexcept -> BSTimer*;

		[[nodiscard]]
		auto GetRuntimeData() noexcept -> RuntimeData&;
		[[nodiscard]]
		auto GetRuntimeData() const noexcept -> const RuntimeData&;

		[[nodiscard]]
		static auto GetGlobalTimeMultiplier() noexcept -> REX::Float32&;
		[[nodiscard]]
		static auto GetGlobalTimeMultiplierTarget() noexcept -> REX::Float32&;

		void SetGlobalTimeMultiplier(REX::Float32 a_timeMult, bool a_now = false);

		// members
		Milliseconds highPrecisionInitTime; // 0x00
		REX::Float32 clamp;					// 0x08
		REX::Float32 clampRemainder;		// 0x0C
		Seconds delta;						// 0x10
		Seconds realTimeDelta;				// 0x14
		Milliseconds lastTime;				// 0x18
#if (COMMONLIB_RUNTIME_AE == 0)
		RUNTIME_DATA_CONTENT; // 0x20
#elif (COMMONLIB_RUNTIME_VR == 0 && COMMONLIB_RUNTIME_OG == 0 && COMMONLIB_RUNTIME_NG == 0)
		std::array<std::byte, 0x10> unk20; // 0x20
		RUNTIME_DATA_CONTENT;			   // 0x30
#endif
	};

#if (COMMONLIB_RUNTIME_AE == 0)
	static_assert(sizeof(BSTimer) == 0x40);
#elif (COMMONLIB_RUNTIME_VR == 0 && COMMONLIB_RUNTIME_OG == 0 && COMMONLIB_RUNTIME_NG == 0)
	static_assert(sizeof(BSTimer) == 0x50);
#else
	static_assert(sizeof(BSTimer) == 0x20);
#endif
}

#undef RUNTIME_DATA_CONTENT
