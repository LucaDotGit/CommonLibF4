#include "REL/Module.hpp"

#include "REL/Iat.hpp"
#include "REL/Memory.hpp"
#include "REL/ModuleSection.hpp"
#include "REX/Container.hpp"
#include "REX/DateTime.hpp"
#include "REX/Localization.hpp"
#include "REX/Message.hpp"
#include "REX/System.hpp"
#include "REX/W32/CORE.hpp"
#include "REX/W32/KERNEL32.hpp"

namespace REL::Impl
{
	extern constexpr auto INTERNAL_LICENSE =
		"This project is licensed under GPL-3.0-or-later with Modding Exception and Linking Exception."sv;
}

namespace REL
{
	Module::Module() = default;

	Module::~Module() noexcept = default;

	auto Module::GetSectionByName(std::string_view a_sectionName) const noexcept -> std::optional<REL::ModuleSection>
	{
		const auto sectionIt = _sections.find(a_sectionName);
		if (sectionIt == _sections.end()) {
			return std::nullopt;
		}

		return sectionIt->second;
	}

	auto Module::GetImportFunctionAddress(std::string_view a_library, std::string_view a_function) const
		-> std::uintptr_t
	{
		const auto moduleHandle = std::bit_cast<REX::W32::HMODULE>(_baseAddress);
		return REL::GetImportFunctionAddress(moduleHandle, a_library, a_function);
	}

	auto Module::GetImportFunctionPointer(std::string_view a_library, std::string_view a_function) const -> void*
	{
		const auto moduleHandle = std::bit_cast<REX::W32::HMODULE>(_baseAddress);
		return REL::GetImportFunctionPointer(moduleHandle, a_library, a_function);
	}

	auto Module::SetImportFunctionPointer(
		std::string_view a_library,
		std::string_view a_function,
		std::uintptr_t a_newFunc) const -> std::uintptr_t
	{
		const auto moduleHandle = std::bit_cast<REX::W32::HMODULE>(_baseAddress);
		return REL::SetImportFunctionPointer(moduleHandle, a_library, a_function, a_newFunc);
	}

	void Module::Setup()
	{
		SetupDefaultLocale();
		SetupTimeZoneDb();
		SetupFile();
		SetupVersion();
		SetupSegments();
	}

	// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
	void Module::SetupDefaultLocale()
	{
		std::ignore = REX::GetOrCreateDefaultLocale();
	}

	// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
	void Module::SetupTimeZoneDb()
	{
		std::ignore = REX::DateTime::GetCurrentTimeZone();
	}

	void Module::SetupFile()
	{
		const auto parentModuleHandle = REX::GetParentModuleHandle();

		auto moduleFilePath = REX::GetModuleFilePath(parentModuleHandle);
		if (!moduleFilePath.has_value()) [[unlikely]] {
			REX::Fail(
				"Failed to get the module file path.\n"
				"System Error (0x{:08X}): {}"sv,
				moduleFilePath.error().value(),
				moduleFilePath.error().message());
		}

		_baseAddress = std::bit_cast<std::uintptr_t>(parentModuleHandle);
		_filePath = std::move(moduleFilePath).value();
	}

	void Module::SetupVersion()
	{
		const auto version = REX::GetModuleFileVersion(std::basic_string_view(_filePath.native()));
		if (!version.has_value()) [[unlikely]] {
			REX::Fail(
				"Failed to get the module file version.\n"
				"File Path: \"{}\"\n"
				"System Error (0x{:08X}): {}"sv,
				_filePath.generic_string(),
				version.error().value(),
				version.error().message());
		}

		_version = version.value();
	}

	void Module::SetupSegments()
	{
		const auto* dosHeader = std::bit_cast<const REX::W32::IMAGE_DOS_HEADER*>(_baseAddress);
		const auto* ntHeader = REL::AdjustPointer<REX::W32::IMAGE_NT_HEADERS64>(dosHeader, dosHeader->lfanew);
		const auto* sections = REX::W32::IMAGE_FIRST_SECTION(ntHeader);
		const auto sectionCount = std::min<std::size_t>(ntHeader->fileHeader.sectionCount, MODULE_SECTION_NAMES.size());

		REX::Reserve(_sections, sectionCount);

		for (const auto& section : std::span{sections, sectionCount}) {
			const auto sectionName = std::string_view{reinterpret_cast<const char*>(section.name.data())};
			_sections.emplace(
				sectionName,
				ModuleSection(_baseAddress, _baseAddress + section.virtualAddress, section.virtualSize));
		}
	}
}
