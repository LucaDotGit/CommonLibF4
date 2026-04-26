#pragma once

#include "RE/B/BSTSingleton.hpp"

namespace RE
{
	class Calendar
		: public BSTSingletonSDM<Calendar> // 00
	{
	public:
		using Milliseconds = std::chrono::duration<REX::Float32, std::chrono::milliseconds::period>;
		using Seconds = std::chrono::duration<REX::Float32, std::chrono::seconds::period>;
		using Minutes = std::chrono::duration<REX::Float32, std::chrono::minutes::period>;
		using Hours = std::chrono::duration<REX::Float32, std::chrono::hours::period>;
		using Days = std::chrono::duration<REX::Float32, std::chrono::days::period>;
		using Weeks = std::chrono::duration<REX::Float32, std::chrono::weeks::period>;
		using Months = std::chrono::duration<REX::Float32, std::chrono::months::period>;
		using Years = std::chrono::duration<REX::Float32, std::chrono::years::period>;

		using DayOfWeek = std::chrono::weekday;
		using DayOfMonth = std::chrono::month_day;
		using MonthOfYear = std::chrono::year_month;

		using Day = std::chrono::day;
		using Month = std::chrono::month;
		using Year = std::chrono::year;

		using YearMonthDay = std::chrono::year_month_day;
		using LocalDays = std::chrono::local_days;
		using TimePoint = std::chrono::time_point<std::chrono::local_t, Hours>;

		inline static constexpr auto DEFAULT_GAME_MILLISECOND = Milliseconds(0);
		inline static constexpr auto DEFAULT_GAME_SECOND = Seconds(0);
		inline static constexpr auto DEFAULT_GAME_MINUTE = Minutes(0);
		inline static constexpr auto DEFAULT_GAME_HOUR = Hours(11);
		inline static constexpr auto DEFAULT_GAME_DAY = Day(23);
		inline static constexpr auto DEFAULT_GAME_MONTH = Month(std::chrono::October);
		inline static constexpr auto DEFAULT_GAME_YEAR = Year(2287);
		inline static constexpr auto DEFAULT_GAME_WEEKDAY = DayOfWeek(DEFAULT_GAME_YEAR / DEFAULT_GAME_MONTH / DEFAULT_GAME_DAY);
		inline static constexpr auto DEFAULT_TIME_SCALE = Seconds(20);
		inline static constexpr auto DEFAULT_GAME_DAYS_PASSED = Days(1);
		inline static constexpr auto DEFAULT_GAME_HOURS_PASSED = std::chrono::duration_cast<Hours>(DEFAULT_GAME_DAYS_PASSED);

		inline static constexpr auto DAY_SETTING_KEYS = std::array{
			"sDaySunday"sv,
			"sDayMonday"sv,
			"sDayTuesday"sv,
			"sDayWednesday"sv,
			"sDayThursday"sv,
			"sDayFriday"sv,
			"sDaySaturday"sv
		};

		inline static constexpr auto MONTH_SETTING_KEYS = std::array{
			"sMonthJanuary"sv,
			"sMonthFebruary"sv,
			"sMonthMarch"sv,
			"sMonthApril"sv,
			"sMonthMay"sv,
			"sMonthJune"sv,
			"sMonthJuly"sv,
			"sMonthAugust"sv,
			"sMonthSeptember"sv,
			"sMonthOctober"sv,
			"sMonthNovember"sv,
			"sMonthDecember"sv
		};

		inline static constexpr auto DAYS = std::array{
			std::chrono::Sunday,
			std::chrono::Monday,
			std::chrono::Tuesday,
			std::chrono::Wednesday,
			std::chrono::Thursday,
			std::chrono::Friday,
			std::chrono::Saturday
		};

		inline static constexpr auto MONTHS = std::array{
			std::chrono::January,
			std::chrono::February,
			std::chrono::March,
			std::chrono::April,
			std::chrono::May,
			std::chrono::June,
			std::chrono::July,
			std::chrono::August,
			std::chrono::September,
			std::chrono::October,
			std::chrono::November,
			std::chrono::December
		};

		[[nodiscard]] static Calendar* GetSingleton();

		[[nodiscard]] static auto GetAllDayNames() -> std::span<const std::string_view, DAY_SETTING_KEYS.size()>;
		[[nodiscard]] static auto GetAllMonthNames() -> std::span<const std::string_view, MONTH_SETTING_KEYS.size()>;

		[[nodiscard]] static std::string_view GetNameOfDay(DayOfWeek a_dayOfWeek);
		[[nodiscard]] static std::string_view GetNameOfMonth(Month a_month);

		[[nodiscard]] static DayOfWeek GetDayOfWeek(Year a_year, Month a_month, Day a_day) noexcept;
		[[nodiscard]] static DayOfWeek GetDayOfWeek_NoLeapYear(Month a_month, Day a_day) noexcept;
		[[nodiscard]] static DayOfMonth GetDayOfMonth(Month a_month, Day a_day) noexcept;
		[[nodiscard]] static MonthOfYear GetMonthOfYear(Year a_year, Month a_month) noexcept;

		[[nodiscard]] Milliseconds GetMillisecond() const noexcept;
		[[nodiscard]] Seconds GetSecond() const noexcept;
		[[nodiscard]] Minutes GetMinute() const noexcept;
		[[nodiscard]] Hours GetHour() const noexcept;
		[[nodiscard]] Day GetDay() const noexcept;
		[[nodiscard]] Month GetMonth() const noexcept;
		[[nodiscard]] Year GetYear() const noexcept;
		[[nodiscard]] TimePoint GetTimePoint() const noexcept;

		[[nodiscard]] DayOfWeek GetWeekDay() const noexcept;
		[[nodiscard]] DayOfMonth GetMonthDay() const noexcept;
		[[nodiscard]] MonthOfYear GetYearMonth() const noexcept;

		[[nodiscard]] Seconds GetTimeScale() const noexcept;
		[[nodiscard]] Days GetMidnightsPassed() const noexcept;
		[[nodiscard]] Hours GetHoursPassed() const noexcept;
		[[nodiscard]] Days GetDaysPassed() const noexcept;

		[[nodiscard]] std::string_view GetDayName() const;
		[[nodiscard]] std::string_view GetMonthName() const;

		// members
		TESGlobal* gameYear;		   // 08
		TESGlobal* gameMonth;		   // 10
		TESGlobal* gameDay;			   // 18
		TESGlobal* gameHour;		   // 20
		TESGlobal* gameDaysPassed;	   // 28
		TESGlobal* timeScale;		   // 30
		std::uint32_t midnightsPassed; // 38
		REX::Float32 rawDaysPassed;	   // 3C
	};
	static_assert(sizeof(Calendar) == 0x40);
}
