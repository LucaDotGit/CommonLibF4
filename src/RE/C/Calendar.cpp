#include "RE/C/Calendar.hpp"

#include "RE/S/Setting.hpp"
#include "RE/S/SettingUtil.hpp"
#include "RE/T/TESGlobal.hpp"

namespace RE::Impl
{
	namespace
	{
		constexpr auto DAY_SETTING_KEYS = REX::CreateStaticOrderedSet(
			"sDayMonday"sv,
			"sDayTuesday"sv,
			"sDayWednesday"sv,
			"sDayThursday"sv,
			"sDayFriday"sv,
			"sDaySaturday"sv,
			"sDaySunday"sv);

		constexpr auto MONTH_SETTING_KEYS = REX::CreateStaticOrderedSet(
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
			"sMonthDecember"sv);
	}
}

namespace RE
{
	auto Calendar::GetSingleton() noexcept -> Calendar*
	{
		static const auto SINGLETON = REL::Relocation<Calendar**>(ID::Calendar::Singleton);
		return *SINGLETON;
	}

	auto Calendar::GetAllDayNames() -> std::span<const BSFixedStringCS, REX::DateTime::WEEKDAYS.size()>
	{
		static const auto ALL_DAY_NAMES = []() -> auto {
			auto result = std::array<BSFixedStringCS, Impl::DAY_SETTING_KEYS.size()>();
			for (auto i = static_cast<std::size_t>(0); i < Impl::DAY_SETTING_KEYS.size(); i++) {
				const auto* daySetting = GetGameSetting(Impl::DAY_SETTING_KEYS[i]);
				if (!daySetting || !daySetting->IsString()) [[unlikely]] {
					REX::Assert(false);
					continue;
				}

				result[i] = BSFixedStringCS(daySetting->GetString());
			}

			return result;
		}();

		return ALL_DAY_NAMES;
	}

	auto Calendar::GetAllMonthNames() -> std::span<const BSFixedStringCS, REX::DateTime::MONTHS.size()>
	{
		static const auto ALL_MONTH_NAMES = []() -> auto {
			auto result = std::array<BSFixedStringCS, Impl::MONTH_SETTING_KEYS.size()>();
			for (auto i = static_cast<std::size_t>(0); i < Impl::MONTH_SETTING_KEYS.size(); i++) {
				const auto* monthSetting = GetGameSetting(Impl::MONTH_SETTING_KEYS[i]);
				if (!monthSetting || !monthSetting->IsString()) [[unlikely]] {
					REX::Assert(false);
					continue;
				}

				result[i] = BSFixedStringCS(monthSetting->GetString());
			}

			return result;
		}();

		return ALL_MONTH_NAMES;
	}

	auto Calendar::GetNameOfDay(std::chrono::weekday a_dayOfWeek) -> BSFixedStringCS
	{
		const auto dayIndex = a_dayOfWeek.iso_encoding();
		if (dayIndex >= Impl::DAY_SETTING_KEYS.size()) {
			return {};
		}

		return GetAllDayNames()[dayIndex];
	}

	auto Calendar::GetNameOfMonth(std::chrono::month a_month) -> BSFixedStringCS
	{
		const auto monthIndex = static_cast<std::uint32_t>(a_month) - 1;
		if (monthIndex >= Impl::MONTH_SETTING_KEYS.size()) {
			return {};
		}

		return GetAllMonthNames()[monthIndex];
	}

	auto Calendar::GetDayOfWeek(
		[[maybe_unused]] std::chrono::year a_year,
		std::chrono::month a_month,
		std::chrono::day a_day) noexcept -> std::chrono::weekday
	{
		// The game does not account for leap years, so the default year is used instead.

		const auto yearMonthDay = std::chrono::year_month_day(DEFAULT_GAME_YEAR, a_month, a_day);
		return {yearMonthDay};
	}

	auto Calendar::GetTimeOfDay(Hours a_hours, Minutes a_minutes, Seconds a_seconds, Milliseconds a_milliseconds)
		noexcept -> std::chrono::hh_mm_ss<Calendar::Milliseconds>
	{
		const auto timeOfDay = a_hours + a_minutes + a_seconds + a_milliseconds;
		return std::chrono::hh_mm_ss(timeOfDay);
	}

	auto Calendar::GetYear() const noexcept -> std::chrono::year
	{
		if (!gameYear) {
			return DEFAULT_GAME_YEAR;
		}

		return std::chrono::year(static_cast<std::int32_t>(gameYear->GetValue()));
	}

