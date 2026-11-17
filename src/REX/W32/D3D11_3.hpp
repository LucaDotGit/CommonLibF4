#pragma once

#include "REX/W32/CORE.hpp"
#include "REX/W32/D3D11_2.hpp"

namespace REX::W32
{
	struct ID3D11Device3;
	struct ID3D11DeviceContext3;
	struct ID3D11DeviceContext4;
	struct ID3D11Fence;
	struct ID3D11Query1;
	struct ID3D11RasterizerState2;
	struct ID3D11RenderTargetView1;
	struct ID3D11ShaderResourceView1;
	struct ID3D11Texture2D1;
	struct ID3D11Texture3D1;
	struct ID3D11UnorderedAccessView1;
}

namespace REX::W32
{
	enum D3D11_CONSERVATIVE_RASTERIZATION_MODE : std::int32_t
	{
		D3D11_CONSERVATIVE_RASTERIZATION_MODE_OFF = 0,
		D3D11_CONSERVATIVE_RASTERIZATION_MODE_ON = 1
	};

	enum D3D11_CONTEXT_TYPE : std::int32_t
	{
		D3D11_CONTEXT_TYPE_ALL = 0,
		D3D11_CONTEXT_TYPE_3D = 1,
		D3D11_CONTEXT_TYPE_COMPUTE = 2,
		D3D11_CONTEXT_TYPE_COPY = 3,
		D3D11_CONTEXT_TYPE_VIDEO = 4
	};

	enum D3D11_FENCE_FLAG : std::uint32_t
	{
		D3D11_FENCE_FLAG_SHARED = 0x02,
		D3D11_FENCE_FLAG_SHARED_CROSS_ADAPTER = 0x04,
		D3D11_FENCE_FLAG_NON_MONITORED = 0x08
	};

	enum D3D11_TEXTURE_LAYOUT : std::int32_t
	{
		D3D11_TEXTURE_LAYOUT_UNDEFINED = 0,
		D3D11_TEXTURE_LAYOUT_ROW_MAJOR = 1,
		D3D11_TEXTURE_LAYOUT_64K_STANDARD_SWIZZLE = 2
	};
}

namespace REX::W32
{
	struct D3D11_TEX2D_ARRAY_RTV1
	{
		std::uint32_t mipSlice;
		std::uint32_t firstArraySlice;
		std::uint32_t arraySize;
		std::uint32_t planeSlice;
	};

	struct D3D11_TEX2D_ARRAY_SRV1
	{
		std::uint32_t mostDetailedMip;
		std::uint32_t mipLevels;
		std::uint32_t firstArraySlice;
		std::uint32_t arraySize;
		std::uint32_t planeSlice;
	};

	struct D3D11_TEX2D_ARRAY_UAV1
	{
		std::uint32_t mipSlice;
		std::uint32_t firstArraySlice;
		std::uint32_t arraySize;
		std::uint32_t planeSlice;
	};

	struct D3D11_TEX2D_RTV1
	{
		std::uint32_t mipSlice;
		std::uint32_t planeSlice;
	};

	struct D3D11_TEX2D_SRV1
	{
		std::uint32_t mostDetailedMip;
		std::uint32_t mipLevels;
		std::uint32_t planeSlice;
	};

	struct D3D11_TEX2D_UAV1
	{
		std::uint32_t mipSlice;
		std::uint32_t planeSlice;
	};

	struct D3D11_QUERY_DESC1
	{
		D3D11_QUERY query;
		std::uint32_t miscFlags;
		D3D11_CONTEXT_TYPE contextType;
	};

	struct D3D11_RASTERIZER_DESC2
	{
		D3D11_FILL_MODE fillMode;
		D3D11_CULL_MODE cullMode;
		BOOL frontCounterClockwise;
		std::int32_t depthBias;
		REX::Float32 depthBiasClamp;
		REX::Float32 slopeScaledDepthBias;
		BOOL depthClipEnable;
		BOOL scissorEnable;
		BOOL multisampleEnable;
		BOOL antialiasedLineEnable;
		std::uint32_t forcedSampleCount;
		D3D11_CONSERVATIVE_RASTERIZATION_MODE conservativeRaster;
	};

