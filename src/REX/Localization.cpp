#include "REX/Localization.hpp"

#include "REX/Message.hpp"
#include "REX/ZString.hpp"

namespace REX
{
	auto CreateLocale(REX::ZStringView a_localeName, std::locale::category a_localeCategory) noexcept
		-> std::expected<std::locale, std::exception>
	{
		try {
			return std::locale(a_localeName.data(), a_localeCategory);
		}
		catch (const std::runtime_error& error) {
			return std::unexpected(error);
		}
		catch (const std::bad_alloc& error) {
			return std::unexpected(error);
		}
	}

	auto CreateLocaleForLanguage(std::string_view a_language, std::locale::category a_localeCategory) noexcept
		-> std::expected<std::locale, std::exception>
	{
		try {
			const auto localeName = REX::Format("{}.UTF-8"sv, a_language);
			return std::locale(localeName, a_localeCategory);
		}
		catch (const std::runtime_error& error) {
			return std::unexpected(error);
		}
		catch (const std::bad_alloc& error) {
			return std::unexpected(error);
		}
	}

	auto GetOrCreateDefaultLocale() noexcept -> std::locale
	{
		static const auto DEFAULT_LOCALE = []() noexcept -> std::locale {
			for (const auto& localeName : DEFAULT_LOCALE_NAMES) {
				auto locale = CreateLocale(localeName);
				if (locale.has_value()) [[likely]] {
					return std::move(locale).value();
				}
			}

			REX::Fail(
				R"(Failed to create any of the default locales: {}.)"sv,
				std::ranges::views::join_with(DEFAULT_LOCALE_NAMES, ", "sv));
		}();

		return DEFAULT_LOCALE;
	}

	auto GetLocaleForLanguageOrDefault(std::string_view a_language, std::locale::category a_localeCategory) noexcept
		-> std::locale
	{
		auto locale = CreateLocaleForLanguage(a_language, a_localeCategory);
		if (!locale.has_value()) [[unlikely]] {
			return GetOrCreateDefaultLocale();
		}

		return std::move(locale).value();
	}
}
