#pragma once

#include "REL/Runtime.hpp"
#include "REX/Casting.hpp"
#include "REX/Comparison.hpp"
#include "REX/Singleton.hpp"
#include "REX/Version.hpp"

namespace REL
{
	class ModuleSection;

	class Module final : public REX::Singleton<Module>
	{
	public:
		Module();
		~Module() noexcept;

		Module(const Module&) = delete;
		Module(Module&&) = delete;

		auto operator=(const Module&) -> Module& = delete;
		auto operator=(Module&&) -> Module& = delete;

		[[nodiscard]]
		auto GetFilePath() const noexcept -> const auto&
		{
			return _filePath;
		}

		[[nodiscard]]
		auto GetBaseAddress() const noexcept
		{
			return _baseAddress;
		}

		[[nodiscard]]
		auto GetVersion() const noexcept
		{
			return _version;
		}

		[[nodiscard]]
		auto GetRuntime() const noexcept -> const auto&
		{
			return _runtime;
		}

		void SetRuntime(const REL::Runtime& a_runtime) noexcept
		{
			_runtime = a_runtime;
		}

		[[nodiscard]]
		auto GetSectionByName(std::string_view a_sectionName) const noexcept -> std::optional<REL::ModuleSection>;

		[[nodiscard]]
		auto GetImportFunctionAddress(std::string_view a_library, std::string_view a_function) const -> std::uintptr_t;

		[[nodiscard]]
		auto GetImportFunctionPointer(std::string_view a_library, std::string_view a_function) const -> void*;

		auto SetImportFunctionPointer(std::string_view a_library, std::string_view a_function, std::uintptr_t a_newFunc)
			const -> std::uintptr_t;

		template <class T>
		[[nodiscard]]
		auto GetImportFunctionPointer(std::string_view a_library, std::string_view a_function) const -> T*
		{
			return static_cast<T*>(GetImportFunctionPointer(a_library, a_function));
		}

		template <class F>
		auto SetImportFunctionPointer(std::string_view a_library, std::string_view a_function, F a_newFunc) const
			-> std::uintptr_t
		{
			return SetImportFunctionPointer(a_library, a_function, REX::UnrestrictedCast<std::uintptr_t>(a_newFunc));
		}

		void Setup();

	private:
		void SetupDefaultLocale();
		void SetupTimeZoneDb();
		void SetupFile();
		void SetupVersion();
		void SetupSegments();

		std::filesystem::path _filePath;
		std::uintptr_t _baseAddress{0};
		REX::Version _version;
		REL::Runtime _runtime{REL::Runtime::LATEST};
		std::flat_map<std::string, REL::ModuleSection, REX::StringLess<char>> _sections;
	};
}
