#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSmallIndexScatterTable.hpp"
#include "RE/P/PersistentPassList.hpp"

namespace RE
{
	class BSRenderPass;

	class __declspec(novtable) BSBatchRenderer
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSBatchRenderer;
		inline static constexpr const auto& VTABLE = VTABLE::BSBatchRenderer;

		enum class GEOMETRY_GROUP_ENUM : std::int32_t
		{
			None = -1,

			LODLand = 0,
			LODObjects = 1,
			MultiIndexDecal = 2,
			OpaqueDecal = 3,
			BlendedDecal = 4,
			RefrActive = 5,
			k1stPersonNonRefractive = 6,
			Fading = 7,
			NoShadow = 8,
			LowAniso = 9,
			UnderwaterFog = 10,
			SSLR = 11,
			ZOnly = 12,
			PostZOnly = 13,
			SkyClouds = 14,
			SmoothAlphaTest = 15,
			VATSMaskDepthOnly = 16,
			VATSMask = 17,
			SunGlare = 18,
			BloodSpatter = 19,
			ZPrepass = 20,
			WaterStencil = 21,
			WaterDepth = 22,

			_Count = 23
		};

		class CommandBufferPassesMapAccess;
		class RenderPassMapAccess;

		class CommandBufferPassesData
		{
		public:
			// members
			std::array<std::byte*, 0x2000> buffer; // 0x00000
			std::byte** currentBuffer;			   // 0x10000
			CommandBufferPassesData* next;		   // 0x10008
			std::uint32_t frame;				   // 0x10010
			std::uint32_t ownerIndex;			   // 0x10014
		};

		static_assert(sizeof(CommandBufferPassesData) == 0x1'0018);

		class CommandBufferPassesDataEntry
		{
		public:
			// members
			CommandBufferPassesData* data; // 0x00
			std::uint64_t groupAndPass;	   // 0x08
		};

		static_assert(sizeof(CommandBufferPassesDataEntry) == 0x10);

		class GeometryGroup
		{
		public:
			// members
			BSBatchRenderer* batchRenderer; // 0x00
			PersistentPassList passList;	// 0x08
			REX::Float32 depth;				// 0x18
			std::uint32_t count;			// 0x1C
			std::uint8_t flags;				// 0x20
			std::int8_t group;				// 0x21
		};

		static_assert(sizeof(GeometryGroup) == 0x28);

		class PassGroup
		{
		public:
			// members
			BSRenderPass* passHead;			   // 0x00
			std::uint32_t passEnum;			   // 0x08
			std::uint16_t nextPassGroup;	   // 0x0C
			std::uint16_t commandBufferPasses; // 0x0E
		};

		static_assert(sizeof(PassGroup) == 0x10);

		virtual ~BSBatchRenderer(); // 0x00

		std::array<BSTArray<PassGroup>, 13> renderPasses;												   // 0x008
		std::array<BSTSmallIndexScatterTable<BSTArray<PassGroup>, RenderPassMapAccess>, 13> renderPassMap; // 0x140
		std::array<std::array<std::uint32_t, 13>, 2> activePassIndexLists;								   // 0x2E0
		std::uint32_t currentFirstPass;																	   // 0x348
		std::uint32_t currentLastPass;																	   // 0x34C
		bool autoClearPasses;																			   // 0x350
		std::array<GeometryGroup*, std::to_underlying(GEOMETRY_GROUP_ENUM::_Count)> geometryGroups;		   // 0x358
		GeometryGroup* alphaGroup;																		   // 0x410
		std::uint32_t groupingAlphasGroupCount;															   // 0x418
		GeometryGroup* groupingAlphasGroup;																   // 0x420
		BSTArray<CommandBufferPassesDataEntry> commandBufferPasses;										   // 0x428
		BSTSmallIndexScatterTable<BSTArray<CommandBufferPassesDataEntry>, CommandBufferPassesMapAccess>
			commandBufferPassMap;					// 0x440
		CommandBufferPassesData* bufferPassesCurr;	// 0x460
		CommandBufferPassesData* bufferPassesHead;	// 0x468
		CommandBufferPassesData** bufferPassesTail; // 0x470
		std::uint32_t bufferPassesCurrAllocFrame;	// 0x478
	};

	static_assert(sizeof(BSBatchRenderer) == 0x480);
}
