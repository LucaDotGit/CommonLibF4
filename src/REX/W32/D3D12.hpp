#pragma once

#include "REX/W32/CORE.hpp"

namespace REX::W32
{
	struct ID3D12CommandAllocator;
	struct ID3D12CommandList;
	struct ID3D12CommandQueue;
	struct ID3D12DescriptorHeap;
	struct ID3D12Device;
	struct ID3D12DeviceChild;
	struct ID3D12Fence;
	struct ID3D12GraphicsCommandList;
	struct ID3D12Heap;
	struct ID3D12Object;
	struct ID3D12Pageable;
	struct ID3D12PipelineState;
	struct ID3D12Resource;
	struct ID3D12RootSignature;

	struct D3D12_CLEAR_VALUE;
	struct D3D12_COMMAND_SIGNATURE_DESC;
	struct D3D12_COMPUTE_PIPELINE_STATE_DESC;
	struct D3D12_CONSTANT_BUFFER_VIEW_DESC;
	struct D3D12_DEPTH_STENCIL_VIEW_DESC;
	struct D3D12_DESCRIPTOR_HEAP_DESC;
	struct D3D12_GRAPHICS_PIPELINE_STATE_DESC;
	struct D3D12_HEAP_DESC;
	struct D3D12_PACKED_MIP_INFO;
	struct D3D12_PLACED_SUBRESOURCE_FOOTPRINT;
	struct D3D12_QUERY_HEAP_DESC;
	struct D3D12_RENDER_TARGET_VIEW_DESC;
	struct D3D12_RESOURCE_DESC;
	struct D3D12_SAMPLER_DESC;
	struct D3D12_SHADER_RESOURCE_VIEW_DESC;
	struct D3D12_SUBRESOURCE_TILING;
	struct D3D12_TILE_REGION_SIZE;
	struct D3D12_TILE_SHAPE;
	struct D3D12_TILED_RESOURCE_COORDINATE;
	struct D3D12_UNORDERED_ACCESS_VIEW_DESC;
}

namespace REX::W32
{
	enum D3D12_COMMAND_LIST_TYPE : std::int32_t
	{
		D3D12_COMMAND_LIST_TYPE_DIRECT = 0,
		D3D12_COMMAND_LIST_TYPE_BUNDLE = 1,
		D3D12_COMMAND_LIST_TYPE_COMPUTE = 2,
		D3D12_COMMAND_LIST_TYPE_COPY = 3,
		D3D12_COMMAND_LIST_TYPE_VIDEO_DECODE = 4,
		D3D12_COMMAND_LIST_TYPE_VIDEO_PROCESS = 5,
		D3D12_COMMAND_LIST_TYPE_VIDEO_ENCODE = 6,
		D3D12_COMMAND_LIST_TYPE_NONE = -1
	};

	enum D3D12_COMMAND_QUEUE_FLAGS : std::uint32_t
	{
		D3D12_COMMAND_QUEUE_FLAG_NONE = 0,
		D3D12_COMMAND_QUEUE_FLAG_DISABLE_GPU_TIMEOUT = 0x01
	};

	enum D3D12_CPU_PAGE_PROPERTY : std::int32_t
	{
		D3D12_CPU_PAGE_PROPERTY_UNKNOWN = 0,
		D3D12_CPU_PAGE_PROPERTY_NOT_AVAILABLE = 1,
		D3D12_CPU_PAGE_PROPERTY_WRITE_COMBINE = 2,
		D3D12_CPU_PAGE_PROPERTY_WRITE_BACK = 3
	};

	enum D3D12_DESCRIPTOR_HEAP_TYPE : std::int32_t
	{
		D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV = 0,
		D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER = 1,
		D3D12_DESCRIPTOR_HEAP_TYPE_RTV = 2,
		D3D12_DESCRIPTOR_HEAP_TYPE_DSV = 3,
		D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES = 4
	};

