#include "REX/Locale.hpp"

#include "REX/Message.hpp"

namespace REX
{
	auto CreateCLocale(std::string_view a_localeName, std::int32_t a_localeCategory) noexcept -> CLocale
	{
		auto* result = ::_create_locale(a_localeCategory, a_localeName.data());
		if (!result) {
			return { nullptr, ::_free_locale };
		}

		return { result, ::_free_locale };
	}

	auto CreateCppLocale(std::string_view a_localeName, std::locale::category a_localeCategory) noexcept -> std::expected<CppLocale, std::runtime_error>
	{
		try {
			return std::locale(a_localeName.data(), a_localeCategory);
		}
		catch (std::runtime_error& error) {
			return std::unexpected(std::move(error));
		}
	}

	auto GetDefaultCLocale() noexcept -> const CLocale&
	{
		static const auto DEFAULT_LOCALE = []() noexcept {
			auto result = CreateCLocale(DEFAULT_LOCALE_NAME);
			if (!result) [[unlikely]] {
				REX::Fail(R"(Failed to create the default C locale "{}".)"sv,
					DEFAULT_LOCALE_NAME);
			}

			return result;
		}();

		return DEFAULT_LOCALE;
	}

	auto GetDefaultCppLocale() noexcept -> const CppLocale&
	{
		static const auto DEFAULT_LOCALE = []() noexcept {
			auto result = CreateCppLocale(DEFAULT_LOCALE_NAME);
			if (!result) [[unlikely]] {
				REX::Fail(R"(Failed to create the default C++ locale "{}".)"sv,
					DEFAULT_LOCALE_NAME);
			}

			return *result;
		}();

		return DEFAULT_LOCALE;
	}
}
