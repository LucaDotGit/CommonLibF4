#include "REX/Json.hpp"

#if COMMONLIB_OPTION_JSON == 1

#include "REX/IO.hpp"
#include "REX/JsonUtility.hpp"
#include "REX/Log.hpp"

namespace REX::Json::Impl
{
	template <class T>
	bool LoadSetting(
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

	template bool LoadSetting<bool>(const std::any&, const key_t&, bool&, const bool&);
	template bool LoadSetting<std::int8_t>(const std::any&, const key_t&, std::int8_t&, const std::int8_t&);
	template bool LoadSetting<std::uint8_t>(const std::any&, const key_t&, std::uint8_t&, const std::uint8_t&);
	template bool LoadSetting<std::int16_t>(const std::any&, const key_t&, std::int16_t&, const std::int16_t&);
	template bool LoadSetting<std::uint16_t>(const std::any&, const key_t&, std::uint16_t&, const std::uint16_t&);
	template bool LoadSetting<std::int32_t>(const std::any&, const key_t&, std::int32_t&, const std::int32_t&);
	template bool LoadSetting<std::uint32_t>(const std::any&, const key_t&, std::uint32_t&, const std::uint32_t&);
	template bool LoadSetting<std::int64_t>(const std::any&, const key_t&, std::int64_t&, const std::int64_t&);
	template bool LoadSetting<std::uint64_t>(const std::any&, const key_t&, std::uint64_t&, const std::uint64_t&);
	template bool LoadSetting<REX::Float32>(const std::any&, const key_t&, REX::Float32&, const REX::Float32&);
	template bool LoadSetting<REX::Float64>(const std::any&, const key_t&, REX::Float64&, const REX::Float64&);
	template bool LoadSetting<REX::Float128>(const std::any&, const key_t&, REX::Float128&, const REX::Float128&);
	template bool LoadSetting<std::string>(const std::any&, const key_t&, std::string&, const std::string&);
	template bool LoadSetting<std::filesystem::path>(const std::any&, const key_t&, std::filesystem::path&, const std::filesystem::path&);
	template bool LoadSetting<nlohmann::json>(const std::any&, const key_t&, nlohmann::json&, const nlohmann::json&);
	template bool LoadSetting<std::vector<bool>>(const std::any&, const key_t&, std::vector<bool>&, const std::vector<bool>&);
	template bool LoadSetting<std::vector<std::int8_t>>(const std::any&, const key_t&, std::vector<std::int8_t>&, const std::vector<std::int8_t>&);
	template bool LoadSetting<std::vector<std::uint8_t>>(const std::any&, const key_t&, std::vector<std::uint8_t>&, const std::vector<std::uint8_t>&);
	template bool LoadSetting<std::vector<std::int16_t>>(const std::any&, const key_t&, std::vector<std::int16_t>&, const std::vector<std::int16_t>&);
	template bool LoadSetting<std::vector<std::uint16_t>>(const std::any&, const key_t&, std::vector<std::uint16_t>&, const std::vector<std::uint16_t>&);
	template bool LoadSetting<std::vector<std::int32_t>>(const std::any&, const key_t&, std::vector<std::int32_t>&, const std::vector<std::int32_t>&);
	template bool LoadSetting<std::vector<std::uint32_t>>(const std::any&, const key_t&, std::vector<std::uint32_t>&, const std::vector<std::uint32_t>&);
	template bool LoadSetting<std::vector<std::int64_t>>(const std::any&, const key_t&, std::vector<std::int64_t>&, const std::vector<std::int64_t>&);
	template bool LoadSetting<std::vector<std::uint64_t>>(const std::any&, const key_t&, std::vector<std::uint64_t>&, const std::vector<std::uint64_t>&);
	template bool LoadSetting<std::vector<REX::Float32>>(const std::any&, const key_t&, std::vector<REX::Float32>&, const std::vector<REX::Float32>&);
	template bool LoadSetting<std::vector<REX::Float64>>(const std::any&, const key_t&, std::vector<REX::Float64>&, const std::vector<REX::Float64>&);
	template bool LoadSetting<std::vector<REX::Float128>>(const std::any&, const key_t&, std::vector<REX::Float128>&, const std::vector<REX::Float128>&);
	template bool LoadSetting<std::vector<std::string>>(const std::any&, const key_t&, std::vector<std::string>&, const std::vector<std::string>&);
	template bool LoadSetting<std::vector<std::filesystem::path>>(const std::any&, const key_t&, std::vector<std::filesystem::path>&, const std::vector<std::filesystem::path>&);
	template bool LoadSetting<std::vector<nlohmann::json>>(const std::any&, const key_t&, std::vector<nlohmann::json>&, const std::vector<nlohmann::json>&);

	template <class T>
	bool SaveSetting(
		const std::any& a_data,
		const key_t& a_key,
		T&& a_value) // NOLINT(cppcoreguidelines-rvalue-reference-param-not-moved)
	{
		if (!a_data.has_value()) {
			return false;
		}

		const auto root = std::any_cast<std::reference_wrapper<nlohmann::json>>(a_data);

		if (a_key.starts_with(REX::Json::KEY_SEPARATOR)) {
			root.get()[nlohmann::json::json_pointer(a_key)] = std::forward<T>(a_value);
		}
		else {
			root.get()[a_key] = std::forward<T>(a_value);
		}

		return true;
	}

	template bool SaveSetting<bool&&>(const std::any&, const key_t&, bool&&);
	template bool SaveSetting<std::int8_t&>(const std::any&, const key_t&, std::int8_t&);
	template bool SaveSetting<std::uint8_t&>(const std::any&, const key_t&, std::uint8_t&);
	template bool SaveSetting<std::int16_t&>(const std::any&, const key_t&, std::int16_t&);
	template bool SaveSetting<std::uint16_t&>(const std::any&, const key_t&, std::uint16_t&);
	template bool SaveSetting<std::int32_t&>(const std::any&, const key_t&, std::int32_t&);
	template bool SaveSetting<std::uint32_t&>(const std::any&, const key_t&, std::uint32_t&);
	template bool SaveSetting<std::int64_t&>(const std::any&, const key_t&, std::int64_t&);
	template bool SaveSetting<std::uint64_t&>(const std::any&, const key_t&, std::uint64_t&);
	template bool SaveSetting<REX::Float32&>(const std::any&, const key_t&, REX::Float32&);
	template bool SaveSetting<REX::Float64&>(const std::any&, const key_t&, REX::Float64&);
	template bool SaveSetting<REX::Float128&>(const std::any&, const key_t&, REX::Float128&);
	template bool SaveSetting<std::string&>(const std::any&, const key_t&, std::string&);
	template bool SaveSetting<std::filesystem::path&>(const std::any&, const key_t&, std::filesystem::path&);
	template bool SaveSetting<nlohmann::json&>(const std::any&, const key_t&, nlohmann::json&);
	template bool SaveSetting<std::vector<bool>&>(const std::any&, const key_t&, std::vector<bool>&);
	template bool SaveSetting<std::vector<std::int8_t>&>(const std::any&, const key_t&, std::vector<std::int8_t>&);
	template bool SaveSetting<std::vector<std::uint8_t>&>(const std::any&, const key_t&, std::vector<std::uint8_t>&);
	template bool SaveSetting<std::vector<std::int16_t>&>(const std::any&, const key_t&, std::vector<std::int16_t>&);
	template bool SaveSetting<std::vector<std::uint16_t>&>(const std::any&, const key_t&, std::vector<std::uint16_t>&);
	template bool SaveSetting<std::vector<std::int32_t>&>(const std::any&, const key_t&, std::vector<std::int32_t>&);
	template bool SaveSetting<std::vector<std::uint32_t>&>(const std::any&, const key_t&, std::vector<std::uint32_t>&);
	template bool SaveSetting<std::vector<std::int64_t>&>(const std::any&, const key_t&, std::vector<std::int64_t>&);
	template bool SaveSetting<std::vector<std::uint64_t>&>(const std::any&, const key_t&, std::vector<std::uint64_t>&);
	template bool SaveSetting<std::vector<REX::Float32>&>(const std::any&, const key_t&, std::vector<REX::Float32>&);
	template bool SaveSetting<std::vector<REX::Float64>&>(const std::any&, const key_t&, std::vector<REX::Float64>&);
	template bool SaveSetting<std::vector<REX::Float128>&>(const std::any&, const key_t&, std::vector<REX::Float128>&);
	template bool SaveSetting<std::vector<std::string>&>(const std::any&, const key_t&, std::vector<std::string>&);
	template bool SaveSetting<std::vector<std::filesystem::path>&>(const std::any&, const key_t&, std::vector<std::filesystem::path>&);
	template bool SaveSetting<std::vector<nlohmann::json>&>(const std::any&, const key_t&, std::vector<nlohmann::json>&);
}

namespace REX::Json
{
	bool SettingStore::Load()
	{
		const auto doLoad = [this](const std::filesystem::path& a_path, bool a_isMain) -> std::optional<std::string> {
			if (a_path.empty()) {
				return std::nullopt;
			}

			auto root = nlohmann::json();

			try {
				auto fileStream = std::fstream(a_path, std::ios::in);
				fileStream.exceptions(std::ios::failbit | std::ios::badbit);

				auto fileContent = std::string{ std::istreambuf_iterator<char>(fileStream), std::istreambuf_iterator<char>() };
				root = nlohmann::json::parse(std::move(fileContent),
					REX::Json::GetParserCallback<nlohmann::json>(),
					REX::Json::ALLOW_EXCEPTIONS,
					REX::Json::IGNORE_COMMENTS);
			}
			catch (const std::ios::failure& error) {
				return error.what();
			}
			catch (const nlohmann::json::exception& error) {
				return error.what();
			}

			for (const auto& setting : _settings) {
				std::ignore = setting->Load(std::ref(root), a_isMain);
			}

			return std::nullopt;
		};

		const auto loadError = doLoad(_mainPath, true);
		if (loadError) [[unlikely]] {
			REX::LogError(R"(Failed to load settings from "{}": {})"sv,
				_mainPath.generic_string(), *loadError);
			return false;
		}

		std::ignore = doLoad(_customPath, false);
		return true;
	}