	auto Calendar::SetYear(std::chrono::year a_year) const noexcept -> bool
	{
		if (!gameYear) {
			return false;
		}

		gameYear->SetValue(static_cast<REX::Float32>(static_cast<std::int32_t>(a_year)));
		return true;
	}

	auto Calendar::GetMonth() const noexcept -> std::chrono::month
	{
		if (!gameMonth) {
			return DEFAULT_GAME_MONTH;
		}

		return std::chrono::month(static_cast<std::uint32_t>(gameMonth->GetValue()));
	}

	auto Calendar::SetMonth(std::chrono::month a_month) const noexcept -> bool
	{
		if (!gameMonth) {
			return false;
		}

		gameMonth->SetValue(static_cast<REX::Float32>(static_cast<std::uint32_t>(a_month)));
		return true;
	}

	auto Calendar::GetDay() const noexcept -> std::chrono::day
	{
		if (!gameDay) {
			return DEFAULT_GAME_DAY;
		}

		return std::chrono::day(static_cast<std::uint32_t>(gameDay->GetValue()));
	}

	auto Calendar::SetDay(std::chrono::day a_day) const noexcept -> bool
	{
		if (!gameDay) {
			return false;
		}

		gameDay->SetValue(static_cast<REX::Float32>(static_cast<std::uint32_t>(a_day)));
		return true;
	}

	auto Calendar::GetHour() const noexcept -> Calendar::Hours
	{
		if (!gameHour) {
			return DEFAULT_GAME_HOUR;
		}

		return Hours(gameHour->GetValue());
	}

	auto Calendar::SetHour(Hours a_hour) const noexcept -> bool
	{
		if (!gameHour) {
			return false;
		}

		gameHour->SetValue(a_hour.count());
		return true;
	}

	auto Calendar::GetSubHour() const noexcept -> Calendar::SubHourData
	{
		if (!gameHour) {
			return DEFAULT_GAME_SUB_HOUR;
		}

		constexpr auto HOURS_MODIFIER = static_cast<REX::Float32>(1.0);

		const auto hours = Hours(gameHour->GetValue());
		const auto hoursPart = Hours(std::fmod(hours.count(), HOURS_MODIFIER));

		const auto minutes = std::chrono::duration_cast<Minutes>(hoursPart);
		const auto minutesPart = Minutes(std::fmod(minutes.count(), HOURS_MODIFIER));

		const auto seconds = std::chrono::duration_cast<Seconds>(minutesPart);
		const auto secondsPart = Seconds(std::fmod(seconds.count(), HOURS_MODIFIER));

		const auto milliseconds = std::chrono::duration_cast<Milliseconds>(secondsPart);

		return {.hour = hours, .minute = minutes, .second = seconds, .millisecond = milliseconds};
	}

	auto Calendar::SetSubHour(const SubHourData& a_subHour) const noexcept -> bool
	{
		if (!gameHour) {
			return false;
		}

		const auto totalHours = a_subHour.hour +
								std::chrono::duration_cast<Hours>(a_subHour.minute) +
								std::chrono::duration_cast<Hours>(a_subHour.second) +
								std::chrono::duration_cast<Hours>(a_subHour.millisecond);

		gameHour->SetValue(totalHours.count());
		return true;
	}

	auto Calendar::GetElapsedDays() const noexcept -> Calendar::Days
	{
		if (!gameDaysPassed) {
			return DEFAULT_ELAPSED_GAME_DAYS;
		}

		return Days(gameDaysPassed->GetValue());
	}

	auto Calendar::SetElapsedDays(Days a_elapsedDays) const noexcept -> bool
	{
		if (!gameDaysPassed) {
			return false;
		}

		gameDaysPassed->SetValue(a_elapsedDays.count());
		return true;
	}

	auto Calendar::GetElapsedHours() const noexcept -> Calendar::Hours
	{
		if (!gameDaysPassed) {
			return DEFAULT_ELAPSED_GAME_HOURS;
		}

		const auto daysPassed = Days(gameDaysPassed->GetValue());
		return std::chrono::duration_cast<Hours>(daysPassed);
	}