	enum D3D12_FEATURE : std::int32_t
	{
		D3D12_FEATURE_D3D12_OPTIONS = 0,
		D3D12_FEATURE_ARCHITECTURE = 1,
		D3D12_FEATURE_FEATURE_LEVELS = 2,
		D3D12_FEATURE_FORMAT_SUPPORT = 3,
		D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS = 4,
		D3D12_FEATURE_FORMAT_INFO = 5,
		D3D12_FEATURE_GPU_VIRTUAL_ADDRESS_SUPPORT = 6,
		D3D12_FEATURE_SHADER_MODEL = 7,
		D3D12_FEATURE_D3D12_OPTIONS1 = 8,
		D3D12_FEATURE_PROTECTED_RESOURCE_SESSION_SUPPORT = 10,
		D3D12_FEATURE_ROOT_SIGNATURE = 12,
		D3D12_FEATURE_ARCHITECTURE1 = 16,
		D3D12_FEATURE_D3D12_OPTIONS2 = 18,
		D3D12_FEATURE_SHADER_CACHE = 19,
		D3D12_FEATURE_COMMAND_QUEUE_PRIORITY = 20,
		D3D12_FEATURE_D3D12_OPTIONS3 = 21,
		D3D12_FEATURE_EXISTING_HEAPS = 22,
		D3D12_FEATURE_D3D12_OPTIONS4 = 23,
		D3D12_FEATURE_SERIALIZATION = 24,
		D3D12_FEATURE_CROSS_NODE = 25,
		D3D12_FEATURE_D3D12_OPTIONS5 = 27,
		D3D12_FEATURE_DISPLAYABLE = 28,
		D3D12_FEATURE_D3D12_OPTIONS6 = 30,
		D3D12_FEATURE_QUERY_META_COMMAND = 31,
		D3D12_FEATURE_D3D12_OPTIONS7 = 32,
		D3D12_FEATURE_PROTECTED_RESOURCE_SESSION_TYPE_COUNT = 33,
		D3D12_FEATURE_PROTECTED_RESOURCE_SESSION_TYPES = 34,
		D3D12_FEATURE_D3D12_OPTIONS8 = 36,
		D3D12_FEATURE_D3D12_OPTIONS9 = 37,
		D3D12_FEATURE_D3D12_OPTIONS10 = 39,
		D3D12_FEATURE_D3D12_OPTIONS11 = 40,
		D3D12_FEATURE_D3D12_OPTIONS12 = 41,
		D3D12_FEATURE_D3D12_OPTIONS13 = 42,
		D3D12_FEATURE_D3D12_OPTIONS14 = 43,
		D3D12_FEATURE_D3D12_OPTIONS15 = 44,
		D3D12_FEATURE_D3D12_OPTIONS16 = 45,
		D3D12_FEATURE_D3D12_OPTIONS17 = 46,
		D3D12_FEATURE_D3D12_OPTIONS18 = 47,
		D3D12_FEATURE_D3D12_OPTIONS19 = 48,
		D3D12_FEATURE_D3D12_OPTIONS20 = 49,
		D3D12_FEATURE_PREDICATION = 50,
		D3D12_FEATURE_PLACED_RESOURCE_SUPPORT_INFO = 51,
		D3D12_FEATURE_HARDWARE_COPY = 52,
		D3D12_FEATURE_D3D12_OPTIONS21 = 53,
		D3D12_FEATURE_APPLICATION_SPECIFIC_DRIVER_STATE = 56,
		D3D12_FEATURE_BYTECODE_BYPASS_HASH_SUPPORTED = 57,
		D3D12_FEATURE_SHADER_CACHE_ABI_SUPPORT = 61
	};

	enum D3D12_FENCE_FLAGS : std::uint32_t
	{
		D3D12_FENCE_FLAG_NONE = 0,
		D3D12_FENCE_FLAG_SHARED = 0x01,
		D3D12_FENCE_FLAG_SHARED_CROSS_ADAPTER = 0x02,
		D3D12_FENCE_FLAG_NON_MONITORED = 0x04
	};

