#include "RE/C/Calendar.hpp"

#include "RE/S/Setting.hpp"
#include "RE/S/SettingUtil.hpp"
#include "RE/T/TESGlobal.hpp"

namespace RE
{
	Calendar* Calendar::GetSingleton()
	{
		static const auto SINGLETON = REL::Relocation<Calendar**>{ ID::Calendar::Singleton };
		return *SINGLETON;
	}

	auto Calendar::GetAllDayNames() -> std::span<const std::string_view, DAY_SETTING_KEYS.size()>
	{
		static const auto ALL_DAY_NAMES = []() {
			auto result = std::array<std::string_view, DAY_SETTING_KEYS.size()>();
			for (auto i = static_cast<std::size_t>(0); i < DAY_SETTING_KEYS.size(); i++) {
				const auto* daySetting = GetGameSetting(DAY_SETTING_KEYS[i]);
				if (!daySetting || !daySetting->IsString()) [[unlikely]] {
					REX::Assert(false);
					continue;
				}

				result[i] = daySetting->GetString();
			}

			return result;
		}();

		return ALL_DAY_NAMES;
	}

	auto Calendar::GetAllMonthNames() -> std::span<const std::string_view, MONTH_SETTING_KEYS.size()>
	{
		static const auto ALL_MONTH_NAMES = []() {
			auto result = std::array<std::string_view, MONTH_SETTING_KEYS.size()>();
			for (auto i = static_cast<std::size_t>(0); i < MONTH_SETTING_KEYS.size(); i++) {
				const auto* monthSetting = GetGameSetting(MONTH_SETTING_KEYS[i]);
				if (!monthSetting || !monthSetting->IsString()) [[unlikely]] {
					REX::Assert(false);
					continue;
				}

				result[i] = monthSetting->GetString();
			}

			return result;
		}();

		return ALL_MONTH_NAMES;
	}

	std::string_view Calendar::GetNameOfDay(DayOfWeek a_dayOfWeek)
	{
		const auto dayIndex = static_cast<std::uint32_t>(a_dayOfWeek.c_encoding());
		if (dayIndex >= DAY_SETTING_KEYS.size()) {
			return {};
		}

		return GetAllDayNames()[dayIndex];
	}

	std::string_view Calendar::GetNameOfMonth(Month a_month)
	{
		const auto monthIndex = static_cast<std::uint32_t>(a_month) - 1;
		if (monthIndex >= MONTH_SETTING_KEYS.size()) {
			return {};
		}

		return GetAllMonthNames()[monthIndex];
	}

	Calendar::DayOfWeek Calendar::GetDayOfWeek(Year a_year, Month a_month, Day a_day) noexcept
	{
		const auto date = a_year / a_month / a_day;
		return { date };
	}

	Calendar::DayOfWeek Calendar::GetDayOfWeek_NoLeapYear(Month a_month, Day a_day) noexcept
	{
		const auto date = DEFAULT_GAME_YEAR / a_month / a_day;
		return { date };
	}

	Calendar::DayOfMonth Calendar::GetDayOfMonth(Month a_month, Day a_day) noexcept
	{
		const auto dayOfMonth = a_month / a_day;
		return { dayOfMonth };
	}

	Calendar::MonthOfYear Calendar::GetMonthOfYear(Year a_year, Month a_month) noexcept
	{
		const auto monthOfYear = a_year / a_month;
		return { monthOfYear };
	}

	Calendar::Milliseconds Calendar::GetMillisecond() const noexcept
	{
		if (!gameHour) {
			return DEFAULT_GAME_MILLISECOND;
		}

		const auto hour = Hours(gameHour->GetValue());
		const auto hours = Hours(std::fmod(hour.count(), 1.0_f32));
		const auto minute = std::chrono::duration_cast<Minutes>(hours);
		const auto minutes = Minutes(std::fmod(minute.count(), 1.0_f32));
		const auto second = std::chrono::duration_cast<Seconds>(minutes);
		const auto seconds = Seconds(std::fmod(second.count(), 1.0_f32));

		return std::chrono::duration_cast<Milliseconds>(seconds);
	}

