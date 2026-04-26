#pragma once

namespace RE
{
	class BSTimer
	{
	public:
		using Milliseconds = std::chrono::duration<std::int64_t, std::chrono::milliseconds::period>;
		using Seconds = std::chrono::duration<REX::Float32, std::chrono::seconds::period>;

		inline static constexpr auto MAX_DELTA_TIME = Seconds(1.0_f32 / 6.0_f32);

#define RUNTIME_DATA_CONTENT                     \
	std::uint64_t firstTime;			/* 30 */ \
	std::uint64_t disabledLastTime;		/* 38 */ \
	std::uint64_t disabledFirstTime;	/* 40 */ \
	std::uint32_t disableCounter;		/* 48 */ \
	bool useGlobalTimeMultiplierTarget; /* 4C */

		class RuntimeData
		{
		public:
			// members
			RUNTIME_DATA_CONTENT;
		};

		[[nodiscard]] static BSTimer* GetSingleton();

		[[nodiscard]] RuntimeData& GetRuntimeData() noexcept;
		[[nodiscard]] const RuntimeData& GetRuntimeData() const noexcept;

		[[nodiscard]] static REX::Float32& QGlobalTimeMultiplier();
		[[nodiscard]] static REX::Float32& QGlobalTimeMultiplierTarget();

		[[nodiscard]] static Seconds GetGlobalTimeMultiplier();
		[[nodiscard]] static Seconds GetGlobalTimeMultiplierTarget();

		void SetGlobalTimeMultiplier(REX::Float32 a_mult, bool a_now);

		[[nodiscard]] Milliseconds GetInitTime() const noexcept;

		[[nodiscard]] Seconds GetDeltaTime() const noexcept;
		[[nodiscard]] Seconds GetRealTimeDeltaTime() const noexcept;

		[[nodiscard]] Milliseconds GetLastTime() const noexcept;
		[[nodiscard]] Milliseconds GetFirstTime() const noexcept;
		[[nodiscard]] Milliseconds GetDisabledLastTime() const noexcept;
		[[nodiscard]] Milliseconds GetDisabledFirstTime() const noexcept;

		// members
		std::int64_t highPrecisionInitTime; // 00
		REX::Float32 clamp;					// 08
		REX::Float32 clampRemainder;		// 0C
		REX::Float32 delta;					// 10
		REX::Float32 realTimeDelta;			// 14
		std::uint64_t lastTime;				// 18
#if COMMONLIB_RUNTIME_AE == 0
		RUNTIME_DATA_CONTENT; // 20
#elif COMMONLIB_RUNTIME_VR == 0 && COMMONLIB_RUNTIME_OG == 0 && COMMONLIB_RUNTIME_NG == 0
		std::array<std::byte, 0x10> unk20; // 20
		RUNTIME_DATA_CONTENT;			   // 30
#endif
	};
#if COMMONLIB_RUNTIME_AE == 0
	static_assert(sizeof(BSTimer) == 0x40);
	static_assert(offsetof(BSTimer, firstTime) == 0x20);
#elif COMMONLIB_RUNTIME_VR == 0 && COMMONLIB_RUNTIME_OG == 0 && COMMONLIB_RUNTIME_NG == 0
	static_assert(sizeof(BSTimer) == 0x50);
	static_assert(offsetof(BSTimer, firstTime) == 0x30);
#else
	static_assert(sizeof(BSTimer) == 0x20);
#endif
}

#undef RUNTIME_DATA_CONTENT
