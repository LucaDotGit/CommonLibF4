#include "REL/Module.hpp"

#include "REL/Iat.hpp"

#include "REX/Locale.hpp"
#include "REX/Message.hpp"
#include "REX/Version.hpp"
#include "REX/W32/KERNEL32.hpp"

namespace REL
{
	Module::Module() = default;

	Module::~Module() noexcept = default;

	REL::ModuleSection Module::GetSection(std::string_view a_sectionName) const noexcept
	{
		const auto sectionIt = _sections.find(a_sectionName);
		if (sectionIt == _sections.end()) [[unlikely]] {
			REX::Assert(false);
			return {};
		}

		return sectionIt->second;
	}

	std::uintptr_t Module::GetImportFunctionAddress(std::string_view a_library, std::string_view a_function) const
	{
		auto modulePtr = std::bit_cast<REX::W32::HMODULE>(_baseAddress);
		return REL::GetImportFunctionAddress(modulePtr, a_library, a_function);
	}

	void* Module::GetImportFunctionPointer(std::string_view a_library, std::string_view a_function) const
	{
		auto modulePtr = std::bit_cast<REX::W32::HMODULE>(_baseAddress);
		return REL::GetImportFunctionPointer(modulePtr, a_library, a_function);
	}

	std::uintptr_t Module::SetImportFunctionPointer(std::string_view a_library, std::string_view a_function, std::uintptr_t a_newFunc) const
	{
		auto modulePtr = std::bit_cast<REX::W32::HMODULE>(_baseAddress);
		return REL::SetImportFunctionPointer(modulePtr, a_library, a_function, a_newFunc);
	}

	bool Module::IsModuleLoaded(REX::zstring_view a_moduleName) noexcept
	{
		return REX::W32::GetModuleHandleA(a_moduleName.data()) != 0;
	}

	bool Module::IsModuleLoaded(REX::zwstring_view a_moduleName) noexcept
	{
		return REX::W32::GetModuleHandleW(a_moduleName.data()) != 0;
	}

	void Module::Init()
	{
		InitLocale();
		InitFile();
		InitVersion();
		InitSegments();
	}

	// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
	void Module::InitLocale()
	{
		std::ignore = REX::GetDefaultCLocale();
		std::ignore = REX::GetDefaultCppLocale();
	}

	void Module::InitFile()
	{
		auto moduleHandle = REX::W32::GetModuleHandleA(nullptr);

		auto filePathBuffer = std::array<wchar_t, REX::W32::MAX_PATH>();
		if (REX::W32::GetModuleFileNameW(moduleHandle, filePathBuffer.data(), static_cast<std::uint32_t>(filePathBuffer.size())) == 0) [[unlikely]] {
			REX::Fail("Failed to obtain module file name."sv);
		}

		_baseAddress = std::bit_cast<std::uintptr_t>(moduleHandle);
		_filePath = std::filesystem::path(filePathBuffer.data(), std::filesystem::path::generic_format);
	}

	void Module::InitVersion()
	{
		const auto version = REX::GetFileVersion(_filePath.generic_string());
		if (!version) [[unlikely]] {
			REX::Fail(
				"Failed to obtain file version.\n"
				"Path: \"{}\""sv,
				_filePath.generic_string());
		}

		_version = *version;
	}

	void Module::InitSegments()
	{
		const auto* dosHeader = std::bit_cast<const REX::W32::IMAGE_DOS_HEADER*>(_baseAddress);
		const auto* ntHeader = REL::AdjustPointer<REX::W32::IMAGE_NT_HEADERS64>(dosHeader, dosHeader->lfanew);
		const auto* sections = REX::W32::IMAGE_FIRST_SECTION(ntHeader);
		const auto sectionCount = std::min<std::size_t>(ntHeader->fileHeader.sectionCount, MODULE_SECTION_NAMES.size());

		_sections.reserve(sectionCount);

		for (auto i = static_cast<std::size_t>(0); i < sectionCount; i++) {
			const auto& section = sections[i];
			const auto sectionName = std::string_view{ reinterpret_cast<const char*>(section.name.data()) };
			_sections.emplace(sectionName, ModuleSection(_baseAddress, _baseAddress + section.virtualAddress, section.virtualSize));
		}
	}
}
