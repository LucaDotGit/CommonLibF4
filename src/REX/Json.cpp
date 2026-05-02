#include "REX/Json.hpp"

#if COMMONLIB_OPTION_JSON == 1

#include "REX/JsonUtility.hpp"
#include "REX/Log.hpp"

namespace REX::Json::Impl
{
	template <class T>
	bool SettingLoad(
		const std::any& a_data,
		const key_t& a_key,
		T& a_value,
		const T& a_defaultValue)
	{
		if (!a_data.has_value()) {
			a_value = a_defaultValue;
			return false;
		}

		const auto root = std::any_cast<std::reference_wrapper<nlohmann::json>>(a_data);

		try {
			a_value = root.get().value<T>(nlohmann::json::json_pointer(a_key), a_defaultValue);
			return true;
		}
		catch ([[maybe_unused]] const nlohmann::json::exception& error) {
			a_value = a_defaultValue;
			return false;
		}
	}

	template bool SettingLoad<bool>(const std::any&, const key_t&, bool&, const bool&);
	template bool SettingLoad<std::int8_t>(const std::any&, const key_t&, std::int8_t&, const std::int8_t&);
	template bool SettingLoad<std::uint8_t>(const std::any&, const key_t&, std::uint8_t&, const std::uint8_t&);
	template bool SettingLoad<std::int16_t>(const std::any&, const key_t&, std::int16_t&, const std::int16_t&);
	template bool SettingLoad<std::uint16_t>(const std::any&, const key_t&, std::uint16_t&, const std::uint16_t&);
	template bool SettingLoad<std::int32_t>(const std::any&, const key_t&, std::int32_t&, const std::int32_t&);
	template bool SettingLoad<std::uint32_t>(const std::any&, const key_t&, std::uint32_t&, const std::uint32_t&);
	template bool SettingLoad<std::int64_t>(const std::any&, const key_t&, std::int64_t&, const std::int64_t&);
	template bool SettingLoad<std::uint64_t>(const std::any&, const key_t&, std::uint64_t&, const std::uint64_t&);
	template bool SettingLoad<REX::Float32>(const std::any&, const key_t&, REX::Float32&, const REX::Float32&);
	template bool SettingLoad<REX::Float64>(const std::any&, const key_t&, REX::Float64&, const REX::Float64&);
	template bool SettingLoad<REX::Float128>(const std::any&, const key_t&, REX::Float128&, const REX::Float128&);
	template bool SettingLoad<std::string>(const std::any&, const key_t&, std::string&, const std::string&);
	template bool SettingLoad<std::filesystem::path>(const std::any&, const key_t&, std::filesystem::path&, const std::filesystem::path&);
	template bool SettingLoad<nlohmann::json>(const std::any&, const key_t&, nlohmann::json&, const nlohmann::json&);
	template bool SettingLoad<std::vector<bool>>(const std::any&, const key_t&, std::vector<bool>&, const std::vector<bool>&);
	template bool SettingLoad<std::vector<std::int8_t>>(const std::any&, const key_t&, std::vector<std::int8_t>&, const std::vector<std::int8_t>&);
	template bool SettingLoad<std::vector<std::uint8_t>>(const std::any&, const key_t&, std::vector<std::uint8_t>&, const std::vector<std::uint8_t>&);
	template bool SettingLoad<std::vector<std::int16_t>>(const std::any&, const key_t&, std::vector<std::int16_t>&, const std::vector<std::int16_t>&);
	template bool SettingLoad<std::vector<std::uint16_t>>(const std::any&, const key_t&, std::vector<std::uint16_t>&, const std::vector<std::uint16_t>&);
	template bool SettingLoad<std::vector<std::int32_t>>(const std::any&, const key_t&, std::vector<std::int32_t>&, const std::vector<std::int32_t>&);
	template bool SettingLoad<std::vector<std::uint32_t>>(const std::any&, const key_t&, std::vector<std::uint32_t>&, const std::vector<std::uint32_t>&);
	template bool SettingLoad<std::vector<std::int64_t>>(const std::any&, const key_t&, std::vector<std::int64_t>&, const std::vector<std::int64_t>&);
	template bool SettingLoad<std::vector<std::uint64_t>>(const std::any&, const key_t&, std::vector<std::uint64_t>&, const std::vector<std::uint64_t>&);
	template bool SettingLoad<std::vector<REX::Float32>>(const std::any&, const key_t&, std::vector<REX::Float32>&, const std::vector<REX::Float32>&);
	template bool SettingLoad<std::vector<REX::Float64>>(const std::any&, const key_t&, std::vector<REX::Float64>&, const std::vector<REX::Float64>&);
	template bool SettingLoad<std::vector<REX::Float128>>(const std::any&, const key_t&, std::vector<REX::Float128>&, const std::vector<REX::Float128>&);
	template bool SettingLoad<std::vector<std::string>>(const std::any&, const key_t&, std::vector<std::string>&, const std::vector<std::string>&);
	template bool SettingLoad<std::vector<std::filesystem::path>>(const std::any&, const key_t&, std::vector<std::filesystem::path>&, const std::vector<std::filesystem::path>&);
	template bool SettingLoad<std::vector<nlohmann::json>>(const std::any&, const key_t&, std::vector<nlohmann::json>&, const std::vector<nlohmann::json>&);

