#include "REL/Iat.hpp"

#include "REL/Memory.hpp"
#include "REX/Comparison.hpp"
#include "REX/W32/CORE.hpp"
#include "REX/W32/KERNEL32.hpp"

namespace REL
{
	auto GetImportFunctionAddress(
		REX::W32::HMODULE a_moduleHandle,
		std::string_view a_libraryName,
		std::string_view a_functionName) -> std::uintptr_t
	{
		return std::bit_cast<std::uintptr_t>(GetImportFunctionPointer(a_moduleHandle, a_libraryName, a_functionName));
	}

	auto GetImportFunctionPointer(
		REX::W32::HMODULE a_moduleHandle,
		std::string_view a_libraryName,
		std::string_view a_functionName) -> void*
	{
		if (a_moduleHandle == 0) {
			return nullptr;
		}

		auto* dosHeader = std::bit_cast<REX::W32::IMAGE_DOS_HEADER*>(a_moduleHandle);
		if (dosHeader->magic != REX::W32::IMAGE_DOS_SIGNATURE) {
			return nullptr;
		}

		const auto* ntHeader = REL::AdjustPointer<REX::W32::IMAGE_NT_HEADERS64>(dosHeader, dosHeader->lfanew);
		const auto& dataDirectory = ntHeader->optionalHeader.dataDirectory[REX::W32::IMAGE_DIRECTORY_ENTRY_IMPORT];
		const auto* importDescriptor =
			REL::AdjustPointer<REX::W32::IMAGE_IMPORT_DESCRIPTOR>(dosHeader, dataDirectory.virtualAddress);

		for (const auto* import = importDescriptor; import->characteristics != 0; import++) {
			const auto* importName = REL::AdjustPointer<const char>(dosHeader, import->name);
			if (!REX::EqualsIgnoreCase(a_libraryName, std::string_view(importName))) {
				continue;
			}

			const auto* thunkData =
				REL::AdjustPointer<REX::W32::IMAGE_THUNK_DATA64>(dosHeader, import->firstThunkOriginal);
			for (auto i = static_cast<std::size_t>(0); thunkData[i].ordinal != 0; i++) {
				if (REX::W32::IMAGE_SNAP_BY_ORDINAL64(thunkData[i].ordinal)) {
					continue;
				}

				const auto* importByName = REL::AdjustPointer<REX::W32::IMAGE_IMPORT_BY_NAME>(
					dosHeader,
					static_cast<std::ptrdiff_t>(thunkData[i].address));
				if (REX::EqualsIgnoreCase(a_functionName, std::string_view(importByName->name.data()))) {
					return REL::AdjustPointer<REX::W32::IMAGE_THUNK_DATA64>(dosHeader, import->firstThunk) + i;
				}
			}
		}

		return nullptr;
	}

	auto SetImportFunctionPointer(
		REX::W32::HMODULE a_moduleHandle,
		std::string_view a_libraryName,
		std::string_view a_functionName,
		std::uintptr_t a_newFunc) -> std::uintptr_t
	{
		const auto oldFunc = GetImportFunctionAddress(a_moduleHandle, a_libraryName, a_functionName);
		if (oldFunc == 0) {
			return 0;
		}

		const auto oldAddress = *std::bit_cast<std::uintptr_t*>(oldFunc);
		std::ignore = WriteSafeData(oldFunc, a_newFunc);
		return oldAddress;
	}
}