	bool SettingStore::Save()
	{
		const auto doSave = [this](const std::filesystem::path& a_path) -> std::optional<std::string> {
			if (a_path.empty()) {
				return std::nullopt;
			}

			auto output = nlohmann::json();

			try {
				auto fileStream = std::fstream(a_path, std::ios::in);
				fileStream.exceptions(std::ios::failbit | std::ios::badbit);

				auto fileContent = std::string{ std::istreambuf_iterator<char>(fileStream), std::istreambuf_iterator<char>() };
				output = nlohmann::json::parse(std::move(fileContent),
					REX::Json::GetParserCallback<nlohmann::json>(),
					REX::Json::ALLOW_EXCEPTIONS,
					REX::Json::IGNORE_COMMENTS);
			}
			catch (const std::ios::failure& error) {
				std::ignore = error;
			}
			catch (const nlohmann::json::exception& error) {
				std::ignore = error;
			}

			for (const auto& setting : _settings) {
				std::ignore = setting->Save(std::ref(output));
			}

			try {
				REX::CreateParentDirectories(a_path);
			}
			catch (const std::filesystem::filesystem_error& error) {
				return error.what();
			}

			try {
				auto fileStream = std::fstream(a_path, std::ios::out | std::ios::trunc);
				fileStream.exceptions(std::ios::failbit | std::ios::badbit);

				auto fileOutput = output.dump(
					REX::Json::INDENT_COUNT,
					REX::Json::INDENT_CHAR,
					REX::Json::ENSURE_ASCII,
					REX::Json::ERROR_HANDLER<nlohmann::json>);
				REX::Print(fileStream, "{}"sv, std::move(fileOutput));

				return std::nullopt;
			}
			catch (const std::ios::failure& error) {
				return error.what();
			}
			catch (const nlohmann::json::exception& error) {
				return error.what();
			}
		};

		const auto saveError = doSave(_mainPath);
		if (saveError) [[unlikely]] {
			REX::LogError(R"(Failed to save settings to "{}": {})"sv,
				_mainPath.generic_string(), *saveError);
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
