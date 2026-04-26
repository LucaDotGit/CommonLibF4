#pragma once

#include "REL/Runtime.hpp"

#include "REX/Contract.hpp"
#include "REX/EnumSet.hpp"
#include "REX/NotNull.hpp"
#include "REX/Own.hpp"
#include "REX/Version.hpp"

namespace F4SE
{
	class PluginVersionData final // since F4SE v0.7.0
	{
	public:
		inline static constexpr auto DATA_VERSION{ 1ui32 };

		enum class AddressIndependence : std::uint32_t
		{
			kUseSignatureScanning = 1 << 0,
			kUseAddressLibrary_RuntimeNG = 1 << 1,
			kUseAddressLibrary_RuntimeAE = 1 << 2,

			kUseAddressLibrary = kUseAddressLibrary_RuntimeAE
		};

		enum class StructureIndependence : std::uint32_t
		{
			kUseNoStructs = 1 << 0,
			kIsLayoutDependent_RuntimeNG = 1 << 1,
			kIsLayoutDependent_RuntimeAE = 1 << 2,

			kIsLayoutDependent = kIsLayoutDependent_RuntimeAE
		};

		constexpr PluginVersionData() noexcept = default;
		constexpr ~PluginVersionData() noexcept = default;

		constexpr PluginVersionData(const PluginVersionData&) noexcept = default;
		constexpr PluginVersionData(PluginVersionData&&) noexcept = default;

		constexpr PluginVersionData& operator=(const PluginVersionData&) noexcept = default;
		constexpr PluginVersionData& operator=(PluginVersionData&&) noexcept = default;

		[[nodiscard]] static auto GetSingleton() noexcept -> REX::NotNull<REX::Observer<const PluginVersionData*>>;

		[[nodiscard]] constexpr std::uint32_t GetDataVersion() const noexcept { return _dataVersion; }
		constexpr void SetDataVersion(std::uint32_t a_version) noexcept { _dataVersion = a_version; }

		[[nodiscard]] constexpr REX::Version GetPluginVersion() const noexcept { return REX::Version::Unpack(_pluginVersion); }
		constexpr void SetPluginVersion(REX::Version a_version) noexcept { _pluginVersion = a_version.Pack<std::uint32_t>(); }

		[[nodiscard]] constexpr std::uint32_t GetPluginVersionNumber() const noexcept { return _pluginVersion; }
		constexpr void SetPluginVersionNumber(std::uint32_t a_version) noexcept { _pluginVersion = a_version; }

		[[nodiscard]] constexpr std::string_view GetPluginName() const noexcept { return _pluginName.data(); }
		constexpr void SetPluginName(std::string_view a_name) noexcept { SetCharBuffer(a_name, _pluginName); }

		[[nodiscard]] constexpr std::string_view GetPluginAuthor() const noexcept { return _pluginAuthor.data(); }
		constexpr void SetPluginAuthor(std::string_view a_author) noexcept { SetCharBuffer(a_author, _pluginAuthor); }

		[[nodiscard]] constexpr bool GetUseSignatureScanning() const noexcept { return _addressIndependence.any(AddressIndependence::kUseSignatureScanning); }
		constexpr void SetUseSignatureScanning(bool a_value) noexcept { _addressIndependence.set(a_value, AddressIndependence::kUseSignatureScanning); }

		[[nodiscard]] constexpr bool GetUseAddressLibrary_RuntimeNG() const noexcept { return _addressIndependence.any(AddressIndependence::kUseAddressLibrary_RuntimeNG); }
		constexpr void SetUseAddressLibrary_RuntimeNG(bool a_value) noexcept { _addressIndependence.set(a_value, AddressIndependence::kUseAddressLibrary_RuntimeNG); }

		[[nodiscard]] constexpr bool GetUseAddressLibrary_RuntimeAE() const noexcept { return _addressIndependence.any(AddressIndependence::kUseAddressLibrary_RuntimeAE); }
		constexpr void SetUseAddressLibrary_RuntimeAE(bool a_value) noexcept { _addressIndependence.set(a_value, AddressIndependence::kUseAddressLibrary_RuntimeAE); }

		[[nodiscard]] constexpr bool GetUseAddressLibrary() const noexcept { return _addressIndependence.any(AddressIndependence::kUseAddressLibrary); }
		constexpr void SetUseAddressLibrary(bool a_value) noexcept { _addressIndependence.set(a_value, AddressIndependence::kUseAddressLibrary); }

