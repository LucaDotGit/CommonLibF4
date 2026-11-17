#pragma once

#include "REX/Hashing.hpp"
#include "REX/NotNull.hpp"

namespace REX
{
	class DateTime final
	{
	public:
		inline static constexpr auto WEEKDAYS = std::array{
			std::chrono::Monday,
			std::chrono::Tuesday,
			std::chrono::Wednesday,
			std::chrono::Thursday,
			std::chrono::Friday,
			std::chrono::Saturday,
			std::chrono::Sunday
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

		inline static constexpr auto LEAP_YEAR_DAYS = std::chrono::days(366);
		inline static constexpr auto NON_LEAP_YEAR_DAYS = std::chrono::days(365);

		inline static constexpr auto MAX_STRING_SIZE = static_cast<std::size_t>(0x20);

		constexpr DateTime() noexcept = default;
		constexpr ~DateTime() noexcept = default;

		constexpr DateTime(std::chrono::year a_year, std::chrono::month a_month, std::chrono::day a_day) noexcept :
			_year(a_year),
			_month(a_month),
			_day(a_day)
		{
		}

		constexpr DateTime(
			std::chrono::year a_year,
			std::chrono::month a_month,
			std::chrono::day a_day,
			std::chrono::hours a_hour,
			std::chrono::minutes a_minute,
			std::chrono::seconds a_second) noexcept :
			_year(a_year),
			_month(a_month),
			_day(a_day),
			_hour(a_hour),
			_minute(a_minute),
			_second(a_second)
		{
		}

		constexpr DateTime(std::chrono::hours a_hour, std::chrono::minutes a_minute, std::chrono::seconds a_second)
			noexcept :
			_hour(a_hour),
			_minute(a_minute),
			_second(a_second)
		{
		}

		constexpr DateTime(
			std::chrono::hours a_hour,
			std::chrono::minutes a_minute,
			std::chrono::seconds a_second,
			std::chrono::milliseconds a_millisecond,
			std::chrono::microseconds a_microsecond,
			std::chrono::nanoseconds a_nanosecond) noexcept :
			_hour(a_hour),
			_minute(a_minute),
			_second(a_second),
			_millisecond(a_millisecond),
			_microsecond(a_microsecond),
			_nanosecond(a_nanosecond)
		{
		}

		constexpr DateTime(
			std::chrono::year a_year,
			std::chrono::month a_month,
			std::chrono::day a_day,
			std::chrono::hours a_hour,
			std::chrono::minutes a_minute,
			std::chrono::seconds a_second,
			std::chrono::milliseconds a_millisecond,
			std::chrono::microseconds a_microsecond,
			std::chrono::nanoseconds a_nanosecond) noexcept :
			_year(a_year),
			_month(a_month),
			_day(a_day),
			_hour(a_hour),
			_minute(a_minute),
			_second(a_second),
			_millisecond(a_millisecond),
			_microsecond(a_microsecond),
			_nanosecond(a_nanosecond)
		{
		}

		constexpr explicit DateTime(std::chrono::year_month_day a_yearMonthDay) noexcept :
			DateTime(a_yearMonthDay.year(), a_yearMonthDay.month(), a_yearMonthDay.day())
		{
		}

		constexpr explicit DateTime(std::chrono::hh_mm_ss<std::chrono::nanoseconds> a_timeOfDay) noexcept :
			DateTime(
				a_timeOfDay.hours(),
				a_timeOfDay.minutes(),
				a_timeOfDay.seconds(),
				std::chrono::duration_cast<std::chrono::milliseconds>(a_timeOfDay.subseconds()),
				std::chrono::duration_cast<std::chrono::microseconds>(a_timeOfDay.subseconds()),
				std::chrono::duration_cast<std::chrono::nanoseconds>(a_timeOfDay.subseconds()))
		{
		}

		constexpr DateTime(
			std::chrono::year_month_day a_yearMonthDay,
			std::chrono::hh_mm_ss<std::chrono::nanoseconds> a_timeOfDay) noexcept :
			DateTime(
				a_yearMonthDay.year(),
				a_yearMonthDay.month(),
				a_yearMonthDay.day(),
				a_timeOfDay.hours(),
				a_timeOfDay.minutes(),
				a_timeOfDay.seconds(),
				std::chrono::duration_cast<std::chrono::milliseconds>(a_timeOfDay.subseconds()),
				std::chrono::duration_cast<std::chrono::microseconds>(a_timeOfDay.subseconds()),
				std::chrono::duration_cast<std::chrono::nanoseconds>(a_timeOfDay.subseconds()))
		{
		}

		constexpr DateTime(const DateTime&) noexcept = default;
		constexpr DateTime(DateTime&&) noexcept = default;

		constexpr auto operator=(const DateTime&) noexcept -> DateTime& = default;
		constexpr auto operator=(DateTime&&) noexcept -> DateTime& = default;

		[[nodiscard]]
		constexpr auto operator==(const DateTime&) const noexcept -> bool = default;
		[[nodiscard]]
		constexpr auto operator<=>(const DateTime&) const noexcept = default;

		[[nodiscard]]
		constexpr auto GetYear() const noexcept
		{
			return _year;
		}

		[[nodiscard]]
		constexpr auto GetMonth() const noexcept
		{
			return _month;
		}

		[[nodiscard]]
		constexpr auto GetDay() const noexcept
		{
			return _day;
		}

		[[nodiscard]]
		constexpr auto GetHour() const noexcept
		{
			return _hour;
		}

		[[nodiscard]]
		constexpr auto GetMinute() const noexcept
		{
			return _minute;
		}

		[[nodiscard]]
		constexpr auto GetSecond() const noexcept
		{
			return _second;
		}

		[[nodiscard]]
		constexpr auto GetMillisecond() const noexcept
		{
			return _millisecond;
		}

		[[nodiscard]]
		constexpr auto GetMicrosecond() const noexcept
		{
			return _microsecond;
		}

		[[nodiscard]]
		constexpr auto GetNanosecond() const noexcept
		{
			return _nanosecond;
		}

		[[nodiscard]]
		constexpr auto GetYearMonthDay() const noexcept -> std::chrono::year_month_day
		{
			return {_year, _month, _day};
		}

		[[nodiscard]]
		constexpr auto GetYearMonth() const noexcept -> std::chrono::year_month
		{
			return {_year, _month};
		}

		[[nodiscard]]
		constexpr auto GetMonthDay() const noexcept -> std::chrono::month_day
		{
			return {_month, _day};
		}

		[[nodiscard]]
		constexpr auto IsLeapYear() const noexcept -> bool
		{
			return _year.is_leap();
		}

		[[nodiscard]]
		constexpr auto GetDaysInYear() const noexcept -> std::chrono::days
		{
			return IsLeapYear() ? LEAP_YEAR_DAYS : NON_LEAP_YEAR_DAYS;
		}

		[[nodiscard]]
		constexpr auto GetDaysInMonth() const noexcept -> std::chrono::days
		{
			const auto yearMonth = std::chrono::year_month_day_last(_year, _month / std::chrono::last);
			return std::chrono::days(static_cast<std::uint32_t>(yearMonth.day()));
		}

		[[nodiscard]]
		constexpr auto GetDayOfWeek() const noexcept -> std::chrono::weekday
		{
			const auto yearMonthDay = std::chrono::year_month_day(_year, _month, _day);
			return {yearMonthDay};
		}

		[[nodiscard]]
		constexpr auto GetTimeOfDay() const noexcept -> std::chrono::hh_mm_ss<std::chrono::nanoseconds>
		{
			const auto timePoint = std::chrono::duration_cast<std::chrono::nanoseconds>(_hour) +
								   std::chrono::duration_cast<std::chrono::nanoseconds>(_minute) +
								   std::chrono::duration_cast<std::chrono::nanoseconds>(_second) +
								   std::chrono::duration_cast<std::chrono::nanoseconds>(_millisecond) +
								   std::chrono::duration_cast<std::chrono::nanoseconds>(_microsecond) +
								   std::chrono::duration_cast<std::chrono::nanoseconds>(_nanosecond);

			return std::chrono::hh_mm_ss<std::chrono::nanoseconds>(timePoint);
		}

		[[nodiscard]]
		static auto GetCurrentTimeZone() noexcept
			-> std::expected<REX::NotNull<const std::chrono::time_zone*>, std::exception>;

		[[nodiscard]]
		static auto Now() noexcept -> std::expected<DateTime, std::exception>;
		[[nodiscard]]
		static auto UtcNow() noexcept -> DateTime;

		template <class Clock, class Duration>
		[[nodiscard]]
		static constexpr auto FromTimePoint(std::chrono::time_point<Clock, Duration> a_timePoint) noexcept -> DateTime
		{
			const auto daysTimePoint = std::chrono::floor<std::chrono::days>(a_timePoint);
			const auto yearMonthDay = std::chrono::year_month_day(daysTimePoint);

			auto tempTimeOfDay = std::chrono::duration_cast<std::chrono::nanoseconds>(a_timePoint - daysTimePoint);

			const auto hours = std::chrono::duration_cast<std::chrono::hours>(tempTimeOfDay);
			tempTimeOfDay -= hours;
			const auto minutes = std::chrono::duration_cast<std::chrono::minutes>(tempTimeOfDay);
			tempTimeOfDay -= minutes;
			const auto seconds = std::chrono::duration_cast<std::chrono::seconds>(tempTimeOfDay);
			tempTimeOfDay -= seconds;
			const auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(tempTimeOfDay);
			tempTimeOfDay -= milliseconds;
			const auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(tempTimeOfDay);
			tempTimeOfDay -= microseconds;
			const auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(tempTimeOfDay);

			return {
				yearMonthDay.year(),
				yearMonthDay.month(),
				yearMonthDay.day(),
				hours,
				minutes,
				seconds,
				milliseconds,
				microseconds,
				nanoseconds
			};
		}

		template <class Clock, class Duration>
		[[nodiscard]]
		constexpr auto ToTimePoint() const noexcept -> std::chrono::time_point<Clock, Duration>
		{
			const auto yearMonthDay = GetYearMonthDay();
			const auto daysTimePoint = std::chrono::time_point<Clock, std::chrono::days>(yearMonthDay);

			const auto timeOfDay = GetTimeOfDay();
			const auto timeOfDayDuration = std::chrono::duration_cast<Duration>(timeOfDay.to_duration());

			return {daysTimePoint + timeOfDayDuration};
		}

		[[nodiscard]]
		constexpr auto ToSystemTimePoint() const noexcept
		{
			return ToTimePoint<std::chrono::system_clock, std::chrono::system_clock::duration>();
		}

		[[nodiscard]]
		constexpr auto ToLocalTimePoint() const noexcept
		{
			return ToTimePoint<std::chrono::local_t, std::chrono::system_clock::duration>();
		}

		[[nodiscard]]
		static constexpr auto FromUnixTimeSeconds(std::chrono::seconds a_seconds) noexcept -> DateTime
		{
			const auto unixTimePoint = std::chrono::system_clock::time_point(a_seconds);
			return FromTimePoint(unixTimePoint);
		}

		[[nodiscard]]
		constexpr auto ToUnixTimeSeconds() const noexcept -> std::chrono::seconds
		{
			const auto systemTimePoint = ToSystemTimePoint();
			return std::chrono::duration_cast<std::chrono::seconds>(systemTimePoint.time_since_epoch());
		}

		template <class Rep, class Period>
		[[nodiscard]]
		constexpr auto AddDuration(std::chrono::duration<Rep, Period> a_duration) const noexcept -> DateTime
		{
			const auto timePoint = ToSystemTimePoint() + a_duration;
			return FromTimePoint(timePoint);
		}

		[[nodiscard]]
		constexpr auto AddDateOnly(const DateTime& a_dateTime) const noexcept -> DateTime
		{
			const auto lhsSystemDays = std::chrono::sys_days(GetYearMonthDay());
			const auto rhsSystemDays = std::chrono::sys_days(a_dateTime.GetYearMonthDay());
			const auto systemDaysDifference = rhsSystemDays - lhsSystemDays;
			const auto yearMonthDay = std::chrono::year_month_day(lhsSystemDays + systemDaysDifference);

			return {
				yearMonthDay.year(),
				yearMonthDay.month(),
				yearMonthDay.day(),
				_hour,
				_minute,
				_second,
				_millisecond,
				_microsecond,
				_nanosecond
			};
		}

		[[nodiscard]]
		constexpr auto AddTimeSpan(const DateTime& a_dateTime) const noexcept -> DateTime
		{
			const auto timeOfDay = a_dateTime.GetTimeOfDay();
			return AddDuration(timeOfDay.to_duration());
		}

		[[nodiscard]]
		constexpr auto AddYears(std::chrono::years a_years) const noexcept -> DateTime
		{
			const auto systemDays = std::chrono::sys_days(GetYearMonthDay() + a_years);
			const auto yearMonthDay = std::chrono::year_month_day(systemDays);

			return {
				yearMonthDay.year(),
				yearMonthDay.month(),
				yearMonthDay.day(),
				_hour,
				_minute,
				_second,
				_millisecond,
				_microsecond,
				_nanosecond
			};
		}

		[[nodiscard]]
		constexpr auto AddMonths(std::chrono::months a_months) const noexcept -> DateTime
		{
			const auto systemDays = std::chrono::sys_days(GetYearMonthDay() + a_months);
			const auto yearMonthDay = std::chrono::year_month_day(systemDays);

			return {
				yearMonthDay.year(),
				yearMonthDay.month(),
				yearMonthDay.day(),
				_hour,
				_minute,
				_second,
				_millisecond,
				_microsecond,
				_nanosecond
			};
		}

		[[nodiscard]]
		constexpr auto AddDays(std::chrono::days a_days) const noexcept -> DateTime
		{
			return AddDuration(a_days);
		}

		[[nodiscard]]
		constexpr auto AddHours(std::chrono::hours a_hours) const noexcept -> DateTime
		{
			return AddDuration(a_hours);
		}

		[[nodiscard]]
		constexpr auto AddMinutes(std::chrono::minutes a_minutes) const noexcept -> DateTime
		{
			return AddDuration(a_minutes);
		}

		[[nodiscard]]
		constexpr auto AddSeconds(std::chrono::seconds a_seconds) const noexcept -> DateTime
		{
			return AddDuration(a_seconds);
		}

		[[nodiscard]]
		constexpr auto AddMilliseconds(std::chrono::milliseconds a_milliseconds) const noexcept -> DateTime
		{
			return AddDuration(a_milliseconds);
		}

		[[nodiscard]]
		constexpr auto AddMicroseconds(std::chrono::microseconds a_microseconds) const noexcept -> DateTime
		{
			return AddDuration(a_microseconds);
		}

		[[nodiscard]]
		constexpr auto AddNanoseconds(std::chrono::nanoseconds a_nanoseconds) const noexcept -> DateTime
		{
			return AddDuration(a_nanoseconds);
		}

		template <class Rep, class Period>
		[[nodiscard]]
		constexpr auto SubtractDuration(std::chrono::duration<Rep, Period> a_duration) const noexcept -> DateTime
		{
			const auto timePoint = ToSystemTimePoint() - a_duration;
			return FromTimePoint(timePoint);
		}

		[[nodiscard]]
		constexpr auto SubtractDateOnly(const DateTime& a_dateTime) const noexcept -> DateTime
		{
			const auto lhsSystemDays = std::chrono::sys_days(GetYearMonthDay());
			const auto rhsSystemDays = std::chrono::sys_days(a_dateTime.GetYearMonthDay());
			const auto systemDaysDifference = rhsSystemDays - lhsSystemDays;
			const auto yearMonthDay = std::chrono::year_month_day(lhsSystemDays - systemDaysDifference);

			return {
				yearMonthDay.year(),
				yearMonthDay.month(),
				yearMonthDay.day(),
				_hour,
				_minute,
				_second,
				_millisecond,
				_microsecond,
				_nanosecond
			};
		}

		[[nodiscard]]
		constexpr auto SubtractTimeSpan(const DateTime& a_dateTime) const noexcept -> DateTime
		{
			const auto timeOfDay = a_dateTime.GetTimeOfDay();
			return SubtractDuration(timeOfDay.to_duration());
		}

		[[nodiscard]]
		constexpr auto SubtractYears(std::chrono::years a_years) const noexcept -> DateTime
		{
			const auto systemDays = std::chrono::sys_days(GetYearMonthDay() - a_years);
			const auto yearMonthDay = std::chrono::year_month_day(systemDays);

			return {
				yearMonthDay.year(),
				yearMonthDay.month(),
				yearMonthDay.day(),
				_hour,
				_minute,
				_second,
				_millisecond,
				_microsecond,
				_nanosecond
			};
		}

		[[nodiscard]]
		constexpr auto SubtractMonths(std::chrono::months a_months) const noexcept -> DateTime
		{
			const auto systemDays = std::chrono::sys_days(GetYearMonthDay() - a_months);
			const auto yearMonthDay = std::chrono::year_month_day(systemDays);

			return {
				yearMonthDay.year(),
				yearMonthDay.month(),
				yearMonthDay.day(),
				_hour,
				_minute,
				_second,
				_millisecond,
				_microsecond,
				_nanosecond
			};
		}

		[[nodiscard]]
		constexpr auto SubtractDays(std::chrono::days a_days) const noexcept -> DateTime
		{
			return SubtractDuration(a_days);
		}

		[[nodiscard]]
		constexpr auto SubtractHours(std::chrono::hours a_hours) const noexcept -> DateTime
		{
			return SubtractDuration(a_hours);
		}

		[[nodiscard]]
		constexpr auto SubtractMinutes(std::chrono::minutes a_minutes) const noexcept -> DateTime
		{
			return SubtractDuration(a_minutes);
		}

		[[nodiscard]]
		constexpr auto SubtractSeconds(std::chrono::seconds a_seconds) const noexcept -> DateTime
		{
			return SubtractDuration(a_seconds);
		}

		[[nodiscard]]
		constexpr auto SubtractMilliseconds(std::chrono::milliseconds a_milliseconds) const noexcept -> DateTime
		{
			return SubtractDuration(a_milliseconds);
		}

		[[nodiscard]]
		constexpr auto SubtractMicroseconds(std::chrono::microseconds a_microseconds) const noexcept -> DateTime
		{
			return SubtractDuration(a_microseconds);
		}

		[[nodiscard]]
		constexpr auto SubtractNanoseconds(std::chrono::nanoseconds a_nanoseconds) const noexcept -> DateTime
		{
			return SubtractDuration(a_nanoseconds);
		}

		auto ToString(std::span<char> a_buffer) const noexcept -> std::string_view;

		[[nodiscard]]
		auto ToString() const -> std::string;

		// private:
		// NOLINTBEGIN(readability-identifier-naming)
		std::chrono::year _year{1};
		std::chrono::month _month{std::chrono::January};
		std::chrono::day _day{1};
		std::chrono::duration<std::uint8_t, std::chrono::hours::period> _hour{0};
		std::chrono::duration<std::uint8_t, std::chrono::minutes::period> _minute{0};
		std::chrono::duration<std::uint8_t, std::chrono::seconds::period> _second{0};
		std::chrono::duration<std::uint16_t, std::chrono::milliseconds::period> _millisecond{0};
		std::chrono::duration<std::uint16_t, std::chrono::microseconds::period> _microsecond{0};
		std::chrono::duration<std::uint16_t, std::chrono::nanoseconds::period> _nanosecond{0};
		// NOLINTEND(readability-identifier-naming)
	};

