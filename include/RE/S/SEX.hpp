#pragma once

namespace RE
{
	enum class SEX : std::int32_t
	{
		kNone = -1,
		kMale = 0,
		kFemale = 1,

		kTotal = 2
	};
}

#if __cpp_lib_format > 0l
namespace std
{
	template <>
	struct formatter<RE::SEX>
		: public formatter<std::string_view>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::SEX& a_value, FormatContext& a_ctx) const
		{
			using namespace std::string_view_literals;

			switch (a_value) {
				case RE::SEX::kNone: {
					return format_to(a_ctx.out(), "{}"sv, "None"sv);
				}
				case RE::SEX::kMale: {
					return format_to(a_ctx.out(), "{}"sv, "Male"sv);
				}
				case RE::SEX::kFemale: {
					return format_to(a_ctx.out(), "{}"sv, "Female"sv);
				}
				[[unlikely]] default: {
					return format_to(a_ctx.out(), "{}"sv, "Unknown"sv);
				}
			}
		}
	};
}
#endif

#if FMT_VERSION > 0l
namespace fmt
{
	template <>
	struct formatter<RE::SEX>
		: public formatter<std::string_view>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::SEX& a_value, FormatContext& a_ctx) const
		{
			using namespace std::string_view_literals;

			switch (a_value) {
				case RE::SEX::kNone: {
					return format_to(a_ctx.out(), "{}"sv, "None"sv);
				}
				case RE::SEX::kMale: {
					return format_to(a_ctx.out(), "{}"sv, "Male"sv);
				}
				case RE::SEX::kFemale: {
					return format_to(a_ctx.out(), "{}"sv, "Female"sv);
				}
				[[unlikely]] default: {
					return format_to(a_ctx.out(), "{}"sv, "Unknown"sv);
				}
			}
		}
	};
}
#endif
