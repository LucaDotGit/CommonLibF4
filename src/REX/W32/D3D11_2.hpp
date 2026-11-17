#pragma once

#include "REX/W32/CORE.hpp"
#include "REX/W32/D3D11_1.hpp"

namespace REX::W32
{
	struct ID3D11Device2;
	struct ID3D11DeviceContext2;
}

namespace REX::W32
{
	enum D3D11_CHECK_MULTISAMPLE_QUALITY_LEVELS_FLAG : std::uint32_t
	{
		D3D11_CHECK_MULTISAMPLE_QUALITY_LEVELS_TILED_RESOURCE = 0x01
	};

	enum D3D11_TILE_COPY_FLAG : std::uint32_t
	{
		D3D11_TILE_COPY_NO_OVERWRITE = 0x01,
		D3D11_TILE_COPY_LINEAR_BUFFER_TO_SWIZZLED_TILED_RESOURCE = 0x02,
		D3D11_TILE_COPY_SWIZZLED_TILED_RESOURCE_TO_LINEAR_BUFFER = 0x04
	};

	enum D3D11_TILE_MAPPING_FLAG : std::uint32_t
	{
		D3D11_TILE_MAPPING_NO_OVERWRITE = 0x01
	};

	enum D3D11_TILE_RANGE_FLAG : std::uint32_t
	{
		D3D11_TILE_RANGE_NULL = 0x01,
		D3D11_TILE_RANGE_SKIP = 0x02,
		D3D11_TILE_RANGE_REUSE_SINGLE_TILE = 0x04
	};
}

namespace REX::W32
{
	struct D3D11_PACKED_MIP_DESC
	{
		std::uint8_t numStandardMips;
		std::uint8_t numPackedMips;
		std::uint32_t numTilesForPackedMips;
		std::uint32_t startTileIndexInOverallResource;
	};

	struct D3D11_SUBRESOURCE_TILING
	{
		std::uint32_t widthInTiles;
		std::uint16_t heightInTiles;
		std::uint16_t depthInTiles;
		std::uint32_t startTileIndexInOverallResource;
	};

	struct D3D11_TILED_RESOURCE_COORDINATE
	{
		std::uint32_t x;
		std::uint32_t y;
		std::uint32_t z;
		std::uint32_t subResource;
	};

	struct D3D11_TILE_REGION_SIZE
	{
		std::uint32_t numTiles;
		BOOL bUseBox;
		std::uint32_t width;
		std::uint16_t height;
		std::uint16_t depth;
	};

	struct D3D11_TILE_SHAPE
	{
		std::uint32_t widthInTexels;
		std::uint32_t heightInTexels;
		std::uint32_t depthInTexels;
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

	struct __declspec(novtable, uuid("9D06DFFA-D1E5-4D07-83A8-1BB123F2F841")) ID3D11Device2 : public ID3D11Device1
	{
		virtual void GetImmediateContext2(ID3D11DeviceContext2** a_immediateContext) = 0;
		virtual auto CreateDeferredContext2(std::uint32_t a_contextFlags, ID3D11DeviceContext2** a_deferredContext)
			-> HRESULT = 0;
		virtual void GetResourceTiling(
			ID3D11Resource* a_tiledResource,
			std::uint32_t* a_numTilesForEntireResource,
			D3D11_PACKED_MIP_DESC* a_packedMipDesc,
			D3D11_TILE_SHAPE* a_standardTileShapeForNonPackedMips,
			std::uint32_t* a_numSubresourceTilings,
			std::uint32_t a_firstSubResourceTilingToGet,
			D3D11_SUBRESOURCE_TILING* a_subResourceTilingsForNonPackedMips) = 0;
		virtual auto CheckMultisampleQualityLevels1(
			DXGI_FORMAT a_format,
			std::uint32_t a_sampleCount,
			std::uint32_t a_flags,
			std::uint32_t* a_numQualityLevels) -> HRESULT = 0;
	};

	struct __declspec(novtable, uuid("420D5B32-B90C-4DA4-BEF0-359F6A24A83A")) ID3D11DeviceContext2 :
		public ID3D11DeviceContext1
	{
		virtual auto UpdateTileMappings(
			ID3D11Resource* a_tiledResource,
			std::uint32_t numTiledResourceRegions,
			const D3D11_TILED_RESOURCE_COORDINATE* a_tiledResourceRegionStartCoordinates,
			const D3D11_TILE_REGION_SIZE* a_tiledResourceRegionSizes,
			ID3D11Buffer* a_tilePool,
			std::uint32_t a_numRanges,
			const std::uint32_t* a_rangeFlags,
			const std::uint32_t* a_tilePoolStartOffsets,
			const std::uint32_t* a_rangeTileCounts,
			std::uint32_t a_flags) -> HRESULT = 0;
		virtual auto CopyTileMappings(
			ID3D11Resource* a_destTiledResource,
			const D3D11_TILED_RESOURCE_COORDINATE* a_destRegionStartCoordinate,
			ID3D11Resource* a_sourceTiledResource,
			const D3D11_TILED_RESOURCE_COORDINATE* a_sourceRegionStartCoordinate,
			const D3D11_TILE_REGION_SIZE* a_tileRegionSize,
			std::uint32_t a_flags) -> HRESULT = 0;
		virtual void CopyTiles(
			ID3D11Resource* a_tiledResource,
			const D3D11_TILED_RESOURCE_COORDINATE* a_tileRegionStartCoordinate,
			const D3D11_TILE_REGION_SIZE* a_tileRegionSize,
			ID3D11Buffer* a_buffer,
			std::uint64_t a_bufferStartOffsetInBytes,
			std::uint32_t a_flags) = 0;
		virtual void UpdateTiles(
			ID3D11Resource* a_destTiledResource,
			const D3D11_TILED_RESOURCE_COORDINATE* a_destTileRegionStartCoordinate,
			const D3D11_TILE_REGION_SIZE* a_destTileRegionSize,
			const void* a_sourceTileData,
			std::uint32_t a_flags) = 0;
		virtual auto ResizeTilePool(ID3D11Buffer* a_tilePool, std::uint64_t a_newSizeInBytes) -> HRESULT = 0;
		virtual void TiledResourceBarrier(
			ID3D11DeviceChild* a_tiledResourceOrViewAccessBeforeBarrier,
			ID3D11DeviceChild* a_tiledResourceOrViewAccessAfterBarrier) = 0;
		virtual auto IsAnnotationEnabled() -> BOOL = 0;
		virtual void SetMarkerInt(const wchar_t* a_label, std::int32_t a_data) = 0;
		virtual void BeginEventInt(const wchar_t* a_label, std::int32_t a_data) = 0;
		virtual void EndEvent() = 0;
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
	inline constexpr auto IID_ID3D11Device2 =
		IID{0x9D06'DFFA, 0xD1E5, 0x4D07, {0x83, 0xA8, 0x1B, 0xB1, 0x23, 0xF2, 0xF8, 0x41}};
	inline constexpr auto IID_ID3D11DeviceContext2 =
		IID{0x420D'5B32, 0xB90C, 0x4DA4, {0xBE, 0xF0, 0x35, 0x9F, 0x6A, 0x24, 0xA8, 0x3A}};
}
