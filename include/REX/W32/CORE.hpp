#pragma once

#if _INC_WINAPIFAMILY != 0
#error Windows API detected. Please move any Windows API includes after CommonLib or remove them.
#endif

#ifndef WIN_API
#define WIN_API __stdcall
#endif

#define BASIC_REX_W32_IMPORT(a_ret, a_name, a_noexcept, ...)                          \
	extern "C" __declspec(dllimport) a_ret WIN_API W32_IMPL_##a_name(...) a_noexcept; \
	__pragma(comment(linker, "/alternatename:__imp_W32_IMPL_" #a_name "=__imp_" #a_name))

#define REX_W32_IMPORT(a_ret, a_name, ...) \
	BASIC_REX_W32_IMPORT(a_ret, a_name, noexcept(true), __VA_ARGS__)

#define REX_W32_IMPORT_THROW(a_ret, a_name, ...) \
	BASIC_REX_W32_IMPORT(a_ret, a_name, noexcept(false), __VA_ARGS__)

namespace REX::W32
{
	template <class T>
		requires(std::is_pointer_v<T>)
	using HANDLE_WRAPPER = std::uintptr_t;

	using BOOL = std::int32_t;
	using DWORD = std::uint32_t;
	using ERROR_CODE = std::uint32_t;
	using HANDLE = HANDLE_WRAPPER<void*>;
	using HBITMAP = HANDLE_WRAPPER<struct HBITMAP__*>;
	using HBRUSH = HANDLE_WRAPPER<struct HBRUSH__*>;
	using HCURSOR = HANDLE_WRAPPER<struct HCURSOR__*>;
	using HDC = HANDLE_WRAPPER<struct HDC__*>;
	using HFONT = HANDLE_WRAPPER<struct HFONT__*>;
	using HICON = HANDLE_WRAPPER<struct HICON__*>;
	using HINSTANCE = HANDLE_WRAPPER<struct HINSTANCE__*>;
	using HKEY = HANDLE_WRAPPER<struct HKEY__*>;
	using HMENU = HANDLE_WRAPPER<struct HMENU__*>;
	using HMODULE = HINSTANCE;
	using HMONITOR = HANDLE_WRAPPER<struct HMONITOR__*>;
	using HPALETTE = HANDLE_WRAPPER<struct HPALETTE__*>;
	using HPEN = HANDLE_WRAPPER<struct HPEN__*>;
	using HRESULT = std::int32_t;
	using HSTRING = HANDLE_WRAPPER<struct HSTRING__*>;
	using HWND = HANDLE_WRAPPER<struct HWND__*>;
	using LPCVOID = const void*;
	using LPVOID = void*;
	using NTSTATUS = std::int32_t;
	using THREAD_ID = std::uint32_t;

	inline constexpr auto TRUE{ static_cast<BOOL>(1) };
	inline constexpr auto FALSE{ static_cast<BOOL>(0) };
	inline constexpr auto EMPTY_THREAD_ID{ static_cast<THREAD_ID>(0) };
	inline constexpr auto ERROR_CODE_SUCCESS{ static_cast<ERROR_CODE>(0) };
	inline constexpr auto INVALID_HANDLE_VALUE{ static_cast<HANDLE>(-1) };
	inline constexpr auto INFINITE{ 0xFFFFFFFFui32 };
	inline constexpr auto MAX_DIR{ 256ui32 };
	inline constexpr auto MAX_DRIVE{ 3ui32 };
	inline constexpr auto MAX_EXT{ 256ui32 };
	inline constexpr auto MAX_FNAME{ 256ui32 };
	inline constexpr auto MAX_PATH{ 260ui32 };
}

namespace REX::W32
{
	class FILETIME
	{
	public:
		constexpr FILETIME() noexcept = default;

		constexpr FILETIME(std::uint64_t a_value) noexcept
		{
			*this = std::bit_cast<FILETIME>(a_value);
		}

		constexpr operator std::uint64_t() const noexcept
		{
			return std::bit_cast<std::uint64_t>(*this);
		}

		// members
		std::uint32_t lowPart{ 0 };	 // 00
		std::uint32_t highPart{ 0 }; // 04
	};
	static_assert(sizeof(FILETIME) == 0x08);
}

namespace REX::W32
{
	class GUID
	{
	public:
		constexpr GUID() noexcept = default;

		constexpr GUID(std::uint32_t a_data1, std::uint16_t a_data2, std::uint16_t a_data3, const std::array<std::uint8_t, 8>& a_data4) noexcept
			: data1(a_data1),
			  data2(a_data2),
			  data3(a_data3),
			  data4{ a_data4[0], a_data4[1], a_data4[2], a_data4[3], a_data4[4], a_data4[5], a_data4[6], a_data4[7] }
		{
		}

		constexpr GUID(const GUID&) noexcept = default;
		constexpr GUID(GUID&&) noexcept = default;

		constexpr GUID& operator=(const GUID&) noexcept = default;
		constexpr GUID& operator=(GUID&&) noexcept = default;

		[[nodiscard]] constexpr bool operator==(const GUID&) const noexcept = default;
		[[nodiscard]] constexpr bool operator!=(const GUID&) const noexcept = default;
		[[nodiscard]] constexpr auto operator<=>(const GUID&) const noexcept = default;

		// members
		std::uint32_t data1{ 0 };				// 00
		std::uint16_t data2{ 0 };				// 04
		std::uint16_t data3{ 0 };				// 08
		std::array<std::uint8_t, 8> data4{ 0 }; // 10
	};
	static_assert(sizeof(GUID) == 0x10);

	using UUID = GUID;
	using IID = GUID;
}

namespace REX::W32
{
	class POINT
	{
	public:
		constexpr POINT() noexcept = default;

		constexpr POINT(std::int32_t a_x, std::int32_t a_y) noexcept
			: x(a_x), y(a_y)
		{
		}

		constexpr POINT(const POINT&) noexcept = default;
		constexpr POINT(POINT&&) noexcept = default;

		constexpr POINT& operator=(const POINT&) noexcept = default;
		constexpr POINT& operator=(POINT&&) noexcept = default;

		[[nodiscard]] constexpr bool operator==(const POINT&) const noexcept = default;
		[[nodiscard]] constexpr bool operator!=(const POINT&) const noexcept = default;
		[[nodiscard]] constexpr auto operator<=>(const POINT&) const noexcept = default;

		// members
		std::int32_t x{ 0 }; // 00
		std::int32_t y{ 0 }; // 04
	};
	static_assert(sizeof(POINT) == 0x08);
}

namespace REX::W32
{
	class RECT
	{
	public:
		constexpr RECT() noexcept = default;

		constexpr RECT(std::int32_t a_x1, std::int32_t a_y1, std::int32_t a_x2, std::int32_t a_y2) noexcept
			: x1(a_x1), y1(a_y1), x2(a_x2), y2(a_y2)
		{
		}

		constexpr RECT(const RECT&) noexcept = default;
		constexpr RECT(RECT&&) noexcept = default;

		constexpr RECT& operator=(const RECT&) noexcept = default;
		constexpr RECT& operator=(RECT&&) noexcept = default;

		[[nodiscard]] constexpr bool operator==(const RECT&) const noexcept = default;
		[[nodiscard]] constexpr bool operator!=(const RECT&) const noexcept = default;
		[[nodiscard]] constexpr auto operator<=>(const RECT&) const noexcept = default;

		// members
		std::int32_t x1{ 0 }; // 00
		std::int32_t y1{ 0 }; // 04
		std::int32_t x2{ 0 }; // 08
		std::int32_t y2{ 0 }; // 10
	};
	static_assert(sizeof(RECT) == 0x10);
}

namespace REX::W32
{
	struct SIZE
	{
		// members
		std::int32_t x; // 00
		std::int32_t y; // 04
	};
	static_assert(sizeof(SIZE) == 0x08);
}

namespace REX::W32
{
	struct CRITICAL_SECTION
	{
		// members
		void* debugInfo;			 // 00
		std::int32_t lockCount;		 // 08
		std::int32_t recursionCount; // 0C
		HANDLE owningThread;		 // 10
		HANDLE lockSemaphore;		 // 18
		std::uintptr_t spinCount;	 // 20
	};
	static_assert(sizeof(CRITICAL_SECTION) == 0x28);

	struct SECURITY_ATTRIBUTES
	{
		// members
		std::uint32_t length;	  // 00
		void* securityDescriptor; // 04
		BOOL inheritHandle;		  // 0C
	};
	static_assert(sizeof(SECURITY_ATTRIBUTES) == 0x18);

	union LARGE_INTEGER
	{
		// members
		union
		{
			struct
			{
				std::uint32_t lowPart;
				std::int32_t highPart;
			};
			std::int64_t value;
		}; // 00
	};
	static_assert(sizeof(LARGE_INTEGER) == 0x08);

	union ULARGE_INTEGER
	{
		// members
		union
		{
			struct
			{
				std::uint32_t lowPart;
				std::uint32_t highPart;
			};
			std::uint64_t value;
		}; // 00
	};
	static_assert(sizeof(ULARGE_INTEGER) == 0x08);

	struct UNICODE_STRING
	{
		// members
		std::uint16_t length;	 // 00
		std::uint16_t maxLength; // 02
		wchar_t* buffer;		 // 08
	};
	static_assert(sizeof(UNICODE_STRING) == 0x10);
}

namespace REX::W32
{
	[[nodiscard]] constexpr bool SUCCESS(const HRESULT a_result) noexcept
	{
		return a_result >= 0;
	}

	[[nodiscard]] constexpr bool NT_SUCCESS(const NTSTATUS a_status) noexcept
	{
		return a_status >= 0;
	}
}
