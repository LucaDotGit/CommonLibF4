#pragma once

#include "REX/StaticString.hpp"
#include "REX/W32/CORE.hpp"
#include "REX/W32/DXGI.hpp"

namespace REX::W32
{
	struct IDXGIAdapter2;
	struct IDXGIDevice2;
	struct IDXGIDisplayControl;
	struct IDXGIFactory2;
	struct IDXGIOutput1;
	struct IDXGIOutputDuplication;
	struct IDXGIResource1;
	struct IDXGISurface2;
	struct IDXGISwapChain1;
}

namespace REX::W32
{
	enum DXGI_ALPHA_MODE : std::int32_t
	{
		DXGI_ALPHA_MODE_UNSPECIFIED = 0,
		DXGI_ALPHA_MODE_PREMULTIPLIED = 1,
		DXGI_ALPHA_MODE_STRAIGHT = 2,
		DXGI_ALPHA_MODE_IGNORE = 3,
		DXGI_ALPHA_MODE_FORCE_DWORD = -1
	};

	enum DXGI_COMPUTE_PREEMPTION_GRANULARITY : std::int32_t
	{
		DXGI_COMPUTE_PREEMPTION_DMA_BUFFER_BOUNDARY = 0,
		DXGI_COMPUTE_PREEMPTION_DISPATCH_BOUNDARY = 1,
		DXGI_COMPUTE_PREEMPTION_THREAD_GROUP_BOUNDARY = 2,
		DXGI_COMPUTE_PREEMPTION_THREAD_BOUNDARY = 3,
		DXGI_COMPUTE_PREEMPTION_INSTRUCTION_BOUNDARY = 4
	};

	enum DXGI_GRAPHICS_PREEMPTION_GRANULARITY : std::int32_t
	{
		DXGI_GRAPHICS_PREEMPTION_DMA_BUFFER_BOUNDARY = 0,
		DXGI_GRAPHICS_PREEMPTION_PRIMITIVE_BOUNDARY = 1,
		DXGI_GRAPHICS_PREEMPTION_TRIANGLE_BOUNDARY = 2,
		DXGI_GRAPHICS_PREEMPTION_PIXEL_BOUNDARY = 3,
		DXGI_GRAPHICS_PREEMPTION_INSTRUCTION_BOUNDARY = 4
	};

	enum DXGI_OFFER_RESOURCE_PRIORITY : std::int32_t
	{
		DXGI_OFFER_RESOURCE_PRIORITY_LOW = 1,
		DXGI_OFFER_RESOURCE_PRIORITY_NORMAL = 2,
		DXGI_OFFER_RESOURCE_PRIORITY_HIGH = 3
	};

	enum DXGI_OUTDUPL_POINTER_SHAPE_TYPE : std::int32_t
	{
		DXGI_OUTDUPL_POINTER_SHAPE_TYPE_MONOCHROME = 0x01,
		DXGI_OUTDUPL_POINTER_SHAPE_TYPE_COLOR = 0x02,
		DXGI_OUTDUPL_POINTER_SHAPE_TYPE_MASKED_COLOR = 0x04
	};

	enum DXGI_SCALING : std::int32_t
	{
		DXGI_SCALING_STRETCH = 0,
		DXGI_SCALING_NONE = 1,
		DXGI_SCALING_ASPECT_RATIO_STRETCH = 2
	};
}

