#include "REX/INI/SettingFile.hpp"

#if (COMMONLIB_FEATURE_INI == 1)

#include "REX/Error.hpp"
#include "REX/INI/Utility.hpp"
#include "REX/IO.hpp"

namespace REX::INI
{
	auto SettingFile::LoadEntry(const entry_type& a_parent) -> REX::SystemError
	{
		for (auto&& [_, value] : _settings) {
			const auto loadError = value->LoadEntry(a_parent);
			if (loadError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
				return loadError;
			}
		}

		return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
	}

	auto SettingFile::SaveEntry(entry_type& a_parent) const -> REX::SystemError
	{
		for (auto&& [_, value] : _settings) {
			const auto saveError = value->SaveEntry(a_parent);
			if (saveError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
				return saveError;
			}
		}

		return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
	}

	auto SettingFile::Load() -> REX::SystemError
	{
		auto entryRoot = entry_type::first_type::type();
		REX::INI::Setup(entryRoot, REX::INI::DEFAULT_OPTIONS);

		const auto fileContent = REX::ReadAllTextFromFile<char>(_filePath);
		if (!fileContent.has_value()) {
			return fileContent.error();
		}

		const auto loadError = REX::INI::CreatePosixError(entryRoot.LoadData(fileContent.value()));
		if (loadError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return REX::CreateSystemError(loadError.value());
		}

		{
			auto tempEntryPair = entry_type{std::ref(entryRoot), std::string_view()};
			return LoadEntry(tempEntryPair);
		}
	}

	auto SettingFile::Save() const -> REX::SystemError
	{
		auto entryRoot = entry_type::first_type::type();
		REX::INI::Setup(entryRoot, REX::INI::DEFAULT_OPTIONS);

		{
			auto tempEntryPair = entry_type{std::ref(entryRoot), std::string_view()};

			const auto saveValueError = SaveEntry(tempEntryPair);
			if (saveValueError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
				return saveValueError;
			}
		}

		auto fileOutput = std::string();

		const auto saveError =
			REX::INI::CreatePosixError(entryRoot.Save(fileOutput, REX::INI::DEFAULT_OPTIONS.prependBom));
		if (saveError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return REX::CreateSystemError(saveError.value());
		}

		return REX::WriteAllTextToFile<char>(_filePath, fileOutput);
	}
}

#endif