	template <class T>
	bool SettingSave(
		const std::any& a_data,
		const key_t& a_key,
		T&& a_value) // NOLINT(cppcoreguidelines-rvalue-reference-param-not-moved)
	{
		if (!a_data.has_value()) {
			return false;
		}

		const auto root = std::any_cast<std::reference_wrapper<nlohmann::json>>(a_data);

		if (a_key.starts_with(Json::KEY_SEPARATOR)) {
			root.get()[nlohmann::json::json_pointer(a_key)] = std::forward<T>(a_value);
		}
		else {
			root.get()[a_key] = std::forward<T>(a_value);
		}

		return true;
	}

	template bool SettingSave<bool&&>(const std::any&, const key_t&, bool&&);
	template bool SettingSave<std::int8_t&>(const std::any&, const key_t&, std::int8_t&);
	template bool SettingSave<std::uint8_t&>(const std::any&, const key_t&, std::uint8_t&);
	template bool SettingSave<std::int16_t&>(const std::any&, const key_t&, std::int16_t&);
	template bool SettingSave<std::uint16_t&>(const std::any&, const key_t&, std::uint16_t&);
	template bool SettingSave<std::int32_t&>(const std::any&, const key_t&, std::int32_t&);
	template bool SettingSave<std::uint32_t&>(const std::any&, const key_t&, std::uint32_t&);
	template bool SettingSave<std::int64_t&>(const std::any&, const key_t&, std::int64_t&);
	template bool SettingSave<std::uint64_t&>(const std::any&, const key_t&, std::uint64_t&);
	template bool SettingSave<REX::Float32&>(const std::any&, const key_t&, REX::Float32&);
	template bool SettingSave<REX::Float64&>(const std::any&, const key_t&, REX::Float64&);
	template bool SettingSave<REX::Float128&>(const std::any&, const key_t&, REX::Float128&);
	template bool SettingSave<std::string&>(const std::any&, const key_t&, std::string&);
	template bool SettingSave<std::filesystem::path&>(const std::any&, const key_t&, std::filesystem::path&);
	template bool SettingSave<nlohmann::json&>(const std::any&, const key_t&, nlohmann::json&);
	template bool SettingSave<std::vector<bool>&>(const std::any&, const key_t&, std::vector<bool>&);
	template bool SettingSave<std::vector<std::int8_t>&>(const std::any&, const key_t&, std::vector<std::int8_t>&);
	template bool SettingSave<std::vector<std::uint8_t>&>(const std::any&, const key_t&, std::vector<std::uint8_t>&);
	template bool SettingSave<std::vector<std::int16_t>&>(const std::any&, const key_t&, std::vector<std::int16_t>&);
	template bool SettingSave<std::vector<std::uint16_t>&>(const std::any&, const key_t&, std::vector<std::uint16_t>&);
	template bool SettingSave<std::vector<std::int32_t>&>(const std::any&, const key_t&, std::vector<std::int32_t>&);
	template bool SettingSave<std::vector<std::uint32_t>&>(const std::any&, const key_t&, std::vector<std::uint32_t>&);
	template bool SettingSave<std::vector<std::int64_t>&>(const std::any&, const key_t&, std::vector<std::int64_t>&);
	template bool SettingSave<std::vector<std::uint64_t>&>(const std::any&, const key_t&, std::vector<std::uint64_t>&);
	template bool SettingSave<std::vector<REX::Float32>&>(const std::any&, const key_t&, std::vector<REX::Float32>&);
	template bool SettingSave<std::vector<REX::Float64>&>(const std::any&, const key_t&, std::vector<REX::Float64>&);
	template bool SettingSave<std::vector<REX::Float128>&>(const std::any&, const key_t&, std::vector<REX::Float128>&);
	template bool SettingSave<std::vector<std::string>&>(const std::any&, const key_t&, std::vector<std::string>&);
	template bool SettingSave<std::vector<std::filesystem::path>&>(const std::any&, const key_t&, std::vector<std::filesystem::path>&);
	template bool SettingSave<std::vector<nlohmann::json>&>(const std::any&, const key_t&, std::vector<nlohmann::json>&);
}

