#pragma once

#include "F4SE/Core.hpp"

namespace REX
{
	class Version;
}

namespace F4SE
{
	class PluginInfo final
	{
	public:
		inline static constexpr auto DATA_VERSION = static_cast<F4SE::DataVersion>(1);

		constexpr PluginInfo() noexcept = default;
		constexpr ~PluginInfo() noexcept = default;

		constexpr PluginInfo(const PluginInfo&) noexcept = default;
		constexpr PluginInfo(PluginInfo&&) noexcept = default;

		constexpr auto operator=(const PluginInfo&) noexcept -> PluginInfo& = default;
		constexpr auto operator=(PluginInfo&&) noexcept -> PluginInfo& = default;

		[[nodiscard]]
		constexpr auto GetDataVersion() const noexcept -> F4SE::DataVersion
		{
			return _dataVersion;
		}

		constexpr void SetDataVersion(F4SE::DataVersion a_version) noexcept
		{
			_dataVersion = a_version;
		}

		[[nodiscard]]
		constexpr auto GetPluginName() const noexcept -> std::string_view
		{
			return _pluginName;
		}

		constexpr void SetPluginName(std::string_view a_plugin) noexcept
		{
			_pluginName = a_plugin.data();
		}

		[[nodiscard]]
		constexpr auto GetPluginVersion() const noexcept -> REX::Version
		{
			return REX::Version::Unpack(_pluginVersion);
		}

		constexpr void SetPluginVersion(REX::Version a_version) noexcept
		{
			_pluginVersion = a_version.Pack<std::uint32_t>();
		}

		[[nodiscard]]
		constexpr auto GetPluginVersionNumber() const noexcept -> std::uint32_t
		{
			return _pluginVersion;
		}

		constexpr void SetPluginVersionNumber(std::uint32_t a_version) noexcept
		{
			_pluginVersion = a_version;
		}

	private:
		// members
		F4SE::DataVersion _dataVersion{DATA_VERSION}; // 0x00
		const char* _pluginName{nullptr};			  // 0x08
		std::uint32_t _pluginVersion{0};			  // 0x10
	};

	static_assert(sizeof(PluginInfo) == 0x18);
}
