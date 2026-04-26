#include "REL/Iat.hpp"

#include "REL/Memory.hpp"

#include "REX/Compare.hpp"
#include "REX/W32/KERNEL32.hpp"

namespace REL
{
	std::uintptr_t GetImportFunctionAddress(REX::W32::HMODULE a_module, std::string_view a_library, std::string_view a_function)
	{
		return std::bit_cast<std::uintptr_t>(GetImportFunctionPointer(a_module, a_library, a_function));
	}

	// Source: https://guidedhacking.com/attachments/pe_imptbl_headers-jpg.2241/
	void* GetImportFunctionPointer(REX::W32::HMODULE a_module, std::string_view a_library, std::string_view a_function)
	{
		if (!a_module) {
			return nullptr;
		}

		auto* dosHeader = std::bit_cast<REX::W32::IMAGE_DOS_HEADER*>(a_module);
		if (dosHeader->magic != REX::W32::IMAGE_DOS_SIGNATURE) {
			return nullptr;
		}

		const auto* ntHeader = REL::AdjustPointer<REX::W32::IMAGE_NT_HEADERS64>(dosHeader, dosHeader->lfanew);
		const auto& dataDirectory = ntHeader->optionalHeader.dataDirectory[REX::W32::IMAGE_DIRECTORY_ENTRY_IMPORT];
		const auto* importDescriptor = REL::AdjustPointer<REX::W32::IMAGE_IMPORT_DESCRIPTOR>(dosHeader, dataDirectory.virtualAddress);

		for (const auto* import = importDescriptor; import->characteristics != 0; import++) {
			const auto* importName = REL::AdjustPointer<const char>(dosHeader, import->name);
			if (!REX::EqualsIgnoreCase(a_library, std::string_view(importName))) {
				continue;
			}

			const auto* thunkData = REL::AdjustPointer<REX::W32::IMAGE_THUNK_DATA64>(dosHeader, import->firstThunkOriginal);
			for (auto i = static_cast<std::size_t>(0); thunkData[i].ordinal != 0; i++) {
				if (REX::W32::IMAGE_SNAP_BY_ORDINAL64(thunkData[i].ordinal)) {
					continue;
				}

				const auto* importByName = REL::AdjustPointer<REX::W32::IMAGE_IMPORT_BY_NAME>(dosHeader, static_cast<std::ptrdiff_t>(thunkData[i].address));
				if (REX::EqualsIgnoreCase(a_function, std::string_view(importByName->name.data()))) {
					return REL::AdjustPointer<REX::W32::IMAGE_THUNK_DATA64>(dosHeader, import->firstThunk) + i;
				}
			}
		}

		return nullptr;
	}

	std::uintptr_t SetImportFunctionPointer(REX::W32::HMODULE a_module, std::string_view a_library, std::string_view a_function, std::uintptr_t a_newFunc)
	{
		const auto oldFunc = GetImportFunctionAddress(a_module, a_library, a_function);
		if (oldFunc == 0) {
			return 0;
		}

		const auto oldAddress = *std::bit_cast<std::uintptr_t*>(oldFunc);
		std::ignore = WriteSafeData(oldFunc, a_newFunc);
		return oldAddress;
	}
}
