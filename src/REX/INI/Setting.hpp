#pragma once

#if (COMMONLIB_FEATURE_INI == 1)

#include "REX/Error.hpp"
#include "REX/INI/Utility.hpp"
#include "REX/Setting.hpp"

namespace REX::INI
{
	template <class T>
		requires(REX::INI::ReadWritable<T, REX::INI::EntryType>)
	class Setting final : public REX::Setting<T, REX::INI::EntryType>
	{
	private:
		using super = REX::Setting<T, REX::INI::EntryType>;

	public:
		using typename super::value_type;
		using typename super::entry_type;

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
			auto newValue = REX::INI::GetValue<T>(a_parent.first.get(), a_parent.second, this->_key);
			if (!newValue.has_value()) {
				if (newValue.error() == REX::PosixErrorCode::invalid_argument) [[likely]] {
					return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
				}

				this->_value = this->_defaultValue;
				return REX::CreateSystemError(REX::PosixErrorCode::bad_message);
			}

			this->_value = std::move(newValue->value);
			return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
		}

		auto SaveEntry(entry_type& a_parent) const -> REX::SystemError override
		{
			if (!REX::INI::SetValue<T>(a_parent.first.get(), a_parent.second, this->_key, this->_value)) [[unlikely]] {
				return REX::CreateSystemError(REX::PosixErrorCode::bad_message);
			}

			return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
		}

	private:
		std::string _key;
	};
}

#endif
