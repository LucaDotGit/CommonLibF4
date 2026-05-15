#pragma once

#if COMMONLIB_OPTION_TOML == 1

#include "REX/Format.hpp"
#include "REX/Setting.hpp"
#include "REX/SettingStore.hpp"

#include <toml.hpp>

namespace REX::Toml
{
	using sec_t = std::string;
	using key_t = std::string;
}

namespace REX::Toml::Impl
{
	template <class T>
	bool LoadSetting(const std::any& a_data, const sec_t& a_section, const key_t& a_key, T& a_value, const T& a_defaultValue);

	template <class T>
	bool SaveSetting(const std::any& a_data, const sec_t& a_section, const key_t& a_key, T&& a_value);
}

namespace REX::Toml
{
	class SettingStore final
		: public REX::SettingStore<SettingStore>
	{
	public:
		explicit SettingStore(std::filesystem::path a_mainPath)
			: REX::SettingStore<SettingStore>(std::move(a_mainPath))
		{
		}

		explicit SettingStore(std::filesystem::path a_mainPath, std::filesystem::path a_customPath)
			: REX::SettingStore<SettingStore>(std::move(a_mainPath), std::move(a_customPath))
		{
		}

		~SettingStore() noexcept override = default;

		SettingStore(const SettingStore&) = default;
		SettingStore(SettingStore&&) noexcept = default;

		SettingStore& operator=(const SettingStore&) = default;
		SettingStore& operator=(SettingStore&&) noexcept = default;

		bool Load() override;
		bool Save() override;
	};

	template <class T>
	class Setting final
		: public REX::Setting<T, SettingStore>
	{
	public:
		explicit Setting(sec_t a_section, key_t a_key)
			: REX::Setting<T, SettingStore>(),
			  _section(std::move(a_section)),
			  _key(std::move(a_key))
		{
		}

		explicit Setting(sec_t a_section, key_t a_key, T a_defaultValue)
			: REX::Setting<T, SettingStore>(std::move(a_defaultValue)),
			  _section(std::move(a_section)),
			  _key(std::move(a_key))
		{
		}

		~Setting() noexcept override = default;

		Setting(const Setting&) = delete;
		Setting(Setting&&) = delete;

		Setting& operator=(const Setting&) = delete;
		Setting& operator=(Setting&&) = delete;

		[[nodiscard]] const sec_t& GetSection() const noexcept { return _section; }
		[[nodiscard]] const key_t& GetKey() const noexcept { return _key; }

		bool Load(const std::any& a_data, bool a_isMain) override
		{
			if (!a_isMain) {
				return Impl::LoadSetting(a_data, _section, _key, this->_value, this->_defaultValue);
			}

			if (!Impl::LoadSetting(a_data, _section, _key, this->_defaultValue, this->_defaultValue)) {
				return false;
			}

			this->SetValue(this->_defaultValue);
			return true;
		}

		bool Save(const std::any& a_data) override
		{
			return Impl::SaveSetting(a_data, _section, _key, this->_value);
		}

		[[nodiscard]] std::string ToString() const
			requires(REX::formattable<T>)
		{
			return REX::Format("[{}:{} = {}]"sv, _section, _key, this->_value);
		}

	private:
		sec_t _section;
		key_t _key;
	};

	extern template class Setting<bool>;
	extern template class Setting<std::int8_t>;
	extern template class Setting<std::uint8_t>;
	extern template class Setting<std::int16_t>;
	extern template class Setting<std::uint16_t>;
	extern template class Setting<std::int32_t>;
	extern template class Setting<std::uint32_t>;
	extern template class Setting<std::int64_t>;
	extern template class Setting<std::uint64_t>;
	extern template class Setting<REX::Float32>;
	extern template class Setting<REX::Float64>;
	extern template class Setting<REX::Float128>;
	extern template class Setting<std::string>;
	extern template class Setting<std::filesystem::path>;
	extern template class Setting<toml::value>;
	extern template class Setting<std::vector<bool>>;
	extern template class Setting<std::vector<std::int8_t>>;
	extern template class Setting<std::vector<std::uint8_t>>;
	extern template class Setting<std::vector<std::int16_t>>;
	extern template class Setting<std::vector<std::uint16_t>>;
	extern template class Setting<std::vector<std::int32_t>>;
	extern template class Setting<std::vector<std::uint32_t>>;
	extern template class Setting<std::vector<std::int64_t>>;
	extern template class Setting<std::vector<std::uint64_t>>;
	extern template class Setting<std::vector<REX::Float32>>;
	extern template class Setting<std::vector<REX::Float64>>;
	extern template class Setting<std::vector<REX::Float128>>;
	extern template class Setting<std::vector<std::string>>;
	extern template class Setting<std::vector<std::filesystem::path>>;
	extern template class Setting<std::vector<toml::value>>;