	Calendar::Seconds Calendar::GetSecond() const noexcept
	{
		if (!gameHour) {
			return DEFAULT_GAME_SECOND;
		}

		const auto hour = Hours(gameHour->GetValue());
		const auto hours = Hours(std::fmod(hour.count(), 1.0_f32));
		const auto minute = std::chrono::duration_cast<Minutes>(hours);
		const auto minutes = Minutes(std::fmod(minute.count(), 1.0_f32));

		return std::chrono::duration_cast<Seconds>(minutes);
	}

	Calendar::Minutes Calendar::GetMinute() const noexcept
	{
		if (!gameHour) {
			return DEFAULT_GAME_MINUTE;
		}

		const auto hour = Hours(gameHour->GetValue());
		const auto hours = Hours(std::fmod(hour.count(), 1.0_f32));

		return std::chrono::duration_cast<Minutes>(hours);
	}

	Calendar::Hours Calendar::GetHour() const noexcept
	{
		if (!gameHour) {
			return DEFAULT_GAME_HOUR;
		}

		return Hours(gameHour->GetValue());
	}

	Calendar::Day Calendar::GetDay() const noexcept
	{
		if (!gameDay) {
			return DEFAULT_GAME_DAY;
		}

		return Day(static_cast<std::uint32_t>(gameDay->GetValue()));
	}

	Calendar::Month Calendar::GetMonth() const noexcept
	{
		if (!gameMonth) {
			return DEFAULT_GAME_MONTH;
		}

		return Month(static_cast<std::uint32_t>(gameMonth->GetValue()));
	}

	Calendar::Year Calendar::GetYear() const noexcept
	{
		if (!gameYear) {
			return DEFAULT_GAME_YEAR;
		}

		return Year(static_cast<std::int32_t>(gameYear->GetValue()));
	}

	Calendar::TimePoint Calendar::GetTimePoint() const noexcept
	{
		const auto year = GetYear();
		const auto month = GetMonth();
		const auto day = GetDay();
		const auto hour = GetHour();
		const auto minute = GetMinute();
		const auto second = GetSecond();
		const auto millisecond = GetMillisecond();

		const auto yearMonthDay = YearMonthDay(year, month, day);
		const auto localDays = LocalDays(yearMonthDay);
		const auto timeOfDay = hour + minute + second + millisecond;

		return { localDays + timeOfDay };
	}

	Calendar::DayOfWeek Calendar::GetWeekDay() const noexcept
	{
		const auto month = GetMonth();
		const auto day = GetDay();

		return GetDayOfWeek_NoLeapYear(month, day);
	}

	Calendar::DayOfMonth Calendar::GetMonthDay() const noexcept
	{
		const auto month = GetMonth();
		const auto day = GetDay();

		return GetDayOfMonth(month, day);
	}

	Calendar::MonthOfYear Calendar::GetYearMonth() const noexcept
	{
		const auto year = DEFAULT_GAME_YEAR;
		const auto month = GetMonth();

		return GetMonthOfYear(year, month);
	}

	Calendar::Seconds Calendar::GetTimeScale() const noexcept
	{
		if (!timeScale) {
			return DEFAULT_TIME_SCALE;
		}

		return Seconds(timeScale->GetValue());
	}

	Calendar::Days Calendar::GetMidnightsPassed() const noexcept
	{
		return Days(midnightsPassed);
	}

	Calendar::Hours Calendar::GetHoursPassed() const noexcept
	{
		if (!gameDaysPassed) {
			return DEFAULT_GAME_HOURS_PASSED;
		}

		const auto daysPassed = Days(gameDaysPassed->GetValue());
		return std::chrono::duration_cast<Hours>(daysPassed);
	}

	Calendar::Days Calendar::GetDaysPassed() const noexcept
	{
		if (!gameDaysPassed) {
			return DEFAULT_GAME_DAYS_PASSED;
		}

		return Days(gameDaysPassed->GetValue());
	}

	std::string_view Calendar::GetDayName() const
	{
		const auto day = GetWeekDay();
		return GetNameOfDay(day);
	}

	std::string_view Calendar::GetMonthName() const
	{
		const auto month = GetMonth();
		return GetNameOfMonth(month);
	}
}
