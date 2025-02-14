#pragma once

#include "REL/Segment.hpp"
#include "REL/Version.hpp"

namespace REL
{
	class Module
	{
	public:
		Module(const Module&) = delete;
		Module(Module&&) = delete;

		Module& operator=(const Module&) = delete;
		Module& operator=(Module&&) = delete;

		/**
		 * Identifies a FALLOUT runtime.
		 */
		enum class Runtime : uint8_t
		{
			Unknown = 0,

			/**
			 * The FALLOUT runtime is a post-Next Generation Update FALLOUT release (version 1.10.980 and later).
			 */
			NG = 1 << 0,

			/**
			 * The FALLOUT runtime is a pre-Next Generation Update FALLOUT release (version 1.10.163 and prior).
			 */
			F4 = 1 << 1,

			/**
			 * The FALLOUT runtime is FALLOUT VR.
			 */
			VR = 1 << 2
		};
		[[nodiscard]] static Module& get()
		{
			static Module singleton;
			return singleton;
		}

		[[nodiscard]] constexpr std::uintptr_t base() const noexcept { return _base; }
		[[nodiscard]] stl::zwstring filename() const noexcept { return _filename; }
		[[nodiscard]] stl::zwstring filePath() const noexcept { return _filePath; }
		[[nodiscard]] constexpr Segment segment(Segment::Name a_segment) const noexcept { return _segments[a_segment]; }
		[[nodiscard]] constexpr Version version() const noexcept { return _version; }

		[[nodiscard]] REX::W32::HMODULE pointer() const noexcept { return reinterpret_cast<REX::W32::HMODULE>(base()); }

		template <class T>
		[[nodiscard]] T* pointer() const noexcept
		{
			return static_cast<T*>(pointer());
		}

		/**
		 * Get the type of runtime the currently-loaded FALLOUT module is.
		 */
		[[nodiscard]] static FALLOUT_REL Runtime GetRuntime() noexcept
		{
#if (!defined(ENABLE_FALLOUT_NG) && !defined(ENABLE_FALLOUT_VR))
			return Runtime::F4;
#elif (!defined(ENABLE_FALLOUT_F4) && !defined(ENABLE_FALLOUT_VR))
			return Runtime::NG;
#elif (!defined(ENABLE_FALLOUT_NG) && !defined(ENABLE_FALLOUT_F4))
			return Runtime::VR;
#else
			return get()._runtime;
#endif
		}

		/**
		 * Returns whether the current FALLOUT runtime is a post-Nextgen Update Fallout release.
		 */
		[[nodiscard]] static FALLOUT_REL bool IsNG() noexcept
		{
			return GetRuntime() == Runtime::NG;
		}

		/**
		 * Returns whether the current FALLOUT runtime is a pre-Nextgen Update Fallout release.
		 */
		[[nodiscard]] static FALLOUT_REL bool IsF4() noexcept
		{
			return GetRuntime() == Runtime::F4;
		}

		/**
		 * Returns whether the current FALLOUT runtime is a FALLOUT VR release.
		 */
		[[nodiscard]] static FALLOUT_REL_VR bool IsVR() noexcept
		{
#if !defined(ENABLE_FALLOUT_VR)
			return false;
#elif !defined(ENABLE_FALLOUT_NG) && !defined(ENABLE_FALLOUT_F4)
			return true;
#else
			return GetRuntime() == Runtime::VR;
#endif
		}

	private:
		Module();
		~Module() noexcept = default;

		void load_segments();
		void load_version();

		static constexpr auto ENVIRONMENT = L"F4SE_RUNTIME"sv;

		static constexpr std::array<std::wstring_view, 2> RUNTIMES{ { L"Fallout4VR.exe",
			L"Fallout4.exe" } };

		static constexpr std::array SEGMENTS{
			".text"sv,
			".interpr"sv,
			".idata"sv,
			".rdata"sv,
			".data"sv,
			".pdata"sv,
			".tls"sv
		};

		static inline std::uintptr_t _natvis{ 0 };

		std::wstring _filename;
		std::wstring _filePath;
		std::array<Segment, Segment::total> _segments;
		Version _version;
		std::uintptr_t _base{ 0 };
		Runtime _runtime{ Runtime::NG };
	};
}