	using Bool = Setting<bool>;
	using Int8 = Setting<std::int8_t>;
	using UInt8 = Setting<std::uint8_t>;
	using Int16 = Setting<std::int16_t>;
	using UInt16 = Setting<std::uint16_t>;
	using Int32 = Setting<std::int32_t>;
	using UInt32 = Setting<std::uint32_t>;
	using Int64 = Setting<std::int64_t>;
	using UInt64 = Setting<std::uint64_t>;
	using Offset = Setting<std::ptrdiff_t>;
	using Size = Setting<std::size_t>;
	using Float32 = Setting<REX::Float32>;
	using Float64 = Setting<REX::Float64>;
	using Float128 = Setting<REX::Float128>;
	using String = Setting<std::string>;
	using Path = Setting<std::filesystem::path>;
	using Value = Setting<toml::value>;
	using BoolArray = Setting<std::vector<bool>>;
	using Int8Array = Setting<std::vector<std::int8_t>>;
	using UInt8Array = Setting<std::vector<std::uint8_t>>;
	using Int16Array = Setting<std::vector<std::int16_t>>;
	using UInt16Array = Setting<std::vector<std::uint16_t>>;
	using Int32Array = Setting<std::vector<std::int32_t>>;
	using UInt32Array = Setting<std::vector<std::uint32_t>>;
	using Int64Array = Setting<std::vector<std::int64_t>>;
	using UInt64Array = Setting<std::vector<std::uint64_t>>;
	using OffsetArray = Setting<std::vector<std::ptrdiff_t>>;
	using SizeArray = Setting<std::vector<std::size_t>>;
	using F32Array = Setting<std::vector<REX::Float32>>;
	using F64Array = Setting<std::vector<REX::Float64>>;
	using F128Array = Setting<std::vector<REX::Float128>>;
	using StringArray = Setting<std::vector<std::string>>;
	using PathArray = Setting<std::vector<std::filesystem::path>>;
	using ValueArray = Setting<std::vector<toml::value>>;
}

#if __cpp_lib_format > 0l
namespace std
{
	template <class T>
	struct formatter<REX::Toml::Setting<T>>
		: public formatter<T>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const REX::Toml::Setting<T>& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, a_value.ToString());
		}
	};

	extern template struct formatter<REX::Toml::Setting<bool>>;
	extern template struct formatter<REX::Toml::Setting<std::int8_t>>;
	extern template struct formatter<REX::Toml::Setting<std::uint8_t>>;
	extern template struct formatter<REX::Toml::Setting<std::int16_t>>;
	extern template struct formatter<REX::Toml::Setting<std::uint16_t>>;
	extern template struct formatter<REX::Toml::Setting<std::int32_t>>;
	extern template struct formatter<REX::Toml::Setting<std::uint32_t>>;
	extern template struct formatter<REX::Toml::Setting<std::int64_t>>;
	extern template struct formatter<REX::Toml::Setting<std::uint64_t>>;
	extern template struct formatter<REX::Toml::Setting<REX::Float32>>;
	extern template struct formatter<REX::Toml::Setting<REX::Float64>>;
	extern template struct formatter<REX::Toml::Setting<REX::Float128>>;
	extern template struct formatter<REX::Toml::Setting<std::string>>;
	extern template struct formatter<REX::Toml::Setting<std::filesystem::path>>;
	extern template struct formatter<REX::Toml::Setting<toml::value>>;
	extern template struct formatter<REX::Toml::Setting<std::vector<bool>>>;
	extern template struct formatter<REX::Toml::Setting<std::vector<std::int8_t>>>;
	extern template struct formatter<REX::Toml::Setting<std::vector<std::uint8_t>>>;
	extern template struct formatter<REX::Toml::Setting<std::vector<std::int16_t>>>;
	extern template struct formatter<REX::Toml::Setting<std::vector<std::uint16_t>>>;
	extern template struct formatter<REX::Toml::Setting<std::vector<std::int32_t>>>;
	extern template struct formatter<REX::Toml::Setting<std::vector<std::uint32_t>>>;
	extern template struct formatter<REX::Toml::Setting<std::vector<std::int64_t>>>;
	extern template struct formatter<REX::Toml::Setting<std::vector<std::uint64_t>>>;
	extern template struct formatter<REX::Toml::Setting<std::vector<REX::Float32>>>;
	extern template struct formatter<REX::Toml::Setting<std::vector<REX::Float64>>>;
	extern template struct formatter<REX::Toml::Setting<std::vector<REX::Float128>>>;
	extern template struct formatter<REX::Toml::Setting<std::vector<std::string>>>;
	extern template struct formatter<REX::Toml::Setting<std::vector<std::filesystem::path>>>;
	extern template struct formatter<REX::Toml::Setting<std::vector<toml::value>>>;
}
#endif

