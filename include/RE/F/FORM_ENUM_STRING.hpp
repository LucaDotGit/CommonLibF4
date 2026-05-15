#pragma once

#include "RE/F/FormType.hpp"

namespace RE
{
	class FORM_ENUM_STRING
	{
	public:
		[[nodiscard]] static auto GetFormTypeStrings()
			-> std::span<FORM_ENUM_STRING, std::to_underlying(FormType::kTotal)>;

		[[nodiscard]] static FormType GetFormTypeByString(std::string_view a_typeString);
		[[nodiscard]] static std::string_view GetFormStringByType(FormType a_formType);

		// members
		REX::Enum<FormType, std::uint8_t> formType; // 00
		const char* formString;						// 08
		std::uint32_t formCode;						// 10
	};
	static_assert(sizeof(FORM_ENUM_STRING) == 0x18);
}

#if __cpp_lib_format > 0l
namespace std
{
	template <>
	struct formatter<RE::FormType>
		: public formatter<std::string_view>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::FormType& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, RE::FORM_ENUM_STRING::GetFormStringByType(a_value));
		}
	};
}
#endif

#if FMT_VERSION > 0l
namespace fmt
{
	template <>
	struct formatter<RE::FormType>
		: public formatter<std::string_view>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::FormType& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, RE::FORM_ENUM_STRING::GetFormStringByType(a_value));
		}
	};
}
#endif
