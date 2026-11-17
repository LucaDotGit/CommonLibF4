#pragma once

#include "REX/Concepts.hpp"

#if (_INC_WINAPIFAMILY != 0)
#error "Windows API detected. Please move any Windows API includes after CommonLib or remove them.";
#endif

#ifndef WIN_API
#define WIN_API __stdcall
#endif

namespace REX::W32
{
	template <class T>
		requires(REX::pointer<T>)
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

	inline constexpr auto TRUE = static_cast<BOOL>(1);
	inline constexpr auto FALSE = static_cast<BOOL>(0);
	inline constexpr auto EMPTY_THREAD_ID = static_cast<THREAD_ID>(0);
	inline constexpr auto ERROR_CODE_SUCCESS = static_cast<ERROR_CODE>(0);
	inline constexpr auto INVALID_HANDLE_VALUE = static_cast<HANDLE>(-1);
	inline constexpr auto INFINITE = static_cast<std::uint32_t>(0xFFFF'FFFF);
	inline constexpr auto MAX_DIR = static_cast<std::uint32_t>(256);
	inline constexpr auto MAX_DRIVE = static_cast<std::uint32_t>(3);
	inline constexpr auto MAX_EXT = static_cast<std::uint32_t>(256);
	inline constexpr auto MAX_FNAME = static_cast<std::uint32_t>(256);
	inline constexpr auto MAX_PATH = static_cast<std::uint32_t>(260);
}

namespace REX::W32
{
	struct FILETIME
	{
	public:
		constexpr FILETIME() noexcept = default;
		constexpr ~FILETIME() noexcept = default;

		constexpr explicit FILETIME(std::uint64_t a_value) noexcept
		{
			*this = std::bit_cast<FILETIME>(a_value);
		}

		constexpr FILETIME(std::uint32_t a_lowPart, std::uint32_t a_highPart) noexcept :
			lowPart(a_lowPart),
			highPart(a_highPart)
		{
		}

		constexpr FILETIME(const FILETIME&) noexcept = default;
		constexpr FILETIME(FILETIME&&) noexcept = default;

		constexpr auto operator=(const FILETIME&) noexcept -> FILETIME& = default;
		constexpr auto operator=(FILETIME&&) noexcept -> FILETIME& = default;

		[[nodiscard]]
		constexpr auto operator==(const FILETIME&) const noexcept -> bool = default;
		[[nodiscard]]
		constexpr auto operator<=>(const FILETIME&) const noexcept = default;

		[[nodiscard]]
		constexpr explicit operator std::uint64_t() const noexcept
		{
			return std::bit_cast<std::uint64_t>(*this);
		}

		std::uint32_t lowPart{0};
		std::uint32_t highPart{0};
	};

	static_assert(sizeof(FILETIME) == 0x08);

	struct GUID
	{
	public:
		constexpr GUID() noexcept = default;
		constexpr ~GUID() noexcept = default;

		constexpr GUID(
			std::uint32_t a_data1,
			std::uint16_t a_data2,
			std::uint16_t a_data3,
			std::array<std::uint8_t, 8> a_data4) noexcept :
			data1(a_data1),
			data2(a_data2),
			data3(a_data3),
			data4(a_data4)
		{
		}

		constexpr GUID(const GUID&) noexcept = default;
		constexpr GUID(GUID&&) noexcept = default;

		constexpr auto operator=(const GUID&) noexcept -> GUID& = default;
		constexpr auto operator=(GUID&&) noexcept -> GUID& = default;

		[[nodiscard]]
		constexpr auto operator==(const GUID&) const noexcept -> bool = default;
		[[nodiscard]]
		constexpr auto operator<=>(const GUID&) const noexcept = default;

		std::uint32_t data1{0};
		std::uint16_t data2{0};
		std::uint16_t data3{0};
		std::array<std::uint8_t, 8> data4{0};
	};

	static_assert(sizeof(GUID) == 0x10);

	using UUID = GUID;
	using IID = GUID;

	struct POINT
	{
	public:
		constexpr POINT() noexcept = default;
		constexpr ~POINT() noexcept = default;

		constexpr POINT(std::int32_t a_x, std::int32_t a_y) noexcept :
			x(a_x),
			y(a_y)
		{
		}

		constexpr POINT(const POINT&) noexcept = default;
		constexpr POINT(POINT&&) noexcept = default;

		constexpr auto operator=(const POINT&) noexcept -> POINT& = default;
		constexpr auto operator=(POINT&&) noexcept -> POINT& = default;

