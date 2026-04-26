#pragma once

#include "REL/Cast.hpp"
#include "REL/ModuleSection.hpp"
#include "REL/Runtime.hpp"

#include "REX/Singleton.hpp"
#include "REX/Version.hpp"
#include "REX/ZString.hpp"

namespace REL
{
	class Module final
		: public REX::Singleton<Module>
	{
	public:
		Module();
		~Module() noexcept;

		Module(const Module&) = delete;
		Module(Module&&) = delete;

		Module& operator=(const Module&) = delete;
		Module& operator=(Module&&) = delete;

		[[nodiscard]] const std::filesystem::path& GetFilePath() const noexcept { return _filePath; }
		[[nodiscard]] REL::ModuleSection GetSection(std::string_view a_sectionName) const noexcept;
		[[nodiscard]] REX::Version GetVersion() const noexcept { return _version; }
		[[nodiscard]] std::uintptr_t GetBaseAddress() const noexcept { return _baseAddress; }

		[[nodiscard]] Runtime GetRuntime() const noexcept { return _runtime; }
		void SetRuntime(Runtime a_runtime) noexcept { _runtime = a_runtime; }

		[[nodiscard]] bool GetIsRuntimeVR() const noexcept { return _runtime.GetType() == RuntimeType::kVR; }

		[[nodiscard]] std::uintptr_t GetImportFunctionAddress(std::string_view a_library, std::string_view a_function) const;

		[[nodiscard]] void* GetImportFunctionPointer(std::string_view a_library, std::string_view a_function) const;

		template <class T>
		[[nodiscard]] T* GetImportFunctionPointer(std::string_view a_library, std::string_view a_function) const
		{
			return static_cast<T*>(GetImportFunctionPointer(a_library, a_function));
		}

		std::uintptr_t SetImportFunctionPointer(std::string_view a_library, std::string_view a_function, std::uintptr_t a_newFunc) const;

		template <class F>
		std::uintptr_t SetImportFunctionPointer(std::string_view a_library, std::string_view a_function, F a_newFunc) const
		{
			return SetImportFunctionPointer(a_library, a_function, REL::UnrestrictedCast<std::uintptr_t>(a_newFunc));
		}

		[[nodiscard]] static bool IsModuleLoaded(REX::zstring_view a_moduleName) noexcept;
		[[nodiscard]] static bool IsModuleLoaded(REX::zwstring_view a_moduleName) noexcept;

		void Load();

	private:
		static void LoadLocale();
		void LoadFile();
		void LoadVersion();
		void LoadSegments();

		std::filesystem::path _filePath;
		std::uintptr_t _baseAddress{ 0 };
		REX::Version _version;
		std::unordered_map<std::string_view, REL::ModuleSection> _sections;
		Runtime _runtime{ Runtime::LATEST };
	};
}
