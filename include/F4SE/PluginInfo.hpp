#pragma once

#include "REX/Version.hpp"

namespace F4SE
{
	class PluginInfo final
	{
	public:
		inline static constexpr auto DATA_VERSION{ 1ui32 };

		constexpr PluginInfo() noexcept = default;
		constexpr ~PluginInfo() noexcept = default;

		constexpr PluginInfo(const PluginInfo&) noexcept = default;
		constexpr PluginInfo(PluginInfo&&) noexcept = default;

		constexpr PluginInfo& operator=(const PluginInfo&) noexcept = default;
		constexpr PluginInfo& operator=(PluginInfo&&) noexcept = default;

		[[nodiscard]] constexpr std::uint32_t GetDataVersion() const noexcept { return _dataVersion; }
		constexpr void SetDataVersion(std::uint32_t a_version) noexcept { _dataVersion = a_version; }

		[[nodiscard]] constexpr std::string_view GetPluginName() const noexcept { return _pluginName; }
		constexpr void SetPluginName(std::string_view a_plugin) noexcept { _pluginName = a_plugin.data(); }

		[[nodiscard]] constexpr REX::Version GetPluginVersion() const noexcept { return REX::Version::Unpack(_pluginVersion); }
		constexpr void SetPluginVersion(REX::Version a_version) noexcept { _pluginVersion = a_version.Pack<std::uint32_t>(); }

		[[nodiscard]] constexpr std::uint32_t GetPluginVersionNumber() const noexcept { return _pluginVersion; }
		constexpr void SetPluginVersionNumber(std::uint32_t a_version) noexcept { _pluginVersion = a_version; }

	private:
		// members
		std::uint32_t _dataVersion{ DATA_VERSION }; // 00
		const char* _pluginName{ nullptr };			// 08
		std::uint32_t _pluginVersion{ 0 };			// 10
	};
	static_assert(sizeof(PluginInfo) == 0x18);
}