namespace REX::W32
{
	struct DXGI_ADAPTER_DESC2
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
		std::uint32_t flags;
		DXGI_GRAPHICS_PREEMPTION_GRANULARITY graphicsPreemptionGranularity;
		DXGI_COMPUTE_PREEMPTION_GRANULARITY computePreemptionGranularity;
	};

	struct DXGI_MODE_DESC1
	{
		std::uint32_t width;
		std::uint32_t height;
		DXGI_RATIONAL refreshRate;
		DXGI_FORMAT format;
		DXGI_MODE_SCANLINE_ORDER scanlineOrdering;
		DXGI_MODE_SCALING scaling;
		BOOL stereo;
	};

	struct DXGI_OUTDUPL_DESC
	{
		DXGI_MODE_DESC modeDesc;
		DXGI_MODE_ROTATION rotation;
		BOOL desktopImageInSystemMemory;
	};

	struct DXGI_OUTDUPL_POINTER_POSITION
	{
		POINT position;
		BOOL visible;
	};

	struct DXGI_OUTDUPL_FRAME_INFO
	{
		std::int64_t lastPresentTime;
		std::int64_t lastMouseUpdateTime;
		std::uint32_t accumulatedFrames;
		BOOL rectsCoalesced;
		BOOL protectedContentMaskedOut;
		DXGI_OUTDUPL_POINTER_POSITION pointerPosition;
		std::uint32_t totalMetadataBufferSize;
		std::uint32_t pointerShapeBufferSize;
	};

	struct DXGI_OUTDUPL_MOVE_RECT
	{
		POINT sourcePoint;
		RECT destinationRect;
	};

	struct DXGI_OUTDUPL_POINTER_SHAPE_INFO
	{
		std::uint32_t type;
		std::uint32_t width;
		std::uint32_t height;
		std::uint32_t pitch;
		POINT hotSpot;
	};

	struct DXGI_PRESENT_PARAMETERS
	{
		std::uint32_t dirtyRectsCount;
		RECT* dirtyRects;
		RECT* scrollRect;
		POINT* scrollOffset;
	};

	struct DXGI_SWAP_CHAIN_DESC1
	{
		std::uint32_t width;
		std::uint32_t height;
		DXGI_FORMAT format;
		BOOL stereo;
		DXGI_SAMPLE_DESC sampleDesc;
		DXGI_USAGE bufferUsage;
		std::uint32_t bufferCount;
		DXGI_SCALING scaling;
		DXGI_SWAP_EFFECT swapEffect;
		DXGI_ALPHA_MODE alphaMode;
		std::uint32_t flags;
	};

	struct DXGI_SWAP_CHAIN_FULLSCREEN_DESC
	{
		DXGI_RATIONAL refreshRate;
		DXGI_MODE_SCANLINE_ORDER scanlineOrdering;
		DXGI_MODE_SCALING scaling;
		BOOL windowed;
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

	struct __declspec(novtable, uuid("0AA1AE0A-FA0E-4B84-8644-E05FF8E5ACB5")) IDXGIAdapter2 : public IDXGIAdapter1
	{
		virtual auto GetDesc2(DXGI_ADAPTER_DESC2* a_desc) -> HRESULT = 0;
	};

	struct __declspec(novtable, uuid("05008617-FBFD-4051-A790-144884B4F6A9")) IDXGIDevice2 : public IDXGIDevice1
	{
		virtual auto OfferResources(
			std::uint32_t a_numResources,
			IDXGIResource* const* a_resources,
			DXGI_OFFER_RESOURCE_PRIORITY a_priority) -> HRESULT = 0;
		virtual auto ReclaimResources(
			std::uint32_t a_numResources,
			IDXGIResource* const* a_resources,
			BOOL* a_discarded) -> HRESULT = 0;
		virtual auto EnqueueSetEvent(HANDLE a_event) -> HRESULT = 0;
	};

	struct __declspec(novtable, uuid("EA9DBF1A-C88E-4486-854A-98AA0138F30C")) IDXGIDisplayControl : public IUnknown
	{
		virtual auto IsStereoEnabled() -> BOOL = 0;
		virtual void SetStereoEnabled(BOOL a_enabled) = 0;
	};

	struct __declspec(novtable, uuid("50C83A1C-E072-4C48-87B0-3630FA36A6D0")) IDXGIFactory2 : public IDXGIFactory1
	{
		virtual auto IsWindowedStereoEnabled() -> BOOL = 0;
		virtual auto CreateSwapChainForHwnd(
			IUnknown* a_device,
			HWND a_wnd,
			const DXGI_SWAP_CHAIN_DESC1* a_desc,
			const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* a_fullscreenDesc,
			IDXGIOutput* a_restrictToOutput,
			IDXGISwapChain1** a_swapChain) -> HRESULT = 0;
		virtual auto CreateSwapChainForCoreWindow(
			IUnknown* a_device,
			IUnknown* a_window,
			const DXGI_SWAP_CHAIN_DESC1* a_desc,
			IDXGIOutput* a_restrictToOutput,
			IDXGISwapChain1** a_swapChain) -> HRESULT = 0;
		virtual auto GetSharedResourceAdapterLuid(HANDLE a_resource, LUID* a_luid) -> HRESULT = 0;
		virtual auto RegisterStereoStatusWindow(HWND a_wnd, std::uint32_t a_msg, std::uint32_t* a_cookie)
			-> HRESULT = 0;
		virtual auto RegisterStereoStatusEvent(HANDLE a_event, std::uint32_t* a_cookie) -> HRESULT = 0;
		virtual void UnregisterStereoStatus(std::uint32_t a_cookie) = 0;
		virtual auto RegisterOcclusionStatusWindow(HWND a_wnd, std::uint32_t a_msg, std::uint32_t* a_cookie)
			-> HRESULT = 0;
		virtual auto RegisterOcclusionStatusEvent(HANDLE a_event, std::uint32_t* a_cookie) -> HRESULT = 0;
		virtual void UnregisterOcclusionStatus(std::uint32_t dwCookie) = 0;
		virtual auto CreateSwapChainForComposition(
			IUnknown* a_device,
			const DXGI_SWAP_CHAIN_DESC1* a_desc,
			IDXGIOutput* a_restrictToOutput,
			IDXGISwapChain1** a_swapChain) -> HRESULT = 0;
	};

	struct __declspec(novtable, uuid("00CDDEA8-939B-4B83-A340-A685226666CC")) IDXGIOutput1 : public IDXGIOutput
	{
		virtual auto GetDisplayModeList1(
			DXGI_FORMAT a_enumFormat,
			std::uint32_t a_flags,
			std::uint32_t* a_numModes,
			DXGI_MODE_DESC1* a_desc) -> HRESULT = 0;
		virtual auto FindClosestMatchingMode1(
			const DXGI_MODE_DESC1* a_modeToMatch,
			DXGI_MODE_DESC1* a_closestMatch,
			IUnknown* a_concernedDevice) -> HRESULT = 0;
		virtual auto GetDisplaySurfaceData1(IDXGIResource* a_destination) -> HRESULT = 0;
		virtual auto DuplicateOutput(IUnknown* a_device, IDXGIOutputDuplication** a_outputDuplication) -> HRESULT = 0;
	};

	struct __declspec(novtable, uuid("191CFAC3-A341-470D-B26E-A864F428319C")) IDXGIOutputDuplication :
		public IDXGIObject
	{
		virtual void GetDesc(DXGI_OUTDUPL_DESC* a_desc) = 0;
		virtual auto AcquireNextFrame(
			std::uint32_t a_timeoutInMilliseconds,
			DXGI_OUTDUPL_FRAME_INFO* a_frameInfo,
			IDXGIResource** a_desktopResource) -> HRESULT = 0;
		virtual auto GetFrameDirtyRects(
			std::uint32_t a_dirtyRectsBufferSize,
			RECT* a_dirtyRectsBuffer,
			std::uint32_t* a_dirtyRectsBufferSizeRequired) -> HRESULT = 0;
		virtual auto GetFrameMoveRects(
			std::uint32_t a_moveRectsBufferSize,
			DXGI_OUTDUPL_MOVE_RECT* a_moveRectBuffer,
			std::uint32_t* a_moveRectsBufferSizeRequired) -> HRESULT = 0;
		virtual auto GetFramePointerShape(
			std::uint32_t a_pointerShapeBufferSize,
			void* a_pointerShapeBuffer,
			std::uint32_t* a_pointerShapeBufferSizeRequired,
			DXGI_OUTDUPL_POINTER_SHAPE_INFO* a_pointerShapeInfo) -> HRESULT = 0;
		virtual auto MapDesktopSurface(DXGI_MAPPED_RECT* a_lockedRect) -> HRESULT = 0;
		virtual auto UnMapDesktopSurface() -> HRESULT = 0;
		virtual auto ReleaseFrame() -> HRESULT = 0;
	};

	struct __declspec(novtable, uuid("30961379-4609-4A41-998E-54FE567EE0C1")) IDXGIResource1 : public IDXGIResource
	{
		virtual auto CreateSubresourceSurface(std::uint32_t a_index, IDXGISurface2** a_surface) -> HRESULT = 0;
		virtual auto CreateSharedHandle(
			const SECURITY_ATTRIBUTES* a_attributes,
			std::uint32_t a_access,
			const wchar_t* a_name,
			HANDLE* a_handle) -> HRESULT = 0;
	};

	struct __declspec(novtable, uuid("ABA496DD-B617-4CB8-A866-BC44D7EB1FA2")) IDXGISurface2 : public IDXGISurface1
	{
		virtual auto GetResource(const IID& a_iid, void** a_parentResource, std::uint32_t* a_subresourceIndex)
			-> HRESULT = 0;
	};

	struct __declspec(novtable, uuid("790A45F7-0D42-4876-983A-0A55CFE6F4AA")) IDXGISwapChain1 : public IDXGISwapChain
	{
		virtual auto GetDesc1(DXGI_SWAP_CHAIN_DESC1* a_desc) -> HRESULT = 0;
		virtual auto GetFullscreenDesc(DXGI_SWAP_CHAIN_FULLSCREEN_DESC* a_desc) -> HRESULT = 0;
		virtual auto GetHwnd(HWND* a_wnd) -> HRESULT = 0;
		virtual auto GetCoreWindow(const IID& a_iid, void** a_unk) -> HRESULT = 0;
		virtual auto Present1(
			std::uint32_t a_syncInterval,
			std::uint32_t a_presentFlags,
			const DXGI_PRESENT_PARAMETERS* a_presentParameters) -> HRESULT = 0;
		virtual auto IsTemporaryMonoSupported() -> BOOL = 0;
		virtual auto GetRestrictToOutput(IDXGIOutput** a_restrictToOutput) -> HRESULT = 0;
		virtual auto SetBackgroundColor(const DXGI_RGBA* a_color) -> HRESULT = 0;
		virtual auto GetBackgroundColor(DXGI_RGBA* a_color) -> HRESULT = 0;
		virtual auto SetRotation(DXGI_MODE_ROTATION a_rotation) -> HRESULT = 0;
		virtual auto GetRotation(DXGI_MODE_ROTATION* a_rotation) -> HRESULT = 0;
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
	inline constexpr auto IID_IDXGIAdapter2 =
		IID{0x0AA1'AE0A, 0xFA0E, 0x4B84, {0x86, 0x44, 0xE0, 0x5F, 0xF8, 0xE5, 0xAC, 0xB5}};
	inline constexpr auto IID_IDXGIDevice2 =
		IID{0x0500'8617, 0xFBFD, 0x4051, {0xA7, 0x90, 0x14, 0x48, 0x84, 0xB4, 0xF6, 0xA9}};
	inline constexpr auto IID_IDXGIDisplayControl =
		IID{0xEA9D'BF1A, 0xC88E, 0x4486, {0x85, 0x4A, 0x98, 0xAA, 0x01, 0x38, 0xF3, 0x0C}};
	inline constexpr auto IID_IDXGIFactory2 =
		IID{0x50C8'3A1C, 0xE072, 0x4C48, {0x87, 0xB0, 0x36, 0x30, 0xFA, 0x36, 0xA6, 0xD0}};
	inline constexpr auto IID_IDXGIOutput1 =
		IID{0x00CD'DEA8, 0x939B, 0x4B83, {0xA3, 0x40, 0xA6, 0x85, 0x22, 0x66, 0x66, 0xCC}};
	inline constexpr auto IID_IDXGIOutputDuplication =
		IID{0x191C'FAC3, 0xA341, 0x470D, {0xB2, 0x6E, 0xA8, 0x64, 0xF4, 0x28, 0x31, 0x9C}};
	inline constexpr auto IID_IDXGIResource1 =
		IID{0x3096'1379, 0x4609, 0x4A41, {0x99, 0x8E, 0x54, 0xFE, 0x56, 0x7E, 0xE0, 0xC1}};
	inline constexpr auto IID_IDXGISurface2 =
		IID{0xABA4'96DD, 0xB617, 0x4CB8, {0xA8, 0x66, 0xBC, 0x44, 0xD7, 0xEB, 0x1F, 0xA2}};
	inline constexpr auto IID_IDXGISwapChain1 =
		IID{0x790A'45F7, 0x0D42, 0x4876, {0x98, 0x3A, 0x0A, 0x55, 0xCF, 0xE6, 0xF4, 0xAA}};
}