	struct D3D11_RENDER_TARGET_VIEW_DESC1
	{
		DXGI_FORMAT format;
		D3D11_RTV_DIMENSION viewDimension;

		union
		{
			D3D11_BUFFER_RTV buffer;
			D3D11_TEX1D_RTV texture1D;
			D3D11_TEX1D_ARRAY_RTV texture1DArray;
			D3D11_TEX2D_RTV1 texture2D;
			D3D11_TEX2D_ARRAY_RTV1 texture2DArray;
			D3D11_TEX2DMS_RTV texture2DMS;
			D3D11_TEX2DMS_ARRAY_RTV texture2DMSArray;
			D3D11_TEX3D_RTV texture3D;
		};
	};

	struct D3D11_TEXTURE2D_DESC1
	{
		std::uint32_t width;
		std::uint32_t height;
		std::uint32_t mipLevels;
		std::uint32_t arraySize;
		DXGI_FORMAT format;
		DXGI_SAMPLE_DESC sampleDesc;
		D3D11_USAGE usage;
		std::uint32_t bindFlags;
		std::uint32_t cpuAccessFlags;
		std::uint32_t miscFlags;
		D3D11_TEXTURE_LAYOUT textureLayout;
	};

	struct D3D11_TEXTURE3D_DESC1
	{
		std::uint32_t width;
		std::uint32_t height;
		std::uint32_t depth;
		std::uint32_t mipLevels;
		DXGI_FORMAT format;
		D3D11_USAGE usage;
		std::uint32_t bindFlags;
		std::uint32_t cpuAccessFlags;
		std::uint32_t miscFlags;
		D3D11_TEXTURE_LAYOUT textureLayout;
	};

	struct D3D11_SHADER_RESOURCE_VIEW_DESC1
	{
		DXGI_FORMAT format;
		D3D11_SRV_DIMENSION viewDimension;

		union
		{
			D3D11_BUFFER_SRV buffer;
			D3D11_TEX1D_SRV texture1D;
			D3D11_TEX1D_ARRAY_SRV texture1DArray;
			D3D11_TEX2D_SRV1 texture2D;
			D3D11_TEX2D_ARRAY_SRV1 texture2DArray;
			D3D11_TEX2DMS_SRV texture2DMS;
			D3D11_TEX2DMS_ARRAY_SRV texture2DMSArray;
			D3D11_TEX3D_SRV texture3D;
			D3D11_TEXCUBE_SRV textureCube;
			D3D11_TEXCUBE_ARRAY_SRV textureCubeArray;
			D3D11_BUFFEREX_SRV bufferEx;
		};
	};

	struct D3D11_UNORDERED_ACCESS_VIEW_DESC1
	{
		DXGI_FORMAT format;
		D3D11_UAV_DIMENSION viewDimension;

		union
		{
			D3D11_BUFFER_UAV buffer;
			D3D11_TEX1D_UAV texture1D;
			D3D11_TEX1D_ARRAY_UAV texture1DArray;
			D3D11_TEX2D_UAV1 texture2D;
			D3D11_TEX2D_ARRAY_UAV1 texture2DArray;
			D3D11_TEX3D_UAV texture3D;
		};
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

