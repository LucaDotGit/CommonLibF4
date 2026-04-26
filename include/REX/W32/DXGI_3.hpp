#pragma once

#include "REX/W32/DXGI_2.hpp"

namespace REX::W32
{
	struct IDXGIDecodeSwapChain;
	struct IDXGIDevice3;
	struct IDXGIFactory3;
	struct IDXGIFactoryMedia;
	struct IDXGIOutput2;
	struct IDXGIOutput3;
	struct IDXGISwapChain2;
	struct IDXGISwapChainMedia;
}

namespace REX::W32
{
	enum DXGI_FRAME_PRESENTATION_MODE : std::int32_t
	{
		DXGI_FRAME_PRESENTATION_MODE_COMPOSED = 0,
		DXGI_FRAME_PRESENTATION_MODE_OVERLAY = 1,
		DXGI_FRAME_PRESENTATION_MODE_NONE = 2,
		DXGI_FRAME_PRESENTATION_MODE_COMPOSITION_FAILURE = 3
	};

	enum DXGI_MULTIPLANE_OVERLAY_YCbCr_FLAGS : std::uint32_t
	{
		DXGI_MULTIPLANE_OVERLAY_YCbCr_FLAG_NOMINAL_RANGE = 0x1,
		DXGI_MULTIPLANE_OVERLAY_YCbCr_FLAG_BT709 = 0x2,
		DXGI_MULTIPLANE_OVERLAY_YCbCr_FLAG_xvYCC = 0x4
	};

	enum DXGI_OVERLAY_SUPPORT_FLAG : std::uint32_t
	{
		DXGI_OVERLAY_SUPPORT_FLAG_DIRECT = 0x1,
		DXGI_OVERLAY_SUPPORT_FLAG_SCALING = 0x2
	};
}

namespace REX::W32
{
	struct DXGI_DECODE_SWAP_CHAIN_DESC
	{
		std::uint32_t flags;
	};

	struct DXGI_FRAME_STATISTICS_MEDIA
	{
		std::uint32_t presentCount;
		std::uint32_t presentRefreshCount;
		std::uint32_t syncRefreshCount;
		std::int64_t syncQPCTime;
		std::int64_t syncGPUTime;
		DXGI_FRAME_PRESENTATION_MODE compositionMode;
		std::uint32_t approvedPresentDuration;
	};

	struct DXGI_MATRIX_3X2_F
	{
		REX::Float32 _11;
		REX::Float32 _12;
		REX::Float32 _21;
		REX::Float32 _22;
		REX::Float32 _31;
		REX::Float32 _32;
	};
}

namespace REX::W32
{
	struct __declspec(novtable, uuid("2633066B-4514-4C7A-8FD8-12EA98059D18"))
	IDXGIDecodeSwapChain
		: public IUnknown
	{
		virtual HRESULT PresentBuffer(std::uint32_t a_bufferToPresent, std::uint32_t a_syncInterval, std::uint32_t a_flags) = 0;
		virtual HRESULT SetSourceRect(const RECT* a_rect) = 0;
		virtual HRESULT SetTargetRect(const RECT* a_rect) = 0;
		virtual HRESULT SetDestSize(std::uint32_t a_width, std::uint32_t a_height) = 0;
		virtual HRESULT GetSourceRect(RECT* a_rect) = 0;
		virtual HRESULT GetTargetRect(RECT* a_rect) = 0;
		virtual HRESULT GetDestSize(std::uint32_t* a_width, std::uint32_t* a_height) = 0;
		virtual HRESULT SetColorSpace(DXGI_MULTIPLANE_OVERLAY_YCbCr_FLAGS a_colorSpace) = 0;
		virtual DXGI_MULTIPLANE_OVERLAY_YCbCr_FLAGS GetColorSpace() = 0;
	};

	struct __declspec(novtable, uuid("6007896C-3244-4AFD-BF18-A6D3BEDA5023"))
	IDXGIDevice3
		: public IDXGIDevice2
	{
		virtual void Trim() = 0;
	};

	struct __declspec(novtable, uuid("25483823-CD46-4C7D-86CA-47AA95B837BD"))
	IDXGIFactory3
		: public IDXGIFactory2
	{
		virtual std::uint32_t GetCreationFlags() = 0;
	};

	struct __declspec(novtable, uuid("41E7D1F2-A591-4F7B-A2E5-FA9C843E1C12"))
	IDXGIFactoryMedia
		: public IUnknown
	{
		virtual HRESULT CreateSwapChainForCompositionSurfaceHandle(IUnknown* a_device, HANDLE a_surface, const DXGI_SWAP_CHAIN_DESC1* a_desc, IDXGIOutput* a_restrictToOutput, IDXGISwapChain1** a_swapChain) = 0;
		virtual HRESULT CreateDecodeSwapChainForCompositionSurfaceHandle(IUnknown* a_device, HANDLE a_surface, DXGI_DECODE_SWAP_CHAIN_DESC* a_desc, IDXGIResource* a_yuvDecodeBuffers, IDXGIOutput* a_restrictToOutput, IDXGIDecodeSwapChain** a_swapChain) = 0;
	};