		[[nodiscard]]
		constexpr auto operator==(const POINT&) const noexcept -> bool = default;
		[[nodiscard]]
		constexpr auto operator<=>(const POINT&) const noexcept = default;

		std::int32_t x{0};
		std::int32_t y{0};
	};

	static_assert(sizeof(POINT) == 0x08);

	struct RECT
	{
	public:
		constexpr RECT() noexcept = default;
		constexpr ~RECT() noexcept = default;

		constexpr RECT(std::int32_t a_x1, std::int32_t a_y1, std::int32_t a_x2, std::int32_t a_y2) noexcept :
			x1(a_x1),
			y1(a_y1),
			x2(a_x2),
			y2(a_y2)
		{
		}

		constexpr RECT(const RECT&) noexcept = default;
		constexpr RECT(RECT&&) noexcept = default;

		constexpr auto operator=(const RECT&) noexcept -> RECT& = default;
		constexpr auto operator=(RECT&&) noexcept -> RECT& = default;

		[[nodiscard]]
		constexpr auto operator==(const RECT&) const noexcept -> bool = default;
		[[nodiscard]]
		constexpr auto operator<=>(const RECT&) const noexcept = default;

		std::int32_t x1{0};
		std::int32_t y1{0};
		std::int32_t x2{0};
		std::int32_t y2{0};
	};

	static_assert(sizeof(RECT) == 0x10);

	struct SIZE
	{
		std::int32_t x;
		std::int32_t y;
	};

	static_assert(sizeof(SIZE) == 0x08);
}

namespace REX::W32
{
	struct WAVEFORMATEX
	{
		std::uint16_t formatTag;
		std::uint16_t channels;
		std::uint32_t samplesPerSec;
		std::uint32_t avgBytesPerSec;
		std::uint16_t blockAlign;
		std::uint16_t bitsPerSample;
		std::uint16_t size;
	};

	static_assert(sizeof(WAVEFORMATEX) == 0x14);

	struct WAVEFORMATEXTENSIBLE
	{
		WAVEFORMATEX format;

		union
		{
			std::uint16_t validBitsPerSample;
			std::uint16_t samplesPerBlock;
			std::uint16_t reserved;
		} samples;

		std::uint32_t channelMask;
		GUID subFormat;
	};

	static_assert(sizeof(WAVEFORMATEXTENSIBLE) == 0x2C);

	struct UNICODE_STRING
	{
		std::uint16_t length;
		std::uint16_t maxLength;
		wchar_t* buffer;
	};

	static_assert(sizeof(UNICODE_STRING) == 0x10);

	struct SECURITY_ATTRIBUTES
	{
		std::uint32_t length;
		void* securityDescriptor;
		BOOL inheritHandle;
	};

	static_assert(sizeof(SECURITY_ATTRIBUTES) == 0x18);

	struct OVERLAPPED
	{
		// members
		std::uintptr_t internal;
		std::uintptr_t internalHigh;

		union
		{
			struct
			{
				std::uint32_t offset;
				std::uint32_t offsetHigh;
			};

			void* ptr;
		};

		REX::W32::HANDLE hEvent;
	};

	static_assert(sizeof(OVERLAPPED) == 0x20);

	struct CRITICAL_SECTION
	{
		void* debugInfo;
		std::int32_t lockCount;
		std::int32_t recursionCount;
		HANDLE owningThread;
		HANDLE lockSemaphore;
		std::uintptr_t spinCount;
	};

	static_assert(sizeof(CRITICAL_SECTION) == 0x28);

	union LARGE_INTEGER
	{
		union
		{
			struct
			{
				std::uint32_t lowPart;
				std::int32_t highPart;
			};

			std::int64_t value;
		};
	};

	static_assert(sizeof(LARGE_INTEGER) == 0x08);

	union ULARGE_INTEGER
	{
		union
		{
			struct
			{
				std::uint32_t lowPart;
				std::uint32_t highPart;
			};

			std::uint64_t value;
		};
	};

	static_assert(sizeof(ULARGE_INTEGER) == 0x08);

}

namespace REX::W32
{
	[[nodiscard]]
	constexpr auto SUCCESS(const HRESULT a_result) noexcept -> bool
	{
		return a_result >= 0;
	}

	[[nodiscard]]
	constexpr auto NT_SUCCESS(const NTSTATUS a_status) noexcept -> bool
	{
		return a_status >= 0;
	}

	[[nodiscard]]
	constexpr auto SH_SUCCESS(std::int32_t a_result) noexcept -> bool
	{
		return a_result >= 0;
	}
}
