#include "REX/Ini.hpp"

#if COMMONLIB_OPTION_INI == 1

#include "REX/Error.hpp"
#include "REX/IniUtility.hpp"
#include "REX/Log.hpp"

#include <SimpleIni.h>

namespace REX::Ini::Impl
{
	template <class T>
	bool LoadSetting(
		const std::any& a_data,
		const sec_t& a_section,
		const key_t& a_key,
		T& a_value,
		const T& a_defaultValue)
	{
		if (!a_data.has_value()) {
			a_value = a_defaultValue;
			return false;
		}

		const auto file = std::any_cast<std::reference_wrapper<CSimpleIniCaseA>>(a_data);

		auto newValue = REX::Ini::GetValue<T>(file.get(), a_section, a_key);
		if (!newValue) {
			a_value = a_defaultValue;
			return false;
		}

		a_value = *std::move(newValue);
		return true;
	}

	template bool LoadSetting<bool>(const std::any&, const sec_t&, const key_t&, bool&, const bool&);
	template bool LoadSetting<std::int8_t>(const std::any&, const sec_t&, const key_t&, std::int8_t&, const std::int8_t&);
	template bool LoadSetting<std::uint8_t>(const std::any&, const sec_t&, const key_t&, std::uint8_t&, const std::uint8_t&);
	template bool LoadSetting<std::int16_t>(const std::any&, const sec_t&, const key_t&, std::int16_t&, const std::int16_t&);
	template bool LoadSetting<std::uint16_t>(const std::any&, const sec_t&, const key_t&, std::uint16_t&, const std::uint16_t&);
	template bool LoadSetting<std::int32_t>(const std::any&, const sec_t&, const key_t&, std::int32_t&, const std::int32_t&);
	template bool LoadSetting<std::uint32_t>(const std::any&, const sec_t&, const key_t&, std::uint32_t&, const std::uint32_t&);
	template bool LoadSetting<std::int64_t>(const std::any&, const sec_t&, const key_t&, std::int64_t&, const std::int64_t&);
	template bool LoadSetting<std::uint64_t>(const std::any&, const sec_t&, const key_t&, std::uint64_t&, const std::uint64_t&);
	template bool LoadSetting<REX::Float32>(const std::any&, const sec_t&, const key_t&, REX::Float32&, const REX::Float32&);
	template bool LoadSetting<REX::Float64>(const std::any&, const sec_t&, const key_t&, REX::Float64&, const REX::Float64&);
	template bool LoadSetting<REX::Float128>(const std::any&, const sec_t&, const key_t&, REX::Float128&, const REX::Float128&);
	template bool LoadSetting<std::string>(const std::any&, const sec_t&, const key_t&, std::string&, const std::string&);
	template bool LoadSetting<std::filesystem::path>(const std::any&, const sec_t&, const key_t&, std::filesystem::path&, const std::filesystem::path&);

	template <class T>
	bool SaveSetting(
		const std::any& a_data,
		const sec_t& a_section,
		const key_t& a_key,
		T&& a_value)
	{
		if (!a_data.has_value()) {
			return false;
		}

		const auto file = std::any_cast<std::reference_wrapper<CSimpleIniCaseA>>(a_data);
		REX::Ini::SetValue<std::remove_reference_t<T>>(file.get(), a_section, a_key, std::forward<T>(a_value));
		return true;
	}

	template bool SaveSetting<bool&>(const std::any&, const sec_t&, const key_t&, bool&);
	template bool SaveSetting<std::int8_t&>(const std::any&, const sec_t&, const key_t&, std::int8_t&);
	template bool SaveSetting<std::uint8_t&>(const std::any&, const sec_t&, const key_t&, std::uint8_t&);
	template bool SaveSetting<std::int16_t&>(const std::any&, const sec_t&, const key_t&, std::int16_t&);
	template bool SaveSetting<std::uint16_t&>(const std::any&, const sec_t&, const key_t&, std::uint16_t&);
	template bool SaveSetting<std::int32_t&>(const std::any&, const sec_t&, const key_t&, std::int32_t&);
	template bool SaveSetting<std::uint32_t&>(const std::any&, const sec_t&, const key_t&, std::uint32_t&);
	template bool SaveSetting<std::int64_t&>(const std::any&, const sec_t&, const key_t&, std::int64_t&);
	template bool SaveSetting<std::uint64_t&>(const std::any&, const sec_t&, const key_t&, std::uint64_t&);
	template bool SaveSetting<REX::Float32&>(const std::any&, const sec_t&, const key_t&, REX::Float32&);
	template bool SaveSetting<REX::Float64&>(const std::any&, const sec_t&, const key_t&, REX::Float64&);
	template bool SaveSetting<REX::Float128&>(const std::any&, const sec_t&, const key_t&, REX::Float128&);
	template bool SaveSetting<std::string&>(const std::any&, const sec_t&, const key_t&, std::string&);
	template bool SaveSetting<std::filesystem::path&>(const std::any&, const sec_t&, const key_t&, std::filesystem::path&);
}