	auto Calendar::SetElapsedHours(Hours a_elapsedHours) const noexcept -> bool
	{
		if (!gameDaysPassed) {
			return false;
		}

		const auto daysPassed = std::chrono::duration_cast<Days>(a_elapsedHours);
		gameDaysPassed->SetValue(daysPassed.count());
		return true;
	}

	auto Calendar::GetTimeScale() const noexcept -> Calendar::Seconds
	{
		if (!timeScale) {
			return DEFAULT_TIME_SCALE;
		}

		return Seconds(timeScale->GetValue());
	}

	auto Calendar::SetTimeScale(Seconds a_timeScale) const noexcept -> bool
	{
		if (!timeScale) {
			return false;
		}

		timeScale->SetValue(a_timeScale.count());
		return true;
	}

	auto Calendar::GetElapsedMidnights() const noexcept -> std::uint32_t
	{
		return midnightsPassed;
	}

	void Calendar::SetElapsedMidnights(std::uint32_t a_elapsedMidnights) noexcept
	{
		midnightsPassed = a_elapsedMidnights;
	}

	auto Calendar::GetElapsedRawDays() const noexcept -> Calendar::Days
	{
		return rawDaysPassed;
	}

	void Calendar::SetElapsedRawDays(Days a_elapsedRawDays) noexcept
	{
		rawDaysPassed = a_elapsedRawDays;
	}

	auto Calendar::GetDateTime() const noexcept -> REX::DateTime
	{
		const auto year = GetYear();
		const auto month = GetMonth();
		const auto day = GetDay();
		const auto subHour = GetSubHour();

		const auto hour = std::chrono::duration_cast<std::chrono::hours>(subHour.hour);
		const auto minute = std::chrono::duration_cast<std::chrono::minutes>(subHour.minute);
		const auto second = std::chrono::duration_cast<std::chrono::seconds>(subHour.second);
		const auto millisecond = std::chrono::duration_cast<std::chrono::milliseconds>(subHour.millisecond);
		const auto microsecond = std::chrono::microseconds::zero();
		const auto nanosecond = std::chrono::nanoseconds::zero();

		return {year, month, day, hour, minute, second, millisecond, microsecond, nanosecond};
	}

	auto Calendar::SetDateTime(const REX::DateTime& a_dateTime) const noexcept -> bool
	{
		const auto year = a_dateTime.GetYear();
		const auto month = a_dateTime.GetMonth();
		const auto day = a_dateTime.GetDay();

		const auto hour = std::chrono::duration_cast<Hours>(a_dateTime.GetHour());
		const auto minute = std::chrono::duration_cast<Minutes>(a_dateTime.GetMinute());
		const auto second = std::chrono::duration_cast<Seconds>(a_dateTime.GetSecond());
		const auto millisecond = std::chrono::duration_cast<Milliseconds>(a_dateTime.GetMillisecond());

		const auto subHour = SubHourData{.hour = hour, .minute = minute, .second = second, .millisecond = millisecond};

		return SetYear(year) && SetMonth(month) && SetDay(day) && SetSubHour(subHour);
	}

	auto Calendar::GetYearMonthDay() const noexcept -> std::chrono::year_month_day
	{
		const auto year = GetYear();
		const auto month = GetMonth();
		const auto day = GetDay();

		return {year, month, day};
	}

	auto Calendar::GetYearMonth() const noexcept -> std::chrono::year_month
	{
		const auto year = GetYear();
		const auto month = GetMonth();

		return {year, month};
	}

	auto Calendar::GetMonthDay() const noexcept -> std::chrono::month_day
	{
		const auto month = GetMonth();
		const auto day = GetDay();

		return {month, day};
	}

	auto Calendar::GetWeekDay() const noexcept -> std::chrono::weekday
	{
		const auto year = GetYear();
		const auto month = GetMonth();
		const auto day = GetDay();

		return GetDayOfWeek(year, month, day);
	}

	auto Calendar::GetDayTime() const noexcept -> std::chrono::hh_mm_ss<Calendar::Milliseconds>
	{
		const auto subHour = GetSubHour();
		return GetTimeOfDay(subHour.hour, subHour.minute, subHour.second, subHour.millisecond);
	}

	auto Calendar::GetDayName() const -> BSFixedStringCS
	{
		const auto weekDay = GetWeekDay();
		return GetNameOfDay(weekDay);
	}

	auto Calendar::GetMonthName() const -> BSFixedStringCS
	{
		const auto month = GetMonth();
		return GetNameOfMonth(month);
	}
}
