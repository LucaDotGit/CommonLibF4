#include "REX/Ini.hpp"

#if COMMONLIB_OPTION_INI == 1

#include "REX/IniUtility.hpp"
#include "REX/Log.hpp"

#include <SimpleIni.h>

namespace REX::Ini::Impl
{
	template <class T>
	bool SettingLoad(
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

	template bool SettingLoad<bool>(const std::any&, const sec_t&, const key_t&, bool&, const bool&);
	template bool SettingLoad<std::int8_t>(const std::any&, const sec_t&, const key_t&, std::int8_t&, const std::int8_t&);
	template bool SettingLoad<std::uint8_t>(const std::any&, const sec_t&, const key_t&, std::uint8_t&, const std::uint8_t&);
	template bool SettingLoad<std::int16_t>(const std::any&, const sec_t&, const key_t&, std::int16_t&, const std::int16_t&);
	template bool SettingLoad<std::uint16_t>(const std::any&, const sec_t&, const key_t&, std::uint16_t&, const std::uint16_t&);
	template bool SettingLoad<std::int32_t>(const std::any&, const sec_t&, const key_t&, std::int32_t&, const std::int32_t&);
	template bool SettingLoad<std::uint32_t>(const std::any&, const sec_t&, const key_t&, std::uint32_t&, const std::uint32_t&);
	template bool SettingLoad<std::int64_t>(const std::any&, const sec_t&, const key_t&, std::int64_t&, const std::int64_t&);
	template bool SettingLoad<std::uint64_t>(const std::any&, const sec_t&, const key_t&, std::uint64_t&, const std::uint64_t&);
	template bool SettingLoad<REX::Float32>(const std::any&, const sec_t&, const key_t&, REX::Float32&, const REX::Float32&);
	template bool SettingLoad<REX::Float64>(const std::any&, const sec_t&, const key_t&, REX::Float64&, const REX::Float64&);
	template bool SettingLoad<REX::Float128>(const std::any&, const sec_t&, const key_t&, REX::Float128&, const REX::Float128&);
	template bool SettingLoad<std::string>(const std::any&, const sec_t&, const key_t&, std::string&, const std::string&);
	template bool SettingLoad<std::filesystem::path>(const std::any&, const sec_t&, const key_t&, std::filesystem::path&, const std::filesystem::path&);

	template <class T>
	bool SettingSave(
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

	template bool SettingSave<bool&>(const std::any&, const sec_t&, const key_t&, bool&);
	template bool SettingSave<std::int8_t&>(const std::any&, const sec_t&, const key_t&, std::int8_t&);
	template bool SettingSave<std::uint8_t&>(const std::any&, const sec_t&, const key_t&, std::uint8_t&);
	template bool SettingSave<std::int16_t&>(const std::any&, const sec_t&, const key_t&, std::int16_t&);
	template bool SettingSave<std::uint16_t&>(const std::any&, const sec_t&, const key_t&, std::uint16_t&);
	template bool SettingSave<std::int32_t&>(const std::any&, const sec_t&, const key_t&, std::int32_t&);
	template bool SettingSave<std::uint32_t&>(const std::any&, const sec_t&, const key_t&, std::uint32_t&);
	template bool SettingSave<std::int64_t&>(const std::any&, const sec_t&, const key_t&, std::int64_t&);
	template bool SettingSave<std::uint64_t&>(const std::any&, const sec_t&, const key_t&, std::uint64_t&);
	template bool SettingSave<REX::Float32&>(const std::any&, const sec_t&, const key_t&, REX::Float32&);
	template bool SettingSave<REX::Float64&>(const std::any&, const sec_t&, const key_t&, REX::Float64&);
	template bool SettingSave<REX::Float128&>(const std::any&, const sec_t&, const key_t&, REX::Float128&);
	template bool SettingSave<std::string&>(const std::any&, const sec_t&, const key_t&, std::string&);
	template bool SettingSave<std::filesystem::path&>(const std::any&, const sec_t&, const key_t&, std::filesystem::path&);
}

namespace REX::Ini
{
	bool SettingStore::Load()
	{
		const auto doLoad = [this](const std::filesystem::path& a_path, bool a_isMain) -> SI_Error {
			if (a_path.empty()) {
				return SI_OK;
			}

			auto file = CSimpleIniCaseA();
			file.SetAllowKeyOnly(Ini::ALLOW_KEY_ONLY);
			file.SetUnicode(Ini::USE_UNICODE);
			file.SetQuotes(Ini::USE_QUOTES);

			const auto loadError = file.LoadFile(a_path.native().data());
			if (loadError < SI_OK) {
				return loadError;
			}

			for (const auto& setting : _settings) {
				std::ignore = setting->Load(std::ref(file), a_isMain);
			}

			return SI_OK;
		};

		const auto loadError = doLoad(_mainPath, true);
		if (loadError < SI_OK) [[unlikely]] {
			REX::LogError(R"(Failed to load settings from "{}": error code {})"sv,
				_mainPath.generic_string(), loadError);
			return false;
		}

		std::ignore = doLoad(_customPath, false);
		return true;
	}

	bool SettingStore::Save()
	{
		const auto doSave = [this](const std::filesystem::path& a_path) -> SI_Error {
			if (a_path.empty()) {
				return SI_OK;
			}

			auto file = CSimpleIniCaseA();
			file.SetAllowKeyOnly(Ini::ALLOW_KEY_ONLY);
			file.SetUnicode(Ini::USE_UNICODE);
			file.SetQuotes(Ini::USE_QUOTES);

			std::ignore = file.LoadFile(a_path.native().data());

			for (const auto& setting : _settings) {
				std::ignore = setting->Save(std::ref(file));
			}

			return file.SaveFile(a_path.native().data(), Ini::PREPEND_BOM);
		};

		const auto saveError = doSave(_mainPath);
		if (saveError < SI_OK) [[unlikely]] {
			REX::LogError(R"(Failed to save settings to "{}": error code {})"sv,
				_mainPath.generic_string(), saveError);
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
