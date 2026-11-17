#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTSingleton.hpp"

namespace RE
{
	class Calendar : public BSTSingletonSDM<Calendar> // 0x00
	{
	public:
		using Milliseconds = std::chrono::duration<REX::Float32, std::chrono::milliseconds::period>;
		using Seconds = std::chrono::duration<REX::Float32, std::chrono::seconds::period>;
		using Minutes = std::chrono::duration<REX::Float32, std::chrono::minutes::period>;
		using Hours = std::chrono::duration<REX::Float32, std::chrono::hours::period>;
		using Days = std::chrono::duration<REX::Float32, std::chrono::days::period>;
		using TimePoint = std::chrono::time_point<std::chrono::local_t, Milliseconds>;

		class SubHourData
		{
		public:
			Hours hour;
			Minutes minute;
			Seconds second;
			Milliseconds millisecond;
		};

		inline static constexpr auto DEFAULT_GAME_YEAR = std::chrono::year(2'287);
		inline static constexpr auto DEFAULT_GAME_MONTH = std::chrono::month(std::chrono::October);
		inline static constexpr auto DEFAULT_GAME_DAY = std::chrono::day(23);
		inline static constexpr auto DEFAULT_GAME_HOUR = Hours(11);
		inline static constexpr auto DEFAULT_GAME_MINUTE = Minutes(0);
		inline static constexpr auto DEFAULT_GAME_SECOND = Seconds(0);
		inline static constexpr auto DEFAULT_GAME_MILLISECOND = Milliseconds(0);

		inline static constexpr auto DEFAULT_GAME_SUB_HOUR = SubHourData{
			.hour = DEFAULT_GAME_HOUR,
			.minute = DEFAULT_GAME_MINUTE,
			.second = DEFAULT_GAME_SECOND,
			.millisecond = DEFAULT_GAME_MILLISECOND
		};

		inline static constexpr auto DEFAULT_ELAPSED_GAME_DAYS = Days(1);
		inline static constexpr auto DEFAULT_ELAPSED_GAME_HOURS =
			std::chrono::duration_cast<Hours>(DEFAULT_ELAPSED_GAME_DAYS);

		inline static constexpr auto DEFAULT_TIME_SCALE = Seconds(20);

		inline static constexpr auto DEFAULT_ELAPSED_MIDNIGHTS = static_cast<std::uint32_t>(0);
		inline static constexpr auto DEFAULT_ELAPSED_RAW_DAYS = Days(0);

		inline static constexpr auto DEFAULT_GAME_DATE_TIME = REX::DateTime(
			DEFAULT_GAME_YEAR,
			DEFAULT_GAME_MONTH,
			DEFAULT_GAME_DAY,
			std::chrono::duration_cast<std::chrono::hours>(DEFAULT_GAME_HOUR),
			std::chrono::duration_cast<std::chrono::minutes>(DEFAULT_GAME_MINUTE),
			std::chrono::duration_cast<std::chrono::seconds>(DEFAULT_GAME_SECOND),
			std::chrono::duration_cast<std::chrono::milliseconds>(DEFAULT_GAME_MILLISECOND),
			std::chrono::microseconds::zero(),
			std::chrono::nanoseconds::zero());

		inline static constexpr auto DEFAULT_GAME_YEAR_MONTH_DAY =
			std::chrono::year_month_day(DEFAULT_GAME_YEAR / DEFAULT_GAME_MONTH / DEFAULT_GAME_DAY);

		inline static constexpr auto DEFAULT_GAME_YEAR_MONTH =
			std::chrono::year_month(DEFAULT_GAME_YEAR / DEFAULT_GAME_MONTH);

		inline static constexpr auto DEFAULT_GAME_MONTH_DAY =
			std::chrono::month_day(DEFAULT_GAME_MONTH / DEFAULT_GAME_DAY);

		inline static constexpr auto DEFAULT_GAME_WEEK_DAY =
			std::chrono::weekday(DEFAULT_GAME_YEAR / DEFAULT_GAME_MONTH / DEFAULT_GAME_DAY);

		inline static constexpr auto DEFAULT_GAME_DAY_TIME = std::chrono::hh_mm_ss<Milliseconds>(
			DEFAULT_GAME_HOUR + DEFAULT_GAME_MINUTE + DEFAULT_GAME_SECOND + DEFAULT_GAME_MILLISECOND);

		[[nodiscard]]
		static auto GetSingleton() noexcept -> Calendar*;

		[[nodiscard]]
		static auto GetAllDayNames() -> std::span<const BSFixedStringCS, REX::DateTime::WEEKDAYS.size()>;
		[[nodiscard]]
		static auto GetAllMonthNames() -> std::span<const BSFixedStringCS, REX::DateTime::MONTHS.size()>;

		[[nodiscard]]
		static auto GetNameOfDay(std::chrono::weekday a_dayOfWeek) -> BSFixedStringCS;
		[[nodiscard]]
		static auto GetNameOfMonth(std::chrono::month a_month) -> BSFixedStringCS;

		[[nodiscard]]
		static auto GetDayOfWeek(std::chrono::year a_year, std::chrono::month a_month, std::chrono::day a_day) noexcept
			-> std::chrono::weekday;
		[[nodiscard]]
		static auto GetTimeOfDay(Hours a_hours, Minutes a_minutes, Seconds a_seconds, Milliseconds a_milliseconds)
			noexcept -> std::chrono::hh_mm_ss<Milliseconds>;

		[[nodiscard]]
		auto GetYear() const noexcept -> std::chrono::year;
		auto SetYear(std::chrono::year a_year) const noexcept -> bool;

		[[nodiscard]]
		auto GetMonth() const noexcept -> std::chrono::month;
		auto SetMonth(std::chrono::month a_month) const noexcept -> bool;

		[[nodiscard]]
		auto GetDay() const noexcept -> std::chrono::day;
		auto SetDay(std::chrono::day a_day) const noexcept -> bool;

		[[nodiscard]]
		auto GetHour() const noexcept -> Hours;
		auto SetHour(Hours a_hour) const noexcept -> bool;

		[[nodiscard]]
		auto GetSubHour() const noexcept -> SubHourData;
		auto SetSubHour(const SubHourData& a_subHour) const noexcept -> bool;

		[[nodiscard]]
		auto GetElapsedDays() const noexcept -> Days;
		auto SetElapsedDays(Days a_elapsedDays) const noexcept -> bool;

		[[nodiscard]]
		auto GetElapsedHours() const noexcept -> Hours;
		auto SetElapsedHours(Hours a_elapsedHours) const noexcept -> bool;

		[[nodiscard]]
		auto GetTimeScale() const noexcept -> Seconds;
		auto SetTimeScale(Seconds a_timeScale) const noexcept -> bool;

		[[nodiscard]]
		auto GetElapsedMidnights() const noexcept -> std::uint32_t;
		void SetElapsedMidnights(std::uint32_t a_elapsedMidnights) noexcept;

		[[nodiscard]]
		auto GetElapsedRawDays() const noexcept -> Days;
		void SetElapsedRawDays(Days a_elapsedRawDays) noexcept;

		[[nodiscard]]
		auto GetDateTime() const noexcept -> REX::DateTime;
		auto SetDateTime(const REX::DateTime& a_dateTime) const noexcept -> bool;

		[[nodiscard]]
		auto GetYearMonthDay() const noexcept -> std::chrono::year_month_day;
		[[nodiscard]]
		auto GetYearMonth() const noexcept -> std::chrono::year_month;
		[[nodiscard]]
		auto GetMonthDay() const noexcept -> std::chrono::month_day;
		[[nodiscard]]
		auto GetWeekDay() const noexcept -> std::chrono::weekday;
		[[nodiscard]]
		auto GetDayTime() const noexcept -> std::chrono::hh_mm_ss<Milliseconds>;

		[[nodiscard]]
		auto GetDayName() const -> BSFixedStringCS;
		[[nodiscard]]
		auto GetMonthName() const -> BSFixedStringCS;

		// members
		TESGlobal* gameYear;		   // 0x08
		TESGlobal* gameMonth;		   // 0x10
		TESGlobal* gameDay;			   // 0x18
		TESGlobal* gameHour;		   // 0x20
		TESGlobal* gameDaysPassed;	   // 0x28
		TESGlobal* timeScale;		   // 0x30
		std::uint32_t midnightsPassed; // 0x38
		Days rawDaysPassed;			   // 0x3C
	};

	static_assert(sizeof(Calendar) == 0x40);
}