namespace REX::Ini
{
	bool SettingStore::Load()
	{
		const auto doLoad = [this](const std::filesystem::path& a_path, bool a_isMain) -> REX::SystemError {
			if (a_path.empty()) {
				return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
			}

			auto file = CSimpleIniCaseA();
			file.SetAllowKeyOnly(REX::Ini::ALLOW_KEY_ONLY);
			file.SetUnicode(REX::Ini::USE_UNICODE);
			file.SetQuotes(REX::Ini::USE_QUOTES);

			try {
				auto fileStream = std::fstream(a_path, std::ios::in);
				fileStream.exceptions(std::ios::failbit | std::ios::badbit);

				auto fileContent = std::string{ std::istreambuf_iterator<char>(fileStream), std::istreambuf_iterator<char>() };

				const auto loadError = REX::Ini::CreatePosixErrorCode(file.LoadData(fileContent));
				if (loadError.value() != REX::ERROR_NUMBER_SUCCESS) {
					return REX::CreateSystemError(loadError.value());
				}
			}
			catch (const std::ios::failure& error) {
				return error.code();
			}

			for (const auto& setting : _settings) {
				std::ignore = setting->Load(std::ref(file), a_isMain);
			}

			return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
		};

		const auto loadError = doLoad(_mainPath, true);
		if (loadError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			REX::LogError(R"(Failed to load settings from "{}": {})"sv,
				_mainPath.generic_string(), loadError.message());
			return false;
		}

		std::ignore = doLoad(_customPath, false);
		return true;
	}

	bool SettingStore::Save()
	{
		const auto doSave = [this](const std::filesystem::path& a_path) -> REX::SystemError {
			if (a_path.empty()) {
				return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
			}

			auto file = CSimpleIniCaseA();
			file.SetAllowKeyOnly(REX::Ini::ALLOW_KEY_ONLY);
			file.SetUnicode(REX::Ini::USE_UNICODE);
			file.SetQuotes(REX::Ini::USE_QUOTES);

			try {
				auto fileStream = std::fstream(a_path, std::ios::in);
				fileStream.exceptions(std::ios::failbit | std::ios::badbit);

				auto fileContent = std::string{ std::istreambuf_iterator<char>(fileStream), std::istreambuf_iterator<char>() };
				std::ignore = file.LoadData(fileContent);
			}
			catch (const std::ios::failure& error) {
				std::ignore = error;
			}

			for (const auto& setting : _settings) {
				std::ignore = setting->Save(std::ref(file));
			}

			try {
				REX::CreateParentDirectories(a_path);
			}
			catch (const std::filesystem::filesystem_error& error) {
				return error.code();
			}

			try {
				auto fileStream = std::fstream(a_path, std::ios::out | std::ios::trunc);
				fileStream.exceptions(std::ios::failbit | std::ios::badbit);

				auto fileOutput = std::string();

				const auto saveError = REX::Ini::CreatePosixErrorCode(file.Save(fileOutput, REX::Ini::PREPEND_BOM));
				if (saveError.value() != REX::ERROR_NUMBER_SUCCESS) {
					return REX::CreateSystemError(saveError.value());
				}

				REX::Print(fileStream, "{}"sv, std::move(fileOutput));
				return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
			}
			catch (const std::ios::failure& error) {
				return error.code();
			}
		};

		const auto saveError = doSave(_mainPath);
		if (saveError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			REX::LogError(R"(Failed to save settings to "{}": {})"sv,
				_mainPath.generic_string(), saveError.message());
			return false;
		}

		return true;
	}

	template class Setting<bool>;
	template class Setting<std::int8_t>;
	template class Setting<std::uint8_t>;
	template class Setting<std::int16_t>;
	template class Setting<std::uint16_t>;
	template class Setting<std::int32_t>;
	template class Setting<std::uint32_t>;
	template class Setting<std::int64_t>;
	template class Setting<std::uint64_t>;
	template class Setting<REX::Float32>;
	template class Setting<REX::Float64>;
	template class Setting<REX::Float128>;
	template class Setting<std::string>;
	template class Setting<std::filesystem::path>;
}

#if __cpp_lib_format > 0l
namespace std
{
	template struct formatter<REX::Ini::Setting<bool>>;
	template struct formatter<REX::Ini::Setting<std::int8_t>>;
	template struct formatter<REX::Ini::Setting<std::uint8_t>>;
	template struct formatter<REX::Ini::Setting<std::int16_t>>;
	template struct formatter<REX::Ini::Setting<std::uint16_t>>;
	template struct formatter<REX::Ini::Setting<std::int32_t>>;
	template struct formatter<REX::Ini::Setting<std::uint32_t>>;
	template struct formatter<REX::Ini::Setting<std::int64_t>>;
	template struct formatter<REX::Ini::Setting<std::uint64_t>>;
	template struct formatter<REX::Ini::Setting<REX::Float32>>;
	template struct formatter<REX::Ini::Setting<REX::Float64>>;
	template struct formatter<REX::Ini::Setting<REX::Float128>>;
	template struct formatter<REX::Ini::Setting<std::string>>;
	template struct formatter<REX::Ini::Setting<std::filesystem::path>>;
}
#endif

#if FMT_VERSION > 0l
namespace fmt
{
	template struct formatter<REX::Ini::Setting<bool>>;
	template struct formatter<REX::Ini::Setting<std::int8_t>>;
	template struct formatter<REX::Ini::Setting<std::uint8_t>>;
	template struct formatter<REX::Ini::Setting<std::int16_t>>;
	template struct formatter<REX::Ini::Setting<std::uint16_t>>;
	template struct formatter<REX::Ini::Setting<std::int32_t>>;
	template struct formatter<REX::Ini::Setting<std::uint32_t>>;
	template struct formatter<REX::Ini::Setting<std::int64_t>>;
	template struct formatter<REX::Ini::Setting<std::uint64_t>>;
	template struct formatter<REX::Ini::Setting<REX::Float32>>;
	template struct formatter<REX::Ini::Setting<REX::Float64>>;
	template struct formatter<REX::Ini::Setting<REX::Float128>>;
	template struct formatter<REX::Ini::Setting<std::string>>;
	template struct formatter<REX::Ini::Setting<std::filesystem::path>>;
}
#endif
#endif
