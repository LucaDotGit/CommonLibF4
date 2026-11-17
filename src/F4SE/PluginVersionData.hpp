#pragma once

#include "F4SE/Core.hpp"
#include "REL/Runtime.hpp"
#include "REX/Contract.hpp"
#include "REX/EnumSet.hpp"
#include "REX/Localization.hpp"
#include "REX/StaticString.hpp"
#include "REX/Version.hpp"

namespace F4SE
{
	// since F4SE v0.7.0
	class PluginVersionData final
	{
	public:
		inline static constexpr auto DATA_VERSION = static_cast<F4SE::DataVersion>(1);

		enum class AddressIndependence : std::uint32_t
		{
			None = 0,
			UseSignatureScanning = 1 << 0,
			UseAddressLibrary_RuntimeNG = 1 << 1,
			UseAddressLibrary_RuntimeAE = 1 << 2,

			UseAddressLibrary = UseAddressLibrary_RuntimeAE
		};

		enum class StructureIndependence : std::uint32_t
		{
			None = 0,
			UseNoStructs = 1 << 0,
			IsLayoutDependent_RuntimeNG = 1 << 1,
			IsLayoutDependent_RuntimeAE = 1 << 2,

			IsLayoutDependent = IsLayoutDependent_RuntimeAE
		};

		constexpr PluginVersionData() noexcept = default;
		constexpr ~PluginVersionData() noexcept = default;

		constexpr PluginVersionData(const PluginVersionData&) = delete;
		constexpr PluginVersionData(PluginVersionData&&) noexcept = default;

		constexpr auto operator=(const PluginVersionData&) -> PluginVersionData& = delete;
		constexpr auto operator=(PluginVersionData&&) noexcept -> PluginVersionData& = default;

		[[nodiscard]]
		static auto GetSingleton() noexcept -> const PluginVersionData&;

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

		[[nodiscard]]
		constexpr auto GetPluginName() const noexcept -> std::string_view
		{
			return _pluginName.data();
		}

		constexpr void SetPluginName(std::string_view a_name) noexcept
		{
			CopyBuffer(a_name, std::span(_pluginName));
		}

		[[nodiscard]]
		constexpr auto GetPluginAuthor() const noexcept -> std::string_view
		{
			return _pluginAuthor.data();
		}

		constexpr void SetPluginAuthor(std::string_view a_author) noexcept
		{
			CopyBuffer(a_author, std::span(_pluginAuthor));
		}

		[[nodiscard]]
		constexpr auto GetUseSignatureScanning() const noexcept -> bool
		{
			return _addressIndependence.any(AddressIndependence::UseSignatureScanning);
		}

		constexpr void SetUseSignatureScanning(bool a_value) noexcept
		{
			_addressIndependence.set(a_value, AddressIndependence::UseSignatureScanning);
		}

		[[nodiscard]]
		constexpr auto GetUseAddressLibrary_RuntimeNG() const noexcept -> bool
		{
			return _addressIndependence.any(AddressIndependence::UseAddressLibrary_RuntimeNG);
		}

		constexpr void SetUseAddressLibrary_RuntimeNG(bool a_value) noexcept
		{
			_addressIndependence.set(a_value, AddressIndependence::UseAddressLibrary_RuntimeNG);
		}

		[[nodiscard]]
		constexpr auto GetUseAddressLibrary_RuntimeAE() const noexcept -> bool
		{
			return _addressIndependence.any(AddressIndependence::UseAddressLibrary_RuntimeAE);
		}

		constexpr void SetUseAddressLibrary_RuntimeAE(bool a_value) noexcept
		{
			_addressIndependence.set(a_value, AddressIndependence::UseAddressLibrary_RuntimeAE);
		}

		[[nodiscard]]
		constexpr auto GetUseAddressLibrary() const noexcept -> bool
		{
			return _addressIndependence.any(AddressIndependence::UseAddressLibrary);
		}

		constexpr void SetUseAddressLibrary(bool a_value) noexcept
		{
			_addressIndependence.set(a_value, AddressIndependence::UseAddressLibrary);
		}

		[[nodiscard]]
		constexpr auto GetUseNoStructs() const noexcept -> bool
		{
			return _structureIndependence.any(StructureIndependence::UseNoStructs);
		}

		constexpr void SetUseNoStructs(bool a_value) noexcept
		{
			_structureIndependence.set(a_value, StructureIndependence::UseNoStructs);
		}

		[[nodiscard]]
		constexpr auto GetIsLayoutDependent_RuntimeNG() const noexcept -> bool
		{
			return _structureIndependence.any(StructureIndependence::IsLayoutDependent_RuntimeNG);
		}

