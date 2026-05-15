#pragma once

#include "REL/Cast.hpp"

#include "REX/W32/CORE.hpp"

namespace REL
{
	[[nodiscard]] std::uintptr_t GetImportFunctionAddress(REX::W32::HMODULE a_module, std::string_view a_library, std::string_view a_function);

	[[nodiscard]] void* GetImportFunctionPointer(REX::W32::HMODULE a_module, std::string_view a_library, std::string_view a_function);

	template <class T>
	[[nodiscard]] T* GetImportFunctionPointer(REX::W32::HMODULE a_module, std::string_view a_library, std::string_view a_function)
	{
		return static_cast<T*>(GetImportFunctionPointer(a_module, a_library, a_function));
	}

	std::uintptr_t SetImportFunctionPointer(REX::W32::HMODULE a_module, std::string_view a_library, std::string_view a_function, std::uintptr_t a_newFunc);

	template <class F>
	std::uintptr_t SetImportFunctionPointer(REX::W32::HMODULE a_module, std::string_view a_library, std::string_view a_function, F a_newFunc)
	{
		return SetImportFunctionPointer(a_module, a_library, a_function, REL::UnrestrictedCast<std::uintptr_t>(a_newFunc));
	}
}