	enum D3D12_HEAP_FLAGS : std::uint32_t
	{
		D3D12_HEAP_FLAG_NONE = 0,
		D3D12_HEAP_FLAG_SHARED = 0x01,
		D3D12_HEAP_FLAG_DENY_BUFFERS = 0x04,
		D3D12_HEAP_FLAG_ALLOW_DISPLAY = 0x08,
		D3D12_HEAP_FLAG_SHARED_CROSS_ADAPTER = 0x20,
		D3D12_HEAP_FLAG_DENY_RT_DS_TEXTURES = 0x40,
		D3D12_HEAP_FLAG_DENY_NON_RT_DS_TEXTURES = 0x80,
		D3D12_HEAP_FLAG_HARDWARE_PROTECTED = 0x100,
		D3D12_HEAP_FLAG_ALLOW_WRITE_WATCH = 0x200,
		D3D12_HEAP_FLAG_ALLOW_SHADER_ATOMICS = 0x400,
		D3D12_HEAP_FLAG_CREATE_NOT_RESIDENT = 0x800,
		D3D12_HEAP_FLAG_CREATE_NOT_ZEROED = 0x1000,
		D3D12_HEAP_FLAG_TOOLS_USE_MANUAL_WRITE_TRACKING = 0x2000,

		D3D12_HEAP_FLAG_ALLOW_ALL_BUFFERS_AND_TEXTURES = 0,
		D3D12_HEAP_FLAG_ALLOW_ONLY_BUFFERS = D3D12_HEAP_FLAG_DENY_RT_DS_TEXTURES |
			D3D12_HEAP_FLAG_DENY_NON_RT_DS_TEXTURES,
		D3D12_HEAP_FLAG_ALLOW_ONLY_NON_RT_DS_TEXTURES = D3D12_HEAP_FLAG_DENY_BUFFERS |
			D3D12_HEAP_FLAG_DENY_RT_DS_TEXTURES,
		D3D12_HEAP_FLAG_ALLOW_ONLY_RT_DS_TEXTURES = D3D12_HEAP_FLAG_DENY_BUFFERS |
			D3D12_HEAP_FLAG_DENY_NON_RT_DS_TEXTURES
	};

	enum D3D12_HEAP_TYPE : std::int32_t
	{
		D3D12_HEAP_TYPE_DEFAULT = 1,
		D3D12_HEAP_TYPE_UPLOAD = 2,
		D3D12_HEAP_TYPE_READBACK = 3,
		D3D12_HEAP_TYPE_CUSTOM = 4,
		D3D12_HEAP_TYPE_GPU_UPLOAD = 5
	};

	enum D3D12_MEMORY_POOL : std::int32_t
	{
		D3D12_MEMORY_POOL_UNKNOWN = 0,
		D3D12_MEMORY_POOL_L0 = 1,
		D3D12_MEMORY_POOL_L1 = 2
	};

	enum D3D12_RESOURCE_STATES : std::uint32_t
	{
		D3D12_RESOURCE_STATE_COMMON = 0,
		D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER = 0x01,
		D3D12_RESOURCE_STATE_INDEX_BUFFER = 0x02,
		D3D12_RESOURCE_STATE_RENDER_TARGET = 0x04,
		D3D12_RESOURCE_STATE_UNORDERED_ACCESS = 0x08,
		D3D12_RESOURCE_STATE_DEPTH_WRITE = 0x10,
		D3D12_RESOURCE_STATE_DEPTH_READ = 0x20,
		D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE = 0x40,
		D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE = 0x80,
		D3D12_RESOURCE_STATE_STREAM_OUT = 0x100,
		D3D12_RESOURCE_STATE_INDIRECT_ARGUMENT = 0x200,
		D3D12_RESOURCE_STATE_COPY_DEST = 0x400,
		D3D12_RESOURCE_STATE_COPY_SOURCE = 0x800,
		D3D12_RESOURCE_STATE_RESOLVE_DEST = 0x1000,
		D3D12_RESOURCE_STATE_RESOLVE_SOURCE = 0x2000,
		D3D12_RESOURCE_STATE_RAYTRACING_ACCELERATION_STRUCTURE = 0x40'0000,
		D3D12_RESOURCE_STATE_SHADING_RATE_SOURCE = 0x100'0000,
		D3D12_RESOURCE_STATE_PREDICATION = 0x200,
		D3D12_RESOURCE_STATE_VIDEO_DECODE_READ = 0x1'0000,
		D3D12_RESOURCE_STATE_VIDEO_DECODE_WRITE = 0x2'0000,
		D3D12_RESOURCE_STATE_VIDEO_PROCESS_READ = 0x4'0000,
		D3D12_RESOURCE_STATE_VIDEO_PROCESS_WRITE = 0x8'0000,
		D3D12_RESOURCE_STATE_VIDEO_ENCODE_READ = 0x10'0000,
		D3D12_RESOURCE_STATE_VIDEO_ENCODE_WRITE = 0x80'0000,