namespace REX::Json
{
	bool SettingStore::Load()
	{
		const auto doLoad = [this](const std::filesystem::path& a_path, bool a_isMain) -> std::optional<nlohmann::json::exception> {
			if (a_path.empty()) {
				return std::nullopt;
			}

			auto root = nlohmann::json();

			try {
				auto stream = std::fstream(a_path, std::ios::in);
				root = nlohmann::json::parse(stream,
					Json::GetParserCallback<nlohmann::json>(),
					Json::ALLOW_EXCEPTIONS,
					Json::IGNORE_COMMENTS);
			}
			catch (const nlohmann::json::exception& error) {
				return error;
			}

			for (const auto& setting : _settings) {
				std::ignore = setting->Load(std::ref(root), a_isMain);
			}

			return std::nullopt;
		};

		const auto loadError = doLoad(_mainPath, true);
		if (loadError) [[unlikely]] {
			REX::LogError(R"(Failed to load settings from "{}": {})"sv,
				_mainPath.generic_string(), loadError->what());
			return false;
		}

		std::ignore = doLoad(_customPath, false);
		return true;
	}

	bool SettingStore::Save()
	{
		const auto doSave = [this](const std::filesystem::path& a_path) -> std::optional<nlohmann::json::exception> {
			if (a_path.empty()) {
				return std::nullopt;
			}

			auto output = nlohmann::json();

			try {
				auto stream = std::fstream(a_path, std::ios::in);
				output = nlohmann::json::parse(stream,
					Json::GetParserCallback<nlohmann::json>(),
					Json::ALLOW_EXCEPTIONS,
					Json::IGNORE_COMMENTS);
			}
			catch ([[maybe_unused]] const nlohmann::json::exception& error) {
				output = nlohmann::json();
			}

			for (const auto& setting : _settings) {
				std::ignore = setting->Save(std::ref(output));
			}

			try {
				auto stream = std::fstream(a_path, std::ios::out | std::ios::trunc);
				REX::Print(stream, "{}"sv,
					output.dump(
						Json::INDENT_COUNT,
						Json::INDENT_CHAR,
						Json::ENSURE_ASCII,
						Json::ERROR_HANDLER<nlohmann::json>));
				return std::nullopt;
			}
			catch (const nlohmann::json::exception& error) {
				return error;
			}
		};

		const auto saveError = doSave(_mainPath);
		if (saveError) [[unlikely]] {
			REX::LogError(R"(Failed to save settings to "{}": {})"sv,
				_mainPath.generic_string(), saveError->what());
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
	template class Setting<nlohmann::json>;
	template class Setting<std::vector<bool>>;
	template class Setting<std::vector<std::int8_t>>;
	template class Setting<std::vector<std::uint8_t>>;
	template class Setting<std::vector<std::int16_t>>;
	template class Setting<std::vector<std::uint16_t>>;
	template class Setting<std::vector<std::int32_t>>;
	template class Setting<std::vector<std::uint32_t>>;
	template class Setting<std::vector<std::int64_t>>;
	template class Setting<std::vector<std::uint64_t>>;
	template class Setting<std::vector<REX::Float32>>;
	template class Setting<std::vector<REX::Float64>>;
	template class Setting<std::vector<REX::Float128>>;
	template class Setting<std::vector<std::string>>;
	template class Setting<std::vector<std::filesystem::path>>;
	template class Setting<std::vector<nlohmann::json>>;
}

#if __cpp_lib_format > 0l
namespace std
{
	template struct formatter<REX::Json::Setting<bool>>;
	template struct formatter<REX::Json::Setting<std::int8_t>>;
	template struct formatter<REX::Json::Setting<std::uint8_t>>;
	template struct formatter<REX::Json::Setting<std::int16_t>>;
	template struct formatter<REX::Json::Setting<std::uint16_t>>;
	template struct formatter<REX::Json::Setting<std::int32_t>>;
	template struct formatter<REX::Json::Setting<std::uint32_t>>;
	template struct formatter<REX::Json::Setting<std::int64_t>>;
	template struct formatter<REX::Json::Setting<std::uint64_t>>;
	template struct formatter<REX::Json::Setting<REX::Float32>>;
	template struct formatter<REX::Json::Setting<REX::Float64>>;
	template struct formatter<REX::Json::Setting<REX::Float128>>;
	template struct formatter<REX::Json::Setting<std::string>>;
	template struct formatter<REX::Json::Setting<std::filesystem::path>>;
	template struct formatter<REX::Json::Setting<nlohmann::json>>;
	template struct formatter<REX::Json::Setting<std::vector<bool>>>;
	template struct formatter<REX::Json::Setting<std::vector<std::int8_t>>>;
	template struct formatter<REX::Json::Setting<std::vector<std::uint8_t>>>;
	template struct formatter<REX::Json::Setting<std::vector<std::int16_t>>>;
	template struct formatter<REX::Json::Setting<std::vector<std::uint16_t>>>;
	template struct formatter<REX::Json::Setting<std::vector<std::int32_t>>>;
	template struct formatter<REX::Json::Setting<std::vector<std::uint32_t>>>;
	template struct formatter<REX::Json::Setting<std::vector<std::int64_t>>>;
	template struct formatter<REX::Json::Setting<std::vector<std::uint64_t>>>;
	template struct formatter<REX::Json::Setting<std::vector<REX::Float32>>>;
	template struct formatter<REX::Json::Setting<std::vector<REX::Float64>>>;
	template struct formatter<REX::Json::Setting<std::vector<REX::Float128>>>;
	template struct formatter<REX::Json::Setting<std::vector<std::string>>>;
	template struct formatter<REX::Json::Setting<std::vector<std::filesystem::path>>>;
	template struct formatter<REX::Json::Setting<std::vector<nlohmann::json>>>;
}
#endif

#if FMT_VERSION > 0l
namespace fmt
{
	template struct formatter<REX::Json::Setting<bool>>;
	template struct formatter<REX::Json::Setting<std::int8_t>>;
	template struct formatter<REX::Json::Setting<std::uint8_t>>;
	template struct formatter<REX::Json::Setting<std::int16_t>>;
	template struct formatter<REX::Json::Setting<std::uint16_t>>;
	template struct formatter<REX::Json::Setting<std::int32_t>>;
	template struct formatter<REX::Json::Setting<std::uint32_t>>;
	template struct formatter<REX::Json::Setting<std::int64_t>>;
	template struct formatter<REX::Json::Setting<std::uint64_t>>;
	template struct formatter<REX::Json::Setting<REX::Float32>>;
	template struct formatter<REX::Json::Setting<REX::Float64>>;
	template struct formatter<REX::Json::Setting<REX::Float128>>;
	template struct formatter<REX::Json::Setting<std::string>>;
	template struct formatter<REX::Json::Setting<std::filesystem::path>>;
	template struct formatter<REX::Json::Setting<nlohmann::json>>;
	template struct formatter<REX::Json::Setting<std::vector<bool>>>;
	template struct formatter<REX::Json::Setting<std::vector<std::int8_t>>>;
	template struct formatter<REX::Json::Setting<std::vector<std::uint8_t>>>;
	template struct formatter<REX::Json::Setting<std::vector<std::int16_t>>>;
	template struct formatter<REX::Json::Setting<std::vector<std::uint16_t>>>;
	template struct formatter<REX::Json::Setting<std::vector<std::int32_t>>>;
	template struct formatter<REX::Json::Setting<std::vector<std::uint32_t>>>;
	template struct formatter<REX::Json::Setting<std::vector<std::int64_t>>>;
	template struct formatter<REX::Json::Setting<std::vector<std::uint64_t>>>;
	template struct formatter<REX::Json::Setting<std::vector<REX::Float32>>>;
	template struct formatter<REX::Json::Setting<std::vector<REX::Float64>>>;
	template struct formatter<REX::Json::Setting<std::vector<REX::Float128>>>;
	template struct formatter<REX::Json::Setting<std::vector<std::string>>>;
	template struct formatter<REX::Json::Setting<std::vector<std::filesystem::path>>>;
	template struct formatter<REX::Json::Setting<std::vector<nlohmann::json>>>;
}
#endif
#endif