	struct __declspec(novtable, uuid("595E39D1-2724-4663-99B1-DA969DE28364"))
	IDXGIOutput2
		: public IDXGIOutput1
	{
		virtual BOOL SupportsOverlays() = 0;
	};

	struct __declspec(novtable, uuid("8A6BB301-7E7E-41F4-A8E0-5B32F7F99B18"))
	IDXGIOutput3
		: public IDXGIOutput2
	{
		virtual HRESULT CheckOverlaySupport(DXGI_FORMAT a_enumFormat, IUnknown* a_concernedDevice, std::uint32_t* a_flags) = 0;
	};

	struct __declspec(novtable, uuid("A8BE2AC4-199F-4946-B331-79599FB98DE7"))
	IDXGISwapChain2
		: public IDXGISwapChain1
	{
		virtual HRESULT SetSourceSize(std::uint32_t a_width, std::uint32_t a_height) = 0;
		virtual HRESULT GetSourceSize(std::uint32_t* a_width, std::uint32_t* a_height) = 0;
		virtual HRESULT SetMaximumFrameLatency(std::uint32_t a_maxLatency) = 0;
		virtual HRESULT GetMaximumFrameLatency(std::uint32_t* a_maxLatency) = 0;
		virtual HANDLE GetFrameLatencyWaitableObject() = 0;
		virtual HRESULT SetMatrixTransform(const DXGI_MATRIX_3X2_F* a_matrix) = 0;
		virtual HRESULT GetMatrixTransform(DXGI_MATRIX_3X2_F* a_matrix) = 0;
	};

	struct __declspec(novtable, uuid("DD95B90B-F05F-4F6A-BD65-25BFB264BD84"))
	IDXGISwapChainMedia
		: public IUnknown
	{
		virtual HRESULT GetFrameStatisticsMedia(DXGI_FRAME_STATISTICS_MEDIA* a_stats) = 0;
		virtual HRESULT SetPresentDuration(std::uint32_t a_duration) = 0;
		virtual HRESULT CheckPresentDurationSupport(std::uint32_t a_desiredPresentDuration, std::uint32_t* a_closestSmallerPresentDuration, std::uint32_t* a_closestLargerPresentDuration) = 0;
	};
}

namespace REX::W32
{
	inline constexpr auto IID_IDXGIDecodeSwapChain = IID{ 0x2633066B, 0x4514, 0x4C7A, { 0x8F, 0xD8, 0x12, 0xEA, 0x98, 0x05, 0x9D, 0x18 } };
	inline constexpr auto IID_IDXGIDevice3 = IID{ 0x6007896C, 0x3244, 0x4AFD, { 0xBF, 0x18, 0xA6, 0xD3, 0xBE, 0xDA, 0x50, 0x23 } };
	inline constexpr auto IID_IDXGIFactory3 = IID{ 0x25483823, 0xCD46, 0x4C7D, { 0x86, 0xCA, 0x47, 0xAA, 0x95, 0xB8, 0x37, 0xBD } };
	inline constexpr auto IID_IDXGIFactoryMedia = IID{ 0x41E7D1F2, 0xA591, 0x4F7B, { 0xA2, 0xE5, 0xFA, 0x9C, 0x84, 0x3E, 0x1C, 0x12 } };
	inline constexpr auto IID_IDXGIOutput2 = IID{ 0x595E39D1, 0x2724, 0x4663, { 0x99, 0xB1, 0xDA, 0x96, 0x9D, 0xE2, 0x83, 0x64 } };
	inline constexpr auto IID_IDXGIOutput3 = IID{ 0x8A6BB301, 0x7E7E, 0x41F4, { 0xA8, 0xE0, 0x5B, 0x32, 0xF7, 0xF9, 0x9B, 0x18 } };
	inline constexpr auto IID_IDXGISwapChain2 = IID{ 0xA8BE2AC4, 0x199F, 0x4946, { 0xB3, 0x31, 0x79, 0x59, 0x9F, 0xB9, 0x8D, 0xE7 } };
	inline constexpr auto IID_IDXGISwapChainMedia = IID{ 0xDD95B90B, 0xF05F, 0x4F6A, { 0xBD, 0x65, 0x25, 0xBF, 0xB2, 0x64, 0xBD, 0x84 } };
}