		D3D12_RESOURCE_STATE_PRESENT = 0,
		D3D12_RESOURCE_STATE_GENERIC_READ = D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER |
			D3D12_RESOURCE_STATE_INDEX_BUFFER |
			D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE |
			D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE |
			D3D12_RESOURCE_STATE_PREDICATION |
			D3D12_RESOURCE_STATE_COPY_SOURCE,
		D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE |
			D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE
	};

	enum D3D12_TILE_MAPPING_FLAGS : std::uint32_t
	{
		D3D12_TILE_MAPPING_FLAG_NONE = 0,
		D3D12_TILE_MAPPING_FLAG_NO_HAZARD = 0x01
	};

	enum D3D12_TILE_RANGE_FLAGS : std::uint32_t
	{
		D3D12_TILE_RANGE_FLAG_NONE = 0,
		D3D12_TILE_RANGE_FLAG_NULL = 0x01,
		D3D12_TILE_RANGE_FLAG_SKIP = 0x02,
		D3D12_TILE_RANGE_FLAG_REUSE_SINGLE_TILE = 0x04
	};
}

namespace REX::W32
{
	struct D3D12_COMMAND_QUEUE_DESC
	{
		D3D12_COMMAND_LIST_TYPE type;
		std::int32_t priority;
		D3D12_COMMAND_QUEUE_FLAGS flags;
		std::uint32_t nodeMask;
	};

	struct D3D12_CPU_DESCRIPTOR_HANDLE
	{
		std::size_t ptr;
	};

	struct D3D12_HEAP_PROPERTIES
	{
		D3D12_HEAP_TYPE type;
		D3D12_CPU_PAGE_PROPERTY cpuPageProperty;
		D3D12_MEMORY_POOL memoryPoolPreference;
		std::uint32_t creationNodeMask;
		std::uint32_t visibleNodeMask;
	};

	struct D3D12_RESOURCE_ALLOCATION_INFO
	{
		std::uint64_t sizeInBytes;
		std::uint64_t alignment;
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

	struct __declspec(novtable, uuid("C4FEC28F-7966-4E95-9F94-F431CB56C3B8")) ID3D12Object : public IUnknown
	{
		virtual auto GetPrivateData(const GUID& a_guid, std::uint32_t* a_dataSize, void* a_data) -> HRESULT = 0;
		virtual auto SetPrivateData(const GUID& a_guid, std::uint32_t a_dataSize, const void* a_data) -> HRESULT = 0;
		virtual auto SetPrivateDataInterface(const GUID& a_guid, const IUnknown* a_data) -> HRESULT = 0;
		virtual auto SetName(const wchar_t* a_name) -> HRESULT = 0;
	};

	struct __declspec(novtable, uuid("905DB94B-A00C-4140-9DF5-2B64CA9EA357")) ID3D12DeviceChild : public ID3D12Object
	{
		virtual auto GetDevice(const GUID& a_guid, void** a_device) -> HRESULT = 0;
	};

	struct __declspec(novtable, uuid("63EE58FB-1268-4835-86DA-F008CE62F0D6")) ID3D12Pageable : public ID3D12DeviceChild
	{
	};