		[[nodiscard]] constexpr bool GetUseNoStructs() const noexcept { return _structureIndependence.any(StructureIndependence::kUseNoStructs); }
		constexpr void SetUseNoStructs(bool a_value) noexcept { _structureIndependence.set(a_value, StructureIndependence::kUseNoStructs); }

		[[nodiscard]] constexpr bool GetIsLayoutDependent_RuntimeNG() const noexcept { return _structureIndependence.any(StructureIndependence::kIsLayoutDependent_RuntimeNG); }
		constexpr void SetIsLayoutDependent_RuntimeNG(bool a_value) noexcept { _structureIndependence.set(a_value, StructureIndependence::kIsLayoutDependent_RuntimeNG); }

		[[nodiscard]] constexpr bool GetIsLayoutDependent_RuntimeAE() const noexcept { return _structureIndependence.any(StructureIndependence::kIsLayoutDependent_RuntimeAE); }
		constexpr void SetIsLayoutDependent_RuntimeAE(bool a_value) noexcept { _structureIndependence.set(a_value, StructureIndependence::kIsLayoutDependent_RuntimeAE); }

		[[nodiscard]] constexpr bool GetIsLayoutDependent() const noexcept { return _structureIndependence.any(StructureIndependence::kIsLayoutDependent); }
		constexpr void SetIsLayoutDependent(bool a_value) noexcept { _structureIndependence.set(a_value, StructureIndependence::kIsLayoutDependent); }

		[[nodiscard]] constexpr std::vector<REX::Version> GetCompatibleVersions() const
		{
			return std::ranges::views::transform(_compatibleVersions, [](std::uint32_t a_version) noexcept {
				return REX::Version::Unpack(a_version);
			}) | std::ranges::to<std::vector>();
		}

		constexpr void SetCompatibleVersions(std::span<const REX::Version> a_versions) noexcept
		{
			REX::Assert(a_versions.size() < _compatibleVersions.size() - 1);

			std::ranges::fill(_compatibleVersions, 0);
			std::ranges::transform(a_versions, _compatibleVersions.begin(), [](REX::Version a_version) noexcept {
				return a_version.Pack<std::uint32_t>();
			});
		}

		constexpr void SetCompatibleVersions(std::span<const REL::Runtime> a_runtimes) noexcept
		{
			REX::Assert(a_runtimes.size() < _compatibleVersions.size() - 1);

			std::ranges::fill(_compatibleVersions, 0);
			std::ranges::transform(a_runtimes, _compatibleVersions.begin(), [](REL::Runtime a_version) noexcept {
				return a_version.GetVersion().Pack<std::uint32_t>();
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

		[[nodiscard]] constexpr REX::Version GetMinimumRequiredXSEVersion() const noexcept { return REX::Version::Unpack(_xseMinimum); }
		constexpr void SetMinimumRequiredXSEVersion(REX::Version a_version) noexcept { _xseMinimum = a_version.Pack<std::uint32_t>(); }

	private:
		static constexpr void SetCharBuffer(std::string_view a_source, std::span<char> a_target) noexcept
		{
			REX::Assert(a_source.size() < a_target.size());

			std::ranges::fill(a_target, '\0');
			std::ranges::copy(a_source, a_target.begin());
		}

		// members
		std::uint32_t _dataVersion{ DATA_VERSION };						 // 000
		std::uint32_t _pluginVersion{ 0 };								 // 004
		std::array<char, 0x100> _pluginName{ '\0' };					 // 008
		std::array<char, 0x100> _pluginAuthor{ '\0' };					 // 108
		REX::EnumSet<AddressIndependence> _addressIndependence;			 // 208
		REX::EnumSet<StructureIndependence> _structureIndependence;		 // 20C
		std::array<std::uint32_t, 0x10> _compatibleVersions{ 0 };		 // 210
		std::uint32_t _xseMinimum{ 0 };									 // 250
		[[maybe_unused]] std::uint32_t _reservedNonBreaking{ 0 };		 // 254
		[[maybe_unused]] std::uint32_t _reservedBreaking{ 0 };			 // 258
		[[maybe_unused]] std::array<std::uint8_t, 0x200> _reserved{ 0 }; // 25C
	};
	static_assert(sizeof(PluginVersionData) == 0x45C);
}