	static_assert(std::is_standard_layout_v<DateTime>);
	static_assert(std::is_trivially_destructible_v<DateTime>);
	static_assert(std::is_trivially_copyable_v<DateTime>);
	static_assert(std::is_trivially_move_constructible_v<DateTime>);

	static_assert([]() consteval noexcept -> bool {
		const auto dateTime = DateTime::FromUnixTimeSeconds(1'000'000'000s);
		return (dateTime.GetYear() == 2'001y) &&
			   (dateTime.GetMonth() == std::chrono::September) &&
			   (dateTime.GetDay() == 9d) &&
			   (dateTime.GetHour() == 1h) &&
			   (dateTime.GetMinute() == 46min) &&
			   (dateTime.GetSecond() == 40s);
	}());

	static_assert([]() consteval noexcept -> bool {
		const auto dateTime = DateTime(2'026y, std::chrono::June, 15d, 10h, 30min, 45s)
								  .AddDateOnly(DateTime(2'026y, std::chrono::July, 15d));
		return (dateTime.GetYear() == 2'026y) &&
			   (dateTime.GetMonth() == std::chrono::July) &&
			   (dateTime.GetDay() == 15d) &&
			   (dateTime.GetHour() == 10h) &&
			   (dateTime.GetMinute() == 30min) &&
			   (dateTime.GetSecond() == 45s);
	}());

	static_assert([]() consteval noexcept -> bool {
		const auto dateTime =
			DateTime(2'026y, std::chrono::June, 15d, 10h, 30min, 45s).AddTimeSpan(DateTime(1h, 30min, 0s));
		return (dateTime.GetYear() == 2'026y) &&
			   (dateTime.GetMonth() == std::chrono::June) &&
			   (dateTime.GetDay() == 15d) &&
			   (dateTime.GetHour() == 12h) &&
			   (dateTime.GetMinute() == 0min) &&
			   (dateTime.GetSecond() == 45s);
	}());

	static_assert([]() consteval noexcept -> bool {
		const auto dateTime =
			DateTime(2'026y, std::chrono::January, 15d, 12h, 30min, 45s).AddYears(std::chrono::years(1));
		return (dateTime.GetYear() == 2'027y) &&
			   (dateTime.GetMonth() == std::chrono::January) &&
			   (dateTime.GetDay() == 15d) &&
			   (dateTime.GetHour() == 12h) &&
			   (dateTime.GetMinute() == 30min) &&
			   (dateTime.GetSecond() == 45s);
	}());

	static_assert([]() consteval noexcept -> bool {
		const auto dateTime =
			DateTime(2'026y, std::chrono::June, 15d, 12h, 30min, 45s).AddMonths(std::chrono::months(7));
		return (dateTime.GetYear() == 2'027y) &&
			   (dateTime.GetMonth() == std::chrono::January) &&
			   (dateTime.GetDay() == 15d) &&
			   (dateTime.GetHour() == 12h) &&
			   (dateTime.GetMinute() == 30min) &&
			   (dateTime.GetSecond() == 45s);
	}());

	static_assert([]() consteval noexcept -> bool {
		const auto dateTime =
			DateTime(2'026y, std::chrono::January, 31d, 12h, 30min, 45s).AddMonths(std::chrono::months(1));
		return (dateTime.GetYear() == 2'026y) &&
			   (dateTime.GetMonth() == std::chrono::March) &&
			   (dateTime.GetDay() == 3d) &&
			   (dateTime.GetHour() == 12h) &&
			   (dateTime.GetMinute() == 30min) &&
			   (dateTime.GetSecond() == 45s);
	}());
}

namespace std
{
	template <>
	struct hash<REX::DateTime>
	{
	public:
		[[nodiscard]]
		auto operator()(const REX::DateTime& a_key) const noexcept -> std::size_t
		{
			return REX::HashCombine(
				static_cast<std::int32_t>(a_key.GetYear()),
				static_cast<std::uint32_t>(a_key.GetMonth()),
				static_cast<std::uint32_t>(a_key.GetDay()),
				a_key.GetHour().count(),
				a_key.GetMinute().count(),
				a_key.GetSecond().count(),
				a_key.GetMillisecond().count(),
				a_key.GetMicrosecond().count(),
				a_key.GetNanosecond().count());
		}
	};
}

#if (__cpp_lib_format > 0l)
namespace std
{
	template <>
	struct formatter<REX::DateTime> : public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]]
		constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]]
		constexpr auto format(const REX::DateTime& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, a_value.ToString());
		}
	};
}
#endif

#if (FMT_VERSION > 0l)
namespace fmt
{
	template <>
	struct formatter<REX::DateTime> : public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]]
		constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]]
		constexpr auto format(const REX::DateTime& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, a_value.ToString());
		}
	};
}
#endif

#if __has_include(<glaze/glaze.hpp>)
namespace glz
{
	template <>
	struct meta<REX::DateTime>
	{
	public:
		using self_type = REX::DateTime;
		using other_type = std::chrono::system_clock::time_point;

		inline static constexpr auto read_fn = [](self_type& a_self, const other_type& a_other) noexcept -> void {
			a_self = self_type::FromTimePoint(a_other);
		};

		inline static constexpr auto write_fn = [](const self_type& a_self, other_type& a_other) noexcept -> void {
			a_other = a_self.ToSystemTimePoint();
		};

		inline static constexpr auto value = glz::custom<read_fn, write_fn>;
	};
}
#endif