	struct __declspec(novtable, uuid("A05C8C37-D2C6-4732-B3A0-9CE0B0DC9AE6")) ID3D11Device3 : public ID3D11Device2
	{
		virtual auto CreateTexture2D1(
			const D3D11_TEXTURE2D_DESC1* a_desc1,
			const D3D11_SUBRESOURCE_DATA* a_initialData,
			ID3D11Texture2D1** a_texture2D) -> HRESULT = 0;
		virtual auto CreateTexture3D1(
			const D3D11_TEXTURE3D_DESC1* a_desc1,
			const D3D11_SUBRESOURCE_DATA* a_initialData,
			ID3D11Texture3D1** a_texture3D) -> HRESULT = 0;
		virtual auto CreateRasterizerState2(
			const D3D11_RASTERIZER_DESC2* a_rasterizerDesc,
			ID3D11RasterizerState2** a_rasterizerState) -> HRESULT = 0;
		virtual auto CreateShaderResourceView1(
			ID3D11Resource* a_resource,
			const D3D11_SHADER_RESOURCE_VIEW_DESC1* a_desc1,
			ID3D11ShaderResourceView1** a_srView1) -> HRESULT = 0;
		virtual auto CreateUnorderedAccessView1(
			ID3D11Resource* a_resource,
			const D3D11_UNORDERED_ACCESS_VIEW_DESC1* a_desc1,
			ID3D11UnorderedAccessView1** a_uaView1) -> HRESULT = 0;
		virtual auto CreateRenderTargetView1(
			ID3D11Resource* a_resource,
			const D3D11_RENDER_TARGET_VIEW_DESC1* a_desc1,
			ID3D11RenderTargetView1** a_rtView1) -> HRESULT = 0;
		virtual auto CreateQuery1(const D3D11_QUERY_DESC1* a_queryDesc1, ID3D11Query1** a_query1) -> HRESULT = 0;
		virtual void GetImmediateContext3(ID3D11DeviceContext3** a_immediateContext) = 0;
		virtual auto CreateDeferredContext3(std::uint32_t a_contextFlags, ID3D11DeviceContext3** a_deferredContext)
			-> HRESULT = 0;
		virtual void WriteToSubresource(
			ID3D11Resource* a_targetResource,
			std::uint32_t a_targetSubresource,
			const D3D11_BOX* a_targetBox,
			const void* a_sourceData,
			std::uint32_t a_sourceRowPitch,
			std::uint32_t a_sourceDepthPitch) = 0;
		virtual void ReadFromSubresource(
			void* a_targetData,
			std::uint32_t a_targetRowPitch,
			std::uint32_t a_targetDepthPitch,
			ID3D11Resource* a_sourceResource,
			std::uint32_t a_sourceSubresource,
			const D3D11_BOX* a_sourceBox) = 0;
	};

	struct __declspec(novtable, uuid("B4E3C01D-E79E-4637-91B2-510E9F4C9B8F")) ID3D11DeviceContext3 :
		public ID3D11DeviceContext2
	{
		virtual void Flush1(D3D11_CONTEXT_TYPE a_contextType, HANDLE a_event) = 0;
		virtual void SetHardwareProtectionState(BOOL a_hwProtectionEnable) = 0;
		virtual void GetHardwareProtectionState(BOOL* a_hwProtectionEnable) = 0;
	};

	struct __declspec(novtable, uuid("917600DA-F58C-4C33-98D8-3E15B390FA24")) ID3D11DeviceContext4 :
		public ID3D11DeviceContext3
	{
		virtual auto Signal(ID3D11Fence* a_fence, std::uint64_t a_value) -> HRESULT = 0;
		virtual auto Wait(ID3D11Fence* a_fence, std::uint64_t a_value) -> HRESULT = 0;
	};

	struct __declspec(novtable, uuid("AFFDE9D1-1DF7-4BB7-8A34-0F46251DAB80")) ID3D11Fence : public ID3D11DeviceChild
	{
		virtual auto CreateSharedHandle(
			const SECURITY_ATTRIBUTES* a_attributes,
			std::uint32_t a_access,
			const wchar_t* a_name,
			HANDLE* a_handle) -> HRESULT = 0;
		virtual auto GetCompletedValue() -> std::uint64_t = 0;
		virtual auto SetEventOnCompletion(std::uint64_t a_value, HANDLE a_event) -> HRESULT = 0;
	};

	struct __declspec(novtable, uuid("631B4766-36DC-461D-8DB6-C47E13E60916")) ID3D11Query1 : public ID3D11Query
	{
		virtual void GetDesc1(D3D11_QUERY_DESC1* a_desc) = 0;
	};

	struct __declspec(novtable, uuid("6FBD02FB-209F-46C4-B059-2ED15586A6AC")) ID3D11RasterizerState2 :
		public ID3D11RasterizerState1
	{
		virtual void GetDesc2(D3D11_RASTERIZER_DESC2* a_desc) = 0;
	};

	struct __declspec(novtable, uuid("FFBE2E23-F011-418A-AC56-5CEED7C5B94B")) ID3D11RenderTargetView1 :
		public ID3D11RenderTargetView
	{
		virtual void GetDesc1(D3D11_RENDER_TARGET_VIEW_DESC1* a_desc1) = 0;
	};

