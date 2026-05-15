#include "REX/IniUtility.hpp"

#if COMMONLIB_OPTION_INI == 1

namespace REX::Ini
{
	bool IsValid(ErrorNumber a_errorCode) noexcept
	{
		return a_errorCode >= SI_OK;
	}

	REX::PosixError CreatePosixErrorCode(ErrorNumber a_errorCode) noexcept
	{
		if (a_errorCode >= SI_OK) {
			return REX::CreatePosixError(REX::POSIX_ERROR_CODE_SUCCESS);
		}

		if (a_errorCode == SI_FAIL) {
			return REX::CreatePosixError(REX::PosixErrorCode::io_error);
		}

		if (a_errorCode == SI_NOMEM) {
			return REX::CreatePosixError(REX::PosixErrorCode::not_enough_memory);
		}

		return REX::GetCurrentPosixError();
	}

	auto CombineSetting(std::string_view a_section, std::string_view a_key)
		-> std::string
	{
		const auto section = std::string(a_section);
		const auto key = std::string(a_key);

		return section + SETTING_SEPARATOR + key;
	}

	auto SplitSetting(std::string_view a_setting)
		-> std::pair<std::string_view, std::string_view>
	{
		const auto separatorIndex = a_setting.find(SETTING_SEPARATOR);
		if (separatorIndex == std::string::npos) {
			return std::make_pair(std::string_view(), a_setting);
		}

		const auto section = a_setting.substr(0, separatorIndex);
		const auto key = a_setting.substr(separatorIndex + 1);

		return std::make_pair(section, key);
	}

	template auto GetValue(const CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view)
		-> std::optional<std::nullptr_t>;
	template bool SetValue(CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view, std::nullptr_t);

	template auto GetValue(const CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view)
		-> std::optional<bool>;
	template bool SetValue(CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view, bool);

	template auto GetValue(const CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view)
		-> std::optional<std::int8_t>;
	template bool SetValue(CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view, std::int8_t);

	template auto GetValue(const CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view)
		-> std::optional<std::uint8_t>;
	template bool SetValue(CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view, std::uint8_t);

	template auto GetValue(const CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view)
		-> std::optional<std::int16_t>;
	template bool SetValue(CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view, std::int16_t);

	template auto GetValue(const CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view)
		-> std::optional<std::uint16_t>;
	template bool SetValue(CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view, std::uint16_t);

	template auto GetValue(const CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view)
		-> std::optional<std::int32_t>;
	template bool SetValue(CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view, std::int32_t);

	template auto GetValue(const CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view)
		-> std::optional<std::uint32_t>;
	template bool SetValue(CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view, std::uint32_t);

	template auto GetValue(const CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view)
		-> std::optional<std::int64_t>;
	template bool SetValue(CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view, std::int64_t);

	template auto GetValue(const CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view)
		-> std::optional<std::uint64_t>;
	template bool SetValue(CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view, std::uint64_t);

	template auto GetValue(const CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view)
		-> std::optional<REX::Float32>;
	template bool SetValue(CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view, REX::Float32);

	template auto GetValue(const CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view)
		-> std::optional<REX::Float64>;
	template bool SetValue(CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view, REX::Float64);

	template auto GetValue(const CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view)
		-> std::optional<REX::Float128>;
	template bool SetValue(CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view, REX::Float128);

	template auto GetValue(const CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view)
		-> std::optional<std::string>;
	template bool SetValue(CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view, const std::string&);

	template auto GetValue(const CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view)
		-> std::optional<std::string_view>;
	template bool SetValue(CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view, const REX::zstring_view&);

	template auto GetValue(const CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view)
		-> std::optional<std::filesystem::path>;
	template bool SetValue(CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view, const std::filesystem::path&);

	template auto GetDetectedValue(const CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view)
		-> std::optional<VariantType<>>;
	template bool SetDetectedValue(CSimpleIniCaseA&, REX::zstring_view, REX::zstring_view, const VariantType<>&);
}

#endif