		constexpr void SetIsLayoutDependent_RuntimeNG(bool a_value) noexcept
		{
			_structureIndependence.set(a_value, StructureIndependence::IsLayoutDependent_RuntimeNG);
		}

		[[nodiscard]]
		constexpr auto GetIsLayoutDependent_RuntimeAE() const noexcept -> bool
		{
			return _structureIndependence.any(StructureIndependence::IsLayoutDependent_RuntimeAE);
		}

		constexpr void SetIsLayoutDependent_RuntimeAE(bool a_value) noexcept
		{
			_structureIndependence.set(a_value, StructureIndependence::IsLayoutDependent_RuntimeAE);
		}

		[[nodiscard]]
		constexpr auto GetIsLayoutDependent() const noexcept -> bool
		{
			return _structureIndependence.any(StructureIndependence::IsLayoutDependent);
		}

		constexpr void SetIsLayoutDependent(bool a_value) noexcept
		{
			_structureIndependence.set(a_value, StructureIndependence::IsLayoutDependent);
		}

		[[nodiscard]]
		constexpr auto GetCompatibleVersions() const -> std::vector<REX::Version>
		{
			return std::ranges::views::transform(
					   _compatibleVersions,
					   [](std::uint32_t a_version) noexcept -> REX::Version {
						   return REX::Version::Unpack(a_version);
					   }) |
				   std::ranges::to<std::vector>();
		}

		constexpr void SetCompatibleVersions(std::span<const REX::Version> a_versions) noexcept
		{
			REX::Assert(a_versions.size() < _compatibleVersions.size() - 1);

			std::ranges::fill(_compatibleVersions, 0);
			std::ranges::transform(
				a_versions,
				_compatibleVersions.begin(),
				[](REX::Version a_version) noexcept -> std::uint32_t {
					return a_version.Pack<std::uint32_t>();
				});
		}

		constexpr void SetCompatibleVersions(std::span<const REL::Runtime> a_runtimes) noexcept
		{
			REX::Assert(a_runtimes.size() < _compatibleVersions.size() - 1);

			std::ranges::fill(_compatibleVersions, 0);
			std::ranges::transform(
				a_runtimes,
				_compatibleVersions.begin(),
				[](REL::Runtime a_version) noexcept -> std::uint32_t {
					return a_version.GetMinVersion().Pack<std::uint32_t>();
				});
		}

		constexpr void SetCompatibleVersions(std::initializer_list<REX::Version> a_versions) noexcept
		{
			const auto versionSpan = std::span<const REX::Version>(a_versions);
			SetCompatibleVersions(versionSpan);
		}

		constexpr void SetCompatibleVersions(std::initializer_list<REL::Runtime> a_runtimes) noexcept
		{
			const auto runtimeSpan = std::span<const REL::Runtime>(a_runtimes);
			SetCompatibleVersions(runtimeSpan);
		}

		[[nodiscard]]
		constexpr auto GetMinimumRequiredXSEVersion() const noexcept -> REX::Version
		{
			return REX::Version::Unpack(_xseMinimum);
		}

		constexpr void SetMinimumRequiredXSEVersion(REX::Version a_version) noexcept
		{
			_xseMinimum = a_version.Pack<std::uint32_t>();
		}

	private:
		template <class CharT, std::size_t N>
		static constexpr void CopyBuffer(std::string_view a_source, std::span<CharT, N> a_target) noexcept
		{
			REX::Assert(a_source.size() < a_target.size());

			std::ranges::fill(a_target, REX::EMPTY_CHAR<char>);
			std::ranges::copy(a_source, a_target.begin());
		}

		// members
		F4SE::DataVersion _dataVersion{DATA_VERSION};											 // 0x000
		std::uint32_t _pluginVersion{0};														 // 0x004
		REX::StaticString<0x100> _pluginName{REX::EMPTY_CHAR<char>};							 // 0x008
		REX::StaticString<0x100> _pluginAuthor{REX::EMPTY_CHAR<char>};							 // 0x108
		REX::EnumSet<AddressIndependence> _addressIndependence{AddressIndependence::None};		 // 0x208
		REX::EnumSet<StructureIndependence> _structureIndependence{StructureIndependence::None}; // 0x20C
		std::array<std::uint32_t, 0x10> _compatibleVersions{0};									 // 0x210
		std::uint32_t _xseMinimum{0};															 // 0x250
		[[maybe_unused]]
		std::uint32_t _reservedNonBreaking{0}; // 0x254
		[[maybe_unused]]
		std::uint32_t _reservedBreaking{0}; // 0x258
		[[maybe_unused]]
		std::array<std::uint8_t, 0x200> _reserved{0}; // 0x25C
	};

	static_assert(sizeof(PluginVersionData) == 0x45C);
}
