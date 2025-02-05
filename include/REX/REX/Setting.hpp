#pragma once

#include "REX/REX/Singleton.hpp"

namespace REX
{
	template <typename T>
	concept copyable = std::is_trivially_copyable_v<T> && std::is_trivially_copy_constructible_v<T>;

	class ISetting
	{
	public:
		virtual void Load(void* a_data, bool a_isBase) = 0;
		virtual void Save(void* a_data) = 0;
	};

	class ISettingStore
	{
	public:
		virtual void Init(std::string_view a_fileBase, std::string_view a_fileUser) = 0;
		virtual void Load() = 0;
		virtual void Save() = 0;
		virtual void Register(ISetting* a_setting) = 0;
	};

	template <class Value, class Store>
	class TSetting
		: public ISetting
	{
	public:
		using value_type = Value;
		using reference = Value&;
		using const_reference = const Value&;

		using store_type = Store;
		using setting_type = TSetting<Value, Store>;

	public:
		TSetting() noexcept = delete;

		TSetting(Value a_default) noexcept :
			m_value(a_default),
			m_valueDefault(a_default)
		{
			Store::GetSingleton()->Register(this);
		}

	public:
		template <typename T = std::conditional_t<copyable<Value>, value_type, const_reference>>
		[[nodiscard]] T GetValue() const noexcept { return m_value; }

		template <typename T = std::conditional_t<copyable<Value>, value_type, const_reference>>
		[[nodiscard]] T GetValueDefault() const noexcept { return m_valueDefault; }

		void SetValue(Value a_value) noexcept { m_value = a_value; }

	public:
		operator Value&() noexcept { return m_value; }
		operator const Value&() const noexcept { return m_value; }

	protected:
		Value m_value;
		Value m_valueDefault;
	};

	template <class T>
	class TSettingStore
		: public ISettingStore,
		  public Singleton<T>
	{
	public:
		using value_type = T;
		using setting_store_type = TSettingStore<T>;

	public:
		[[nodiscard]] const std::string_view& GetFileBase() const noexcept { return m_fileBase; }
		[[nodiscard]] const std::string_view& GetFileUser() const noexcept { return m_fileUser; }

	public:
		virtual void Init(std::string_view a_fileBase, std::string_view a_fileUser) noexcept override
		{
			m_fileBase = a_fileBase;
			m_fileUser = a_fileUser;
		}

		virtual void Register(ISetting* a_setting) override
		{
			m_settings.emplace_back(a_setting);
		}

	protected:
		std::string_view m_fileBase;
		std::string_view m_fileUser;
		std::vector<ISetting*> m_settings;
	};
}
