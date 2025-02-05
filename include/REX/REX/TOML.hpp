#pragma once

#ifdef REX_OPTION_TOML

#include "REX/REX/Setting.hpp"

namespace REX::TOML
{
	using sec_t = std::vector<std::string>;
	using key_t = std::string_view;

	namespace Impl
	{
		template <class T>
		void SettingLoad(void* a_file, sec_t a_section, key_t a_key, T& a_value, T& a_valueDefault);

		template <class T>
		void SettingSave(void* a_file, sec_t a_section, key_t a_key, T&& a_value);
	}

	class SettingStore
		: public TSettingStore<SettingStore>
	{
	public:
		virtual void Load() override;
		virtual void Save() override;
	};

	template <class T, class Store = SettingStore>
	class Setting
		: public TSetting<T, Store>
	{
	public:
		Setting(key_t a_key, T a_default) :
			TSetting<T, Store>(a_default),
			m_section(),
			m_key(a_key)
		{
		}

		Setting(std::string_view a_section, key_t a_key, T a_default) noexcept :
			TSetting<T, Store>(a_default),
			m_section(),
			m_key(a_key)
		{
			for (const auto token : std::ranges::split_view{ a_section, std::string_view{ "." } }) {
				m_section.emplace_back(token.data(), token.size());
			}
		}

		Setting(std::initializer_list<std::string> a_section, key_t a_key, T a_default) noexcept :
			TSetting<T, Store>(a_default),
			m_section(a_section),
			m_key(a_key)
		{
		}

	public:
		[[nodiscard]] const sec_t& GetSection() const noexcept { return m_section; }
		[[nodiscard]] const key_t& GetKey() const noexcept { return m_key; }

	public:
		virtual void Load(void* a_data, bool a_isBase) override
		{
			if (a_isBase) {
				Impl::SettingLoad(a_data, m_section, m_key, this->m_valueDefault, this->m_valueDefault);
				this->SetValue(this->m_valueDefault);
			}
			else {
				Impl::SettingLoad(a_data, m_section, m_key, this->m_value, this->m_valueDefault);
			}
		}

		virtual void Save(void* a_data) override
		{
			Impl::SettingSave(a_data, m_section, m_key, this->m_value);
		}

	private:
		sec_t m_section;
		key_t m_key;
	};

	template <class Store = SettingStore>
	using Bool = Setting<bool, Store>;

	template <class Store = SettingStore>
	using F32 = Setting<float, Store>;

	template <class Store = SettingStore>
	using F64 = Setting<double, Store>;

	template <class Store = SettingStore>
	using I8 = Setting<std::int8_t, Store>;

	template <class Store = SettingStore>
	using I16 = Setting<std::int16_t, Store>;

	template <class Store = SettingStore>
	using I32 = Setting<std::int32_t, Store>;

	template <class Store = SettingStore>
	using U8 = Setting<std::uint8_t, Store>;

	template <class Store = SettingStore>
	using U16 = Setting<std::uint16_t, Store>;

	template <class Store = SettingStore>
	using U32 = Setting<std::uint32_t, Store>;

	template <class Store = SettingStore>
	using Str = Setting<std::string, Store>;
}

namespace std
{
	template <class T, class S>
	struct formatter<REX::TOML::Setting<T, S>>
		: public formatter<T>
	{
		constexpr auto parse(format_parse_context& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		constexpr auto format(const REX::TOML::Setting<T, S>& a_setting, FormatContext& a_ctx) const
		{
			return formatter<T>::format(a_setting.GetValue(), a_ctx);
		}
	};
}

#ifdef FMT_VERSION
namespace fmt
{
	template <class T, class S>
	struct formatter<REX::TOML::Setting<T, S>>
		: public formatter<T>
	{
		constexpr auto parse(format_parse_context& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		constexpr auto format(const REX::TOML::Setting<T, S>& a_setting, FormatContext& a_ctx) const
		{
			return formatter<T>::format(a_setting.GetValue(), a_ctx);
		}
	};
}
#endif
#endif
