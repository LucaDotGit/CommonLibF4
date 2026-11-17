#pragma once

#include "REX/StaticString.hpp"
#include "REX/W32/CORE.hpp"
#include "REX/W32/DXGI_5.hpp"

namespace REX::W32
{
	struct IDXGIAdapter4;
	struct IDXGIFactory6;
	struct IDXGIFactory7;
	struct IDXGIOutput6;
}

namespace REX::W32
{
	enum DXGI_ADAPTER_FLAG3 : std::int32_t
	{
		DXGI_ADAPTER_FLAG3_REMOTE = 0x01,
		DXGI_ADAPTER_FLAG3_SOFTWARE = 0x02,
		DXGI_ADAPTER_FLAG3_ACG_COMPATIBLE = 0x04,
		DXGI_ADAPTER_FLAG3_SUPPORT_MONITORED_FENCES = 0x08,
		DXGI_ADAPTER_FLAG3_SUPPORT_NON_MONITORED_FENCES = 0x10,
		DXGI_ADAPTER_FLAG3_KEYED_MUTEX_CONFORMANCE = 0x20,
		DXGI_ADAPTER_FLAG3_FORCE_DWORD =
			static_cast<std::underlying_type_t<DXGI_ADAPTER_FLAG3>>(std::numeric_limits<std::uint32_t>::max())
	};

	enum DXGI_GPU_PREFERENCE : std::int32_t
	{
		DXGI_GPU_PREFERENCE_UNSPECIFIED = 0,
		DXGI_GPU_PREFERENCE_MINIMUM_POWER = 1,
		DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE = 2
	};

	enum DXGI_HARDWARE_COMPOSITION_SUPPORT_FLAGS : std::uint32_t
	{
		DXGI_HARDWARE_COMPOSITION_SUPPORT_FLAG_FULLSCREEN = 0x01,
		DXGI_HARDWARE_COMPOSITION_SUPPORT_FLAG_WINDOWED = 0x02,
		DXGI_HARDWARE_COMPOSITION_SUPPORT_FLAG_CURSOR_STRETCHED = 0x04
	};
}

namespace REX::W32
{
	struct DXGI_ADAPTER_DESC3
	{
		REX::StaticWString<0x40> description;
		std::uint32_t vendorID;
		std::uint32_t deviceID;
		std::uint32_t subSysID;
		std::uint32_t revision;
		std::size_t dedicatedVideoMemory;
		std::size_t dedicatedSystemMemory;
		std::size_t sharedSystemMemory;
		LUID adapterLUID;
		DXGI_ADAPTER_FLAG3 flags;
		DXGI_GRAPHICS_PREEMPTION_GRANULARITY graphicsPreemptionGranularity;
		DXGI_COMPUTE_PREEMPTION_GRANULARITY computePreemptionGranularity;
	};

	struct DXGI_OUTPUT_DESC1
	{
		REX::StaticWString<0x10> deviceName;
		RECT desktopCoordinates;
		BOOL attachedToDesktop;
		DXGI_MODE_ROTATION rotation;
		HMONITOR monitor;
		std::uint32_t bitsPerColor;
		DXGI_COLOR_SPACE_TYPE colorSpace;
		std::array<REX::Float32, 2> redPrimary;
		std::array<REX::Float32, 2> greenPrimary;
		std::array<REX::Float32, 2> bluePrimary;
		std::array<REX::Float32, 2> whitePoint;
		REX::Float32 minLuminance;
		REX::Float32 maxLuminance;
		REX::Float32 maxFullFrameLuminance;
	};
}

namespace REX::W32
{
#if (__clang__ == 1)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"
#endif

#if (_MSC_VER > 0l)
#pragma warning(push)
#pragma warning(disable : 4'265)
#endif

	// NOLINTBEGIN(cppcoreguidelines-virtual-class-destructor)

	struct __declspec(novtable, uuid("3C8D99D1-4FBF-4181-A82C-AF66BF7BD24E")) IDXGIAdapter4 : public IDXGIAdapter3
	{
		virtual auto GetDesc3(DXGI_ADAPTER_DESC3* a_desc) -> HRESULT = 0;
	};

	struct __declspec(novtable, uuid("C1B6694F-FF09-44A9-B03C-77900A0A1D17")) IDXGIFactory6 : public IDXGIFactory5
	{
		virtual auto EnumAdapterByGpuPreference(
			std::uint32_t a_adapterFlags,
			DXGI_GPU_PREFERENCE a_gpuPreference,
			const IID& a_iid,
			void** a_adapter) -> HRESULT = 0;
	};

	struct __declspec(novtable, uuid("A4966EED-76DB-44DA-84C1-EE9A7AFB20A8")) IDXGIFactory7 : public IDXGIFactory6
	{
		virtual auto RegisterAdaptersChangedEvent(HANDLE a_event, std::uint32_t* a_cookie) -> HRESULT = 0;
		virtual auto UnregisterAdaptersChangedEvent(std::uint32_t a_cookie) -> HRESULT = 0;
	};

	struct __declspec(novtable, uuid("068346E8-AAEC-4B84-ADD7-137F513F77A1")) IDXGIOutput6 : public IDXGIOutput5
	{
		virtual auto GetDesc1(DXGI_OUTPUT_DESC1* a_desc) -> HRESULT = 0;
		virtual auto CheckHardwareCompositionSupport(std::uint32_t* a_flags) -> HRESULT = 0;
	};

	// NOLINTEND(cppcoreguidelines-virtual-class-destructor)

#if (_MSC_VER > 0l)
#pragma warning(pop)
#endif

#if (__clang__ == 1)
#pragma clang diagnostic pop
#endif
}

namespace REX::W32
{
	inline constexpr auto IID_IDXGIAdapter4 =
		IID{0x3C8D'99D1, 0x4FBF, 0x4181, {0xA8, 0x2C, 0xAF, 0x66, 0xBF, 0x7B, 0xD2, 0x4E}};
	inline constexpr auto IID_IDXGIFactory6 =
		IID{0xC1B6'694F, 0xFF09, 0x44A9, {0xB0, 0x3C, 0x77, 0x90, 0x0A, 0x0A, 0x1D, 0x17}};
	inline constexpr auto IID_IDXGIFactory7 =
		IID{0xA496'6EED, 0x76DB, 0x44DA, {0x84, 0xC1, 0xEE, 0x9A, 0x7A, 0xFB, 0x20, 0xA8}};
	inline constexpr auto IID_IDXGIOutput6 =
		IID{0x0683'46E8, 0xAAEC, 0x4B84, {0xAD, 0xD7, 0x13, 0x7F, 0x51, 0x3F, 0x77, 0xA1}};
}
