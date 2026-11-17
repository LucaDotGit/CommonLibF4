#pragma once

#if __has_include(<glaze/glaze.hpp>)

#include "REX/Error.hpp"
#include "REX/Glaze/Utility.hpp"
#include "REX/Setting.hpp"

namespace REX::Glaze
{
	template <class T, auto Options, glz::num_mode NumberMode, template <class> class MapType = REX::Glaze::MapType>
		requires(REX::Glaze::ReadWritable<T, Options>)
	class Setting final : public REX::Setting<T, glz::generic_json<NumberMode, MapType>>
	{
	private:
		using super = REX::Setting<T, glz::generic_json<NumberMode, MapType>>;

	public:
		using value_type = super::value_type;
		using entry_type = super::entry_type;

		explicit Setting(std::string a_key) noexcept :
			_key(std::move(a_key))
		{
		}

		explicit Setting(std::string a_key, value_type a_defaultValue) noexcept :
			super(std::move(a_defaultValue)),
			_key(std::move(a_key))
		{
		}

		~Setting() noexcept override = default;

		Setting(const Setting&) = delete;
		Setting(Setting&&) noexcept = default;

		auto operator=(const Setting&) -> Setting& = delete;
		auto operator=(Setting&&) noexcept -> Setting& = default;

		[[nodiscard]]
		auto GetKey() const noexcept -> std::string_view override
		{
			return _key;
		}

		auto LoadEntry(const entry_type& a_parent) -> REX::SystemError override
		{
			if (!a_parent.is_object()) [[unlikely]] {
				this->_value = this->_defaultValue;
				return REX::CreateSystemError(REX::PosixErrorCode::bad_message);
			}

			const auto& parentObject = a_parent.get_object();

			const auto keyIt = parentObject.find(this->_key);
			if (keyIt == parentObject.end()) {
				return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
			}

			const auto& currentObject = keyIt->second;

			auto objectBuffer = std::string();

			const auto writeError = glz::write<Options>(currentObject, objectBuffer);
			if (writeError != glz::error_code::none) [[unlikely]] {
				this->_value = this->_defaultValue;
				return REX::CreateSystemError(REX::PosixErrorCode::bad_message);
			}

			auto newValue = T();

			const auto readError = glz::read<Options>(newValue, objectBuffer);
			if (readError != glz::error_code::none) [[unlikely]] {
				this->_value = this->_defaultValue;
				return REX::CreateSystemError(REX::PosixErrorCode::bad_message);
			}

			this->_value = std::move(newValue);
			return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
		}

		auto SaveEntry(entry_type& a_parent) const -> REX::SystemError override
		{
			if (!a_parent.is_object()) [[unlikely]] {
				return REX::CreateSystemError(REX::PosixErrorCode::bad_message);
			}

			auto objectBuffer = std::string();

			const auto writeError = glz::write<Options>(this->_value, objectBuffer);
			if (writeError != glz::error_code::none) [[unlikely]] {
				return REX::CreateSystemError(REX::PosixErrorCode::bad_message);
			}

			auto& currentObject = a_parent.get_object()[this->_key];

			const auto readError = glz::read<Options>(currentObject, objectBuffer);
			if (readError != glz::error_code::none) [[unlikely]] {
				return REX::CreateSystemError(REX::PosixErrorCode::bad_message);
			}

			return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
		}

	private:
		std::string _key;
	};
}

#endif