	struct __declspec(novtable, uuid("0EC870A6-5D7E-4C22-8CFC-5BAAE07616ED")) ID3D12CommandQueue : public ID3D12Pageable
	{
		virtual void UpdateTileMappings(
			ID3D12Resource* a_resource,
			std::uint32_t a_numResourceRegions,
			const D3D12_TILED_RESOURCE_COORDINATE* a_resourceRegionStartCoordinates,
			const D3D12_TILE_REGION_SIZE* a_resourceRegionSizes,
			ID3D12Heap* a_heap,
			std::uint32_t a_numRanges,
			const D3D12_TILE_RANGE_FLAGS* a_rangeFlags,
			const std::uint32_t* a_heapRangeStartOffsets,
			const std::uint32_t* a_rangeTileCounts,
			D3D12_TILE_MAPPING_FLAGS a_flags) = 0;
		virtual void CopyTileMappings(
			ID3D12Resource* a_targetResource,
			const D3D12_TILED_RESOURCE_COORDINATE* a_targetRegionStartCoordinate,
			ID3D12Resource* a_sourceResource,
			const D3D12_TILED_RESOURCE_COORDINATE* a_sourceRegionStartCoordinate,
			const D3D12_TILE_REGION_SIZE* a_regionSize,
			D3D12_TILE_MAPPING_FLAGS a_flags) = 0;
		virtual void ExecuteCommandLists(std::uint32_t a_numCommandLists, ID3D12CommandList* const* a_commandLists) = 0;
		virtual void SetMarker(std::uint32_t a_metadata, const void* a_data, std::uint32_t a_size) = 0;
		virtual void BeginEvent(std::uint32_t a_metadata, const void* a_data, std::uint32_t a_size) = 0;
		virtual void EndEvent() = 0;
		virtual auto Signal(ID3D12Fence* a_fence, std::uint64_t a_value) -> HRESULT = 0;
		virtual auto Wait(ID3D12Fence* a_fence, std::uint64_t a_value) -> HRESULT = 0;
		virtual auto GetTimestampFrequency(std::uint64_t* a_frequency) -> HRESULT = 0;
		virtual auto GetClockCalibration(std::uint64_t* a_gpuTimestamp, std::uint64_t* a_cpuTimestamp) -> HRESULT = 0;
		virtual auto GetDesc() -> D3D12_COMMAND_QUEUE_DESC = 0;
	};