#if FMT_VERSION > 0l
namespace fmt
{
	template <class T>
	struct formatter<REX::Toml::Setting<T>>
		: public formatter<T>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const REX::Toml::Setting<T>& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, a_value.ToString());
		}
	};

	extern template struct formatter<REX::Toml::Setting<bool>>;
	extern template struct formatter<REX::Toml::Setting<std::int8_t>>;
	extern template struct formatter<REX::Toml::Setting<std::uint8_t>>;
	extern template struct formatter<REX::Toml::Setting<std::int16_t>>;
	extern template struct formatter<REX::Toml::Setting<std::uint16_t>>;
	extern template struct formatter<REX::Toml::Setting<std::int32_t>>;
	extern template struct formatter<REX::Toml::Setting<std::uint32_t>>;
	extern template struct formatter<REX::Toml::Setting<std::int64_t>>;
	extern template struct formatter<REX::Toml::Setting<std::uint64_t>>;
	extern template struct formatter<REX::Toml::Setting<REX::Float32>>;
	extern template struct formatter<REX::Toml::Setting<REX::Float64>>;
	extern template struct formatter<REX::Toml::Setting<REX::Float128>>;
	extern template struct formatter<REX::Toml::Setting<std::string>>;
	extern template struct formatter<REX::Toml::Setting<std::filesystem::path>>;
	extern template struct formatter<REX::Toml::Setting<toml::value>>;
	extern template struct formatter<REX::Toml::Setting<std::vector<bool>>>;
	extern template struct formatter<REX::Toml::Setting<std::vector<std::int8_t>>>;
	extern template struct formatter<REX::Toml::Setting<std::vector<std::uint8_t>>>;
	extern template struct formatter<REX::Toml::Setting<std::vector<std::int16_t>>>;
	extern template struct formatter<REX::Toml::Setting<std::vector<std::uint16_t>>>;
	extern template struct formatter<REX::Toml::Setting<std::vector<std::int32_t>>>;
	extern template struct formatter<REX::Toml::Setting<std::vector<std::uint32_t>>>;
	extern template struct formatter<REX::Toml::Setting<std::vector<std::int64_t>>>;
	extern template struct formatter<REX::Toml::Setting<std::vector<std::uint64_t>>>;
	extern template struct formatter<REX::Toml::Setting<std::vector<REX::Float32>>>;
	extern template struct formatter<REX::Toml::Setting<std::vector<REX::Float64>>>;
	extern template struct formatter<REX::Toml::Setting<std::vector<REX::Float128>>>;
	extern template struct formatter<REX::Toml::Setting<std::vector<std::string>>>;
	extern template struct formatter<REX::Toml::Setting<std::vector<std::filesystem::path>>>;
	extern template struct formatter<REX::Toml::Setting<std::vector<toml::value>>>;
}
#endif
#endif
