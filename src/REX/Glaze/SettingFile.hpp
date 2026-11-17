#pragma once

#if __has_include(<glaze/glaze.hpp>)

#include "REX/Error.hpp"
#include "REX/Glaze/Utility.hpp"
#include "REX/IO.hpp"
#include "REX/SettingFile.hpp"

namespace REX::Glaze
{
	template <auto Options, glz::num_mode NumberMode, template <class> class MapType = REX::Glaze::MapType>
		requires(REX::Glaze::GenericReadWritable<Options, NumberMode, MapType>)
	class SettingFile final : public REX::SettingFile<glz::generic_json<NumberMode, MapType>>
	{
	private:
		using super = REX::SettingFile<glz::generic_json<NumberMode, MapType>>;

	public:
		using entry_type = super::entry_type;

		explicit SettingFile(std::filesystem::path a_filePath) :
			super(std::move(a_filePath))
		{
		}

		~SettingFile() noexcept override = default;

		SettingFile(const SettingFile&) = delete;
		SettingFile(SettingFile&&) noexcept = default;

		auto operator=(const SettingFile&) -> SettingFile& = delete;
		auto operator=(SettingFile&&) noexcept -> SettingFile& = default;

		auto LoadEntry(const entry_type& a_parent) -> REX::SystemError override
		{
			if (!a_parent.is_object()) [[unlikely]] {
				return REX::CreateSystemError(REX::PosixErrorCode::bad_message);
			}

			for (auto&& [_, value] : this->_settings) {
				const auto loadError = value->LoadEntry(a_parent);
				if (loadError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
					return loadError;
				}
			}

			return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
		}

		auto SaveEntry(entry_type& a_parent) const -> REX::SystemError override
		{
			if (!a_parent.is_object()) [[unlikely]] {
				return REX::CreateSystemError(REX::PosixErrorCode::bad_message);
			}

			for (auto&& [_, value] : this->_settings) {
				const auto saveError = value->SaveEntry(a_parent);
				if (saveError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
					return saveError;
				}
			}

			return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
		}

		auto Load() -> REX::SystemError override
		{
			const auto fileContent = REX::ReadAllTextFromFile<char>(this->_filePath);
			if (!fileContent.has_value()) {
				return fileContent.error();
			}

			auto entryRoot = entry_type();

			const auto readError = glz::read<Options>(entryRoot, fileContent.value());
			if (readError.ec != glz::error_code::none) [[unlikely]] {
				return REX::CreateSystemError(REX::PosixErrorCode::bad_message);
			}

			return LoadEntry(entryRoot);
		}

		auto Save() const -> REX::SystemError override
		{
			auto entryRoot = entry_type();

			const auto saveValueError = SaveEntry(entryRoot);
			if (saveValueError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
				return saveValueError;
			}

			auto fileOutput = std::string();

			const auto writeError = glz::write<Options>(entryRoot, fileOutput);
			if (writeError.ec != glz::error_code::none) [[unlikely]] {
				return REX::CreateSystemError(REX::PosixErrorCode::bad_message);
			}

			return REX::WriteAllTextToFile<char>(this->_filePath, fileOutput);
		}
	};
}

#endif
