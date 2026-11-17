#pragma once

#include "REX/Contract.hpp"
#include "REX/Hashing.hpp"

namespace REX::Logging
{
	enum class Level : std::int32_t
	{
		Trace = 0,
		Debug = 1,
		Information = 2,
		Warning = 3,
		Error = 4,
		Critical = 5,
		None = 6,

		_Min = Trace,
		_Max = None,

		_Count = _Max + 1
	};

	[[nodiscard]]
	constexpr auto GetFullNameForLevel(Level a_level) noexcept -> std::string_view
	{
		switch (a_level) {
			case Level::Trace: {
				return "Trace"sv;
			}
			case Level::Debug: {
				return "Debug"sv;
			}
			case Level::Information: {
				return "Information"sv;
			}
			case Level::Warning: {
				return "Warning"sv;
			}
			case Level::Error: {
				return "Error"sv;
			}
			case Level::Critical: {
				return "Critical"sv;
			}
			case Level::None: {
				return "None"sv;
			}
			[[unlikely]]
			default: {
				REX::Assert(false);
				return "Unknown"sv;
			}
		}
	}

	[[nodiscard]]
	constexpr auto GetShortNameForLevel(Level a_level) noexcept -> std::string_view
	{
		switch (a_level) {
			case Level::Trace: {
				return "Trce"sv;
			}
			case Level::Debug: {
				return "Dbug"sv;
			}
			case Level::Information: {
				return "Info"sv;
			}
			case Level::Warning: {
				return "Warn"sv;
			}
			case Level::Error: {
				return "Erro"sv;
			}
			case Level::Critical: {
				return "Crit"sv;
			}
			case Level::None: {
				return "None"sv;
			}
			[[unlikely]]
			default: {
				REX::Assert(false);
				return "Unkn"sv;
			}
		}
	}

	[[nodiscard]]
	constexpr auto GetAnsiColorCodeForLevel(Level a_level) noexcept -> std::string_view
	{
		constexpr auto WHITE_ANSI_COLOR_CODE = "\033[90m"sv;
		constexpr auto CYAN_ANSI_COLOR_CODE = "\033[36m"sv;
		constexpr auto GREEN_ANSI_COLOR_CODE = "\033[32m"sv;
		constexpr auto YELLOW_ANSI_COLOR_CODE = "\033[33m"sv;
		constexpr auto RED_ANSI_COLOR_CODE = "\033[31m"sv;
		constexpr auto RED_BACKGROUND_ANSI_COLOR_CODE = "\033[1;41;97m"sv;
		constexpr auto RESET_ANSI_COLOR_CODE = "\033[0m"sv;

		switch (a_level) {
			case Level::Trace: {
				return WHITE_ANSI_COLOR_CODE;
			}
			case Level::Debug: {
				return CYAN_ANSI_COLOR_CODE;
			}
			case Level::Information: {
				return GREEN_ANSI_COLOR_CODE;
			}
			case Level::Warning: {
				return YELLOW_ANSI_COLOR_CODE;
			}
			case Level::Error: {
				return RED_ANSI_COLOR_CODE;
			}
			case Level::Critical: {
				return RED_BACKGROUND_ANSI_COLOR_CODE;
			}
			case Level::None: {
				return RESET_ANSI_COLOR_CODE;
			}
			[[unlikely]]
			default: {
				REX::Assert(false);
				return RESET_ANSI_COLOR_CODE;
			}
		}
	}
}

namespace std
{
	template <>
	struct hash<REX::Logging::Level>
	{
	public:
		[[nodiscard]]
		auto operator()(const REX::Logging::Level& a_level) const noexcept -> std::size_t
		{
			return REX::Hash(a_level);
		}
	};
}

#if (__cpp_lib_format > 0l)
namespace std
{
	template <>
	struct formatter<REX::Logging::Level> : public formatter<std::string_view>
	{
	public:
		template <class FormatContext>
		[[nodiscard]]
		constexpr auto parse(FormatContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]]
		constexpr auto format(const REX::Logging::Level& a_level, FormatContext& a_context) const
		{
			return format_to(a_context.out(), "{}", REX::Logging::GetFullNameForLevel(a_level));
		}
	};
}
#endif

#if (FMT_VERSION > 0l)
namespace fmt
{
	template <>
	struct formatter<REX::Logging::Level> : public formatter<std::string_view>
	{
	public:
		template <class FormatContext>
		[[nodiscard]]
		constexpr auto parse(FormatContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]]
		constexpr auto format(const REX::Logging::Level& a_level, FormatContext& a_context) const
		{
			return format_to(a_context.out(), "{}", REX::Logging::GetFullNameForLevel(a_level));
		}
	};
}
#endif

#if __has_include(<glaze/glaze.hpp>)
namespace glz
{
	template <>
	struct meta<REX::Logging::Level>
	{
	public:
		using enum REX::Logging::Level;

		inline static constexpr auto value = glz::enumerate(Trace, Debug, Information, Warning, Error, Critical, None);
	};
}
#endif