	struct __declspec(novtable, uuid("91308B87-9040-411D-8C67-C39253CE3802")) ID3D11ShaderResourceView1 :
		public ID3D11ShaderResourceView
	{
		virtual void GetDesc1(D3D11_SHADER_RESOURCE_VIEW_DESC1* a_desc) = 0;
	};

	struct __declspec(novtable, uuid("51218251-1E33-4617-9CCB-4D3A4367E7BB")) ID3D11Texture2D1 : public ID3D11Texture2D
	{
		virtual void GetDesc1(D3D11_TEXTURE2D_DESC1* a_desc) = 0;
	};

	struct __declspec(novtable, uuid("0C711683-2853-4846-9BB0-F3E60639E46A")) ID3D11Texture3D1 : public ID3D11Texture3D
	{
		virtual void GetDesc1(D3D11_TEXTURE3D_DESC1* a_desc) = 0;
	};

	struct __declspec(novtable, uuid("7B3B6153-A886-4544-AB37-6537C8500403")) ID3D11UnorderedAccessView1 :
		public ID3D11UnorderedAccessView
	{
		virtual void GetDesc1(D3D11_UNORDERED_ACCESS_VIEW_DESC1* a_desc) = 0;
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
	inline constexpr auto IID_ID3D11Device3 =
		IID{0xA05C'8C37, 0xD2C6, 0x4732, {0xB3, 0xA0, 0x9C, 0xE0, 0xB0, 0xDC, 0x9A, 0xE6}};
	inline constexpr auto IID_ID3D11DeviceContext3 =
		IID{0xB4E3'C01D, 0xE79E, 0x4637, {0x91, 0xB2, 0x51, 0x0E, 0x9F, 0x4C, 0x9B, 0x8F}};
	inline constexpr auto IID_ID3D11DeviceContext4 =
		IID{0x9176'00DA, 0xF58C, 0x4C33, {0x98, 0xD8, 0x3E, 0x15, 0xB3, 0x90, 0xFA, 0x24}};
	inline constexpr auto IID_ID3D11Fence =
		IID{0xAFFD'E9D1, 0x1DF7, 0x4BB7, {0x8A, 0x34, 0x0F, 0x46, 0x25, 0x1D, 0xAB, 0x80}};
	inline constexpr auto IID_ID3D11Query1 =
		IID{0x631B'4766, 0x36DC, 0x461D, {0x8D, 0xB6, 0xC4, 0x7E, 0x13, 0xE6, 0x09, 0x16}};
	inline constexpr auto IID_ID3D11RasterizerState2 =
		IID{0x6FBD'02FB, 0x209F, 0x46C4, {0xB0, 0x59, 0x2E, 0xD1, 0x55, 0x86, 0xA6, 0xAC}};
	inline constexpr auto IID_ID3D11RenderTargetView1 =
		IID{0xFFBE'2E23, 0xF011, 0x418A, {0xAC, 0x56, 0x5C, 0xEE, 0xD7, 0xC5, 0xB9, 0x4B}};
	inline constexpr auto IID_ID3D11ShaderResourceView1 =
		IID{0x9130'8B87, 0x9040, 0x411D, {0x8C, 0x67, 0xC3, 0x92, 0x53, 0xCE, 0x38, 0x02}};
	inline constexpr auto IID_ID3D11Texture2D1 =
		IID{0x5121'8251, 0x1E33, 0x4617, {0x9C, 0xCB, 0x4D, 0x3A, 0x43, 0x67, 0xE7, 0xBB}};
	inline constexpr auto IID_ID3D11Texture3D1 =
		IID{0x0C71'1683, 0x2853, 0x4846, {0x9B, 0xB0, 0xF3, 0xE6, 0x06, 0x39, 0xE4, 0x6A}};
	inline constexpr auto IID_ID3D11UnorderedAccessView1 =
		IID{0x7B3B'6153, 0xA886, 0x4544, {0xAB, 0x37, 0x65, 0x37, 0xC8, 0x50, 0x04, 0x03}};
}