	struct __declspec(novtable, uuid("189819F1-1DB6-4B57-BE54-1821339B85F7")) ID3D12Device : public ID3D12Object
	{
		virtual auto GetNodeCount() -> std::uint32_t = 0;
		virtual auto CreateCommandQueue(
			const D3D12_COMMAND_QUEUE_DESC* a_desc,
			const IID& a_riid,
			void** a_commandQueue) -> HRESULT = 0;
		virtual auto CreateCommandAllocator(
			D3D12_COMMAND_LIST_TYPE a_type,
			const IID& a_riid,
			void** a_commandAllocator) -> HRESULT = 0;
		virtual auto CreateGraphicsPipelineState(
			const D3D12_GRAPHICS_PIPELINE_STATE_DESC* a_desc,
			const IID& a_riid,
			void** a_pipelineState) -> HRESULT = 0;
		virtual auto CreateComputePipelineState(
			const D3D12_COMPUTE_PIPELINE_STATE_DESC* a_desc,
			const IID& a_riid,
			void** a_pipelineState) -> HRESULT = 0;
		virtual auto CreateCommandList(
			std::uint32_t a_nodeMask,
			D3D12_COMMAND_LIST_TYPE a_type,
			ID3D12CommandAllocator* a_commandAllocator,
			ID3D12PipelineState* a_initialState,
			const IID& a_riid,
			void** a_commandList) -> HRESULT = 0;
		virtual auto CheckFeatureSupport(
			D3D12_FEATURE a_feature,
			void* a_featureSupportData,
			std::uint32_t a_featureSupportDataSize) -> HRESULT = 0;
		virtual auto CreateDescriptorHeap(
			const D3D12_DESCRIPTOR_HEAP_DESC* a_descriptorHeapDesc,
			const IID& a_riid,
			void** a_heap) -> HRESULT = 0;
		virtual auto GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE a_descriptorHeapType)
			-> std::uint32_t = 0;
		virtual auto CreateRootSignature(
			std::uint32_t a_nodeMask,
			const void* a_blobWithRootSignature,
			std::size_t a_blobLengthInBytes,
			const IID& a_riid,
			void** a_rootSignature) -> HRESULT = 0;
		virtual void CreateConstantBufferView(
			const D3D12_CONSTANT_BUFFER_VIEW_DESC* a_desc,
			D3D12_CPU_DESCRIPTOR_HANDLE a_destDescriptor) = 0;
		virtual void CreateShaderResourceView(
			ID3D12Resource* a_resource,
			const D3D12_SHADER_RESOURCE_VIEW_DESC* a_desc,
			D3D12_CPU_DESCRIPTOR_HANDLE a_destDescriptor) = 0;
		virtual void CreateUnorderedAccessView(
			ID3D12Resource* a_resource,
			ID3D12Resource* a_counterResource,
			const D3D12_UNORDERED_ACCESS_VIEW_DESC* a_desc,
			D3D12_CPU_DESCRIPTOR_HANDLE a_destDescriptor) = 0;
		virtual void CreateRenderTargetView(
			ID3D12Resource* a_resource,
			const D3D12_RENDER_TARGET_VIEW_DESC* a_desc,
			D3D12_CPU_DESCRIPTOR_HANDLE a_destDescriptor) = 0;
		virtual void CreateDepthStencilView(
			ID3D12Resource* a_resource,
			const D3D12_DEPTH_STENCIL_VIEW_DESC* a_desc,
			D3D12_CPU_DESCRIPTOR_HANDLE a_destDescriptor) = 0;
		virtual void CreateSampler(const D3D12_SAMPLER_DESC* a_desc, D3D12_CPU_DESCRIPTOR_HANDLE a_destDescriptor) = 0;
		virtual void CopyDescriptors(
			std::uint32_t a_numDestDescriptorRanges,
			const D3D12_CPU_DESCRIPTOR_HANDLE* a_destDescriptorRangeStarts,
			const std::uint32_t* a_destDescriptorRangeSizes,
			std::uint32_t a_numSrcDescriptorRanges,
			const D3D12_CPU_DESCRIPTOR_HANDLE* a_sourceDescriptorRangeStarts,
			const std::uint32_t* a_sourceDescriptorRangeSizes,
			D3D12_DESCRIPTOR_HEAP_TYPE a_descriptorHeapsType) = 0;
		virtual void CopyDescriptorsSimple(
			std::uint32_t a_numDescriptors,
			D3D12_CPU_DESCRIPTOR_HANDLE a_destDescriptorRangeStart,
			D3D12_CPU_DESCRIPTOR_HANDLE a_sourceDescriptorRangeStart,
			D3D12_DESCRIPTOR_HEAP_TYPE a_descriptorHeapsType) = 0;
		virtual auto GetResourceAllocationInfo(
			std::uint32_t a_visibleMask,
			std::uint32_t a_numResourceDescs,
			const D3D12_RESOURCE_DESC* a_resourceDescs) -> D3D12_RESOURCE_ALLOCATION_INFO = 0;
		virtual auto GetCustomHeapProperties(std::uint32_t a_nodeMask, D3D12_HEAP_TYPE a_heapType)
			-> D3D12_HEAP_PROPERTIES = 0;
		virtual auto CreateCommittedResource(
			const D3D12_HEAP_PROPERTIES* a_heapProperties,
			D3D12_HEAP_FLAGS a_heapFlags,
			const D3D12_RESOURCE_DESC* a_desc,
			D3D12_RESOURCE_STATES a_initialResourceState,
			const D3D12_CLEAR_VALUE* a_optimizedClearValue,
			const IID& a_riidResource,
			void** a_resource) -> HRESULT = 0;
		virtual auto CreateHeap(const D3D12_HEAP_DESC* a_desc, const IID& a_riid, void** a_heap) -> HRESULT = 0;
		virtual auto CreatePlacedResource(
			ID3D12Heap* a_heap,
			std::uint64_t a_heapOffset,
			const D3D12_RESOURCE_DESC* a_desc,
			D3D12_RESOURCE_STATES a_initialState,
			const D3D12_CLEAR_VALUE* a_optimizedClearValue,
			const IID& a_riid,
			void** a_resource) -> HRESULT = 0;
		virtual auto CreateReservedResource(
			const D3D12_RESOURCE_DESC* a_desc,
			D3D12_RESOURCE_STATES a_initialState,
			const D3D12_CLEAR_VALUE* a_optimizedClearValue,
			const IID& a_riid,
			void** a_resource) -> HRESULT = 0;
		virtual auto CreateSharedHandle(
			ID3D12DeviceChild* a_object,
			const SECURITY_ATTRIBUTES* a_attributes,
			std::uint32_t a_access,
			const wchar_t* a_name,
			HANDLE* a_handle) -> HRESULT = 0;
		virtual auto OpenSharedHandle(HANDLE a_ntHandle, const IID& a_riid, void** a_obj) -> HRESULT = 0;
		virtual auto OpenSharedHandleByName(const wchar_t* a_name, std::uint32_t a_access, HANDLE* a_ntHandle)
			-> HRESULT = 0;
		virtual auto MakeResident(std::uint32_t a_numObjects, ID3D12Pageable* const* a_objects) -> HRESULT = 0;
		virtual auto Evict(std::uint32_t a_numObjects, ID3D12Pageable* const* a_objects) -> HRESULT = 0;
		virtual auto CreateFence(
			std::uint64_t a_initialValue,
			D3D12_FENCE_FLAGS a_flags,
			const IID& a_riid,
			void** a_fence) -> HRESULT = 0;
		virtual auto GetDeviceRemovedReason() -> HRESULT = 0;
		virtual void GetCopyableFootprints(
			const D3D12_RESOURCE_DESC* a_resourceDesc,
			std::uint32_t a_firstSubresource,
			std::uint32_t a_numSubresources,
			std::uint64_t a_baseOffset,
			D3D12_PLACED_SUBRESOURCE_FOOTPRINT* a_layouts,
			std::uint32_t* a_numRows,
			std::uint64_t* a_rowSizeInBytes,
			std::uint64_t* a_totalBytes) = 0;
		virtual auto CreateQueryHeap(const D3D12_QUERY_HEAP_DESC* a_desc, const IID& a_riid, void** a_heap)
			-> HRESULT = 0;
		virtual auto SetStablePowerState(BOOL a_enable) -> HRESULT = 0;
		virtual auto CreateCommandSignature(
			const D3D12_COMMAND_SIGNATURE_DESC* a_desc,
			ID3D12RootSignature* a_rootSignature,
			const IID& a_riid,
			void** a_commandSignature) -> HRESULT = 0;
		virtual void GetResourceTiling(
			ID3D12Resource* a_tiledResource,
			std::uint32_t* a_numTilesForEntireResource,
			D3D12_PACKED_MIP_INFO* a_packedMipDesc,
			D3D12_TILE_SHAPE* a_standardTileShapeForNonPackedMips,
			std::uint32_t* a_numSubresourceTilings,
			std::uint32_t a_firstSubresourceTilingToGet,
			D3D12_SUBRESOURCE_TILING* a_subresourceTilingsForNonPackedMips) = 0;
		virtual auto GetAdapterLuid() -> LUID = 0;
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
	inline constexpr auto IID_ID3D12Object =
		IID{0xC4FE'C28F, 0x7966, 0x4E95, {0x9F, 0x94, 0xF4, 0x31, 0xCB, 0x56, 0xC3, 0xB8}};
	inline constexpr auto IID_ID3D12DeviceChild =
		IID{0x905D'B94B, 0xA00C, 0x4140, {0x9D, 0xF5, 0x2B, 0x64, 0xCA, 0x9E, 0xA3, 0x57}};
	inline constexpr auto IID_ID3D12Pageable =
		IID{0x63EE'58FB, 0x1268, 0x4835, {0x86, 0xDA, 0xF0, 0x08, 0xCE, 0x62, 0xF0, 0xD6}};
	inline constexpr auto IID_ID3D12CommandQueue =
		IID{0x0EC8'70A6, 0x5D7E, 0x4C22, {0x8C, 0xFC, 0x5B, 0xAA, 0xE0, 0x76, 0x16, 0xED}};
	inline constexpr auto IID_ID3D12Device =
		IID{0x1898'19F1, 0x1DB6, 0x4B57, {0xBE, 0x54, 0x18, 0x21, 0x33, 0x9B, 0x85, 0xF7}};
}
