#pragma once

#include "REX/Casting.hpp"
#include "REX/W32/CORE.hpp"

namespace REL
{
	[[nodiscard]]
	auto GetImportFunctionAddress(
		REX::W32::HMODULE a_moduleHandle,
		std::string_view a_libraryName,
		std::string_view a_functionName) -> std::uintptr_t;

	[[nodiscard]]
	auto GetImportFunctionPointer(
		REX::W32::HMODULE a_moduleHandle,
		std::string_view a_libraryName,
		std::string_view a_functionName) -> void*;

	auto SetImportFunctionPointer(
		REX::W32::HMODULE a_moduleHandle,
		std::string_view a_libraryName,
		std::string_view a_functionName,
		std::uintptr_t a_newFunc) -> std::uintptr_t;

	template <class T>
	[[nodiscard]]
	auto GetImportFunctionPointer(
		REX::W32::HMODULE a_moduleHandle,
		std::string_view a_libraryName,
		std::string_view a_functionName) -> T*
	{
		return static_cast<T*>(GetImportFunctionPointer(a_moduleHandle, a_libraryName, a_functionName));
	}

	template <class F>
	auto SetImportFunctionPointer(
		REX::W32::HMODULE a_moduleHandle,
		std::string_view a_libraryName,
		std::string_view a_functionName,
		F a_newFunc) -> std::uintptr_t
	{
		return SetImportFunctionPointer(
			a_moduleHandle,
			a_libraryName,
			a_functionName,
			REX::UnrestrictedCast<std::uintptr_t>(a_newFunc));
	}
}
