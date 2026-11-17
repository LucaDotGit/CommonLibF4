#pragma once

#include "REX/W32/CORE.hpp"
#include "REX/W32/DXGI_3.hpp"

namespace REX::W32
{
	struct IDXGIAdapter3;
	struct IDXGIFactory4;
	struct IDXGIOutput4;
	struct IDXGISwapChain3;
}

namespace REX::W32
{
	enum DXGI_MEMORY_SEGMENT_GROUP : std::int32_t
	{
		DXGI_MEMORY_SEGMENT_GROUP_LOCAL = 0,
		DXGI_MEMORY_SEGMENT_GROUP_NON_LOCAL = 1
	};

	enum DXGI_OVERLAY_COLOR_SPACE_SUPPORT_FLAG : std::uint32_t
	{
		DXGI_OVERLAY_COLOR_SPACE_SUPPORT_FLAG_PRESENT = 0x01
	};

	enum DXGI_SWAP_CHAIN_COLOR_SPACE_SUPPORT_FLAG : std::uint32_t
	{
		DXGI_SWAP_CHAIN_COLOR_SPACE_SUPPORT_FLAG_PRESENT = 0x01,
		DXGI_SWAP_CHAIN_COLOR_SPACE_SUPPORT_FLAG_OVERLAY_PRESENT = 0x02
	};
}

namespace REX::W32
{
	struct DXGI_QUERY_VIDEO_MEMORY_INFO
	{
		std::uint64_t budget;
		std::uint64_t currentUsage;
		std::uint64_t availableForReservation;
		std::uint64_t currentReservation;
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

	struct __declspec(novtable, uuid("645967A4-1392-4310-A798-8053CE3E93FD")) IDXGIAdapter3 : public IDXGIAdapter2
	{
		virtual auto RegisterHardwareContentProtectionTeardownStatusEvent(HANDLE a_event, std::uint32_t* a_cookie)
			-> HRESULT = 0;
		virtual void UnregisterHardwareContentProtectionTeardownStatus(std::uint32_t a_cookie) = 0;
		virtual auto QueryVideoMemoryInfo(
			std::uint32_t a_nodeIndex,
			DXGI_MEMORY_SEGMENT_GROUP a_memorySegmentGroup,
			DXGI_QUERY_VIDEO_MEMORY_INFO* a_videoMemoryInfo) -> HRESULT = 0;
		virtual auto SetVideoMemoryReservation(
			std::uint32_t a_nodeIndex,
			DXGI_MEMORY_SEGMENT_GROUP a_memorySegmentGroup,
			std::uint64_t a_reservation) -> HRESULT = 0;
		virtual auto RegisterVideoMemoryBudgetChangeNotificationEvent(HANDLE a_event, std::uint32_t* a_cookie)
			-> HRESULT = 0;
		virtual void UnregisterVideoMemoryBudgetChangeNotification(std::uint32_t a_cookie) = 0;
	};

	struct __declspec(novtable, uuid("1BC6EA02-EF36-464F-BF0C-21CA39E5168A")) IDXGIFactory4 : public IDXGIFactory3
	{
		virtual auto EnumAdapterByLuid(LUID a_luid, const IID& a_iid, void** a_adapter) -> HRESULT = 0;
		virtual auto EnumWarpAdapter(const IID& a_iid, void** a_adapter) -> HRESULT = 0;
	};

	struct __declspec(novtable, uuid("DC7DCA35-2196-414D-9F53-617884032A60")) IDXGIOutput4 : public IDXGIOutput3
	{
		virtual auto CheckOverlayColorSpaceSupport(
			DXGI_FORMAT a_format,
			DXGI_COLOR_SPACE_TYPE a_colorSpace,
			IUnknown* a_concernedDevice,
			std::uint32_t* a_flags) -> HRESULT = 0;
	};

	struct __declspec(novtable, uuid("94D99BDB-F1F8-4AB0-B236-7DA0170EDAB1")) IDXGISwapChain3 : public IDXGISwapChain2
	{
		virtual auto GetCurrentBackBufferIndex() -> std::uint32_t = 0;
		virtual auto CheckColorSpaceSupport(DXGI_COLOR_SPACE_TYPE a_colorSpace, std::uint32_t* a_colorSpaceSupport)
			-> HRESULT = 0;
		virtual auto SetColorSpace1(DXGI_COLOR_SPACE_TYPE a_colorSpace) -> HRESULT = 0;
		virtual auto ResizeBuffers1(
			std::uint32_t a_bufferCount,
			std::uint32_t a_width,
			std::uint32_t a_height,
			DXGI_FORMAT a_format,
			std::uint32_t a_swapChainFlags,
			const std::uint32_t* a_creationNodeMask,
			IUnknown* const* a_presentQueue) -> HRESULT = 0;
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
	inline constexpr auto IID_IDXGIAdapter3 =
		IID{0x6459'67A4, 0x1392, 0x4310, {0xA7, 0x98, 0x80, 0x53, 0xCE, 0x3E, 0x93, 0xFD}};
	inline constexpr auto IID_IDXGIFactory4 =
		IID{0x1BC6'EA02, 0xEF36, 0x464F, {0xBF, 0x0C, 0x21, 0xCA, 0x39, 0xE5, 0x16, 0x8A}};
	inline constexpr auto IID_IDXGIOutput4 =
		IID{0xDC7D'CA35, 0x2196, 0x414D, {0x9F, 0x53, 0x61, 0x78, 0x84, 0x03, 0x2A, 0x60}};
	inline constexpr auto IID_IDXGISwapChain3 =
		IID{0x94D9'9BDB, 0xF1F8, 0x4AB0, {0xB2, 0x36, 0x7D, 0xA0, 0x17, 0x0E, 0xDA, 0xB1}};
}
