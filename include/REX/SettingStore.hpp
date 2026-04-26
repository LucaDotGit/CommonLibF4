#pragma once

#include "REX/NotNull.hpp"
#include "REX/Setting.hpp"

namespace REX
{
	class ISettingStore
	{
	public:
		virtual ~ISettingStore() noexcept = default;

		[[nodiscard]] virtual auto GetMainPath() const noexcept -> const std::filesystem::path& = 0;
		[[nodiscard]] virtual auto GetCustomPath() const noexcept -> const std::filesystem::path& = 0;
		[[nodiscard]] virtual auto GetSettings() const noexcept -> std::span<const REX::NotNull<std::shared_ptr<ISetting>>> = 0;

		virtual void Add(REX::NotNull<std::shared_ptr<ISetting>> a_setting) = 0;
		virtual void AddRange(std::span<const REX::NotNull<std::shared_ptr<ISetting>>> a_settings) = 0;
		virtual void AddRange(std::initializer_list<const REX::NotNull<std::shared_ptr<ISetting>>> a_settings) = 0;
		virtual void Clear() noexcept = 0;

		virtual bool Load() = 0;
		virtual bool Save() = 0;
	};

	template <class T>
	class SettingStore
		: public ISettingStore
	{
	public:
		using value_type = T;

		explicit SettingStore(std::filesystem::path a_mainPath)
			: _mainPath(std::move(a_mainPath))
		{
		}

		explicit SettingStore(std::filesystem::path a_mainPath, std::filesystem::path a_customPath)
			: _mainPath(std::move(a_mainPath)),
			  _customPath(std::move(a_customPath))
		{
		}

		~SettingStore() noexcept override = default;

		SettingStore(const SettingStore&) = default;
		SettingStore(SettingStore&&) noexcept = default;

		SettingStore& operator=(const SettingStore&) = default;
		SettingStore& operator=(SettingStore&&) noexcept = default;

		[[nodiscard]] auto GetMainPath() const noexcept -> const std::filesystem::path& override { return _mainPath; }
		[[nodiscard]] auto GetCustomPath() const noexcept -> const std::filesystem::path& override { return _customPath; }
		[[nodiscard]] auto GetSettings() const noexcept -> std::span<const REX::NotNull<std::shared_ptr<ISetting>>> override { return _settings; }

		void Add(REX::NotNull<std::shared_ptr<ISetting>> a_setting) override
		{
			_settings.push_back(std::move(a_setting));
		}

		void AddRange(std::span<const REX::NotNull<std::shared_ptr<ISetting>>> a_settings) override
		{
			_settings.reserve(_settings.size() + a_settings.size());

			for (const auto& setting : a_settings) {
				_settings.push_back(setting);
			}
		}

		void AddRange(std::initializer_list<const REX::NotNull<std::shared_ptr<ISetting>>> a_settings) override
		{
			AddRange(std::span(a_settings));
		}

		void Clear() noexcept override
		{
			_settings.clear();
		}

	protected:
		std::filesystem::path _mainPath;
		std::filesystem::path _customPath;
		std::vector<REX::NotNull<std::shared_ptr<ISetting>>> _settings;
	};
}
