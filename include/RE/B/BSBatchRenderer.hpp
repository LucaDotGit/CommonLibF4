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
		inline static constexpr auto RTTI{ RTTI::BSBatchRenderer };
		inline static constexpr auto VTABLE{ VTABLE::BSBatchRenderer };

		enum class GEOMETRY_GROUP_ENUM : std::int32_t
		{
			kNone = -1,

			kLODLand = 0,
			kLODObjects = 1,
			kMultiIndexDecal = 2,
			kOpaqueDecal = 3,
			kBlendedDecal = 4,
			kRefrActive = 5,
			k1stPersonNonRefractive = 6,
			kFading = 7,
			kNoShadow = 8,
			kLowAniso = 9,
			kUnderwaterFog = 10,
			kSSLR = 11,
			kZOnly = 12,
			kPostZOnly = 13,
			kSkyClouds = 14,
			kSmoothAlphaTest = 15,
			kVATSMaskDepthOnly = 16,
			kVATSMask = 17,
			kSunGlare = 18,
			kBloodSpatter = 19,
			kZPrepass = 20,
			kWaterStencil = 21,
			kWaterDepth = 22,

			kTotal = 23
		};

		class CommandBufferPassesMapAccess;
		class RenderPassMapAccess;

		class CommandBufferPassesData
		{
		public:
			// members
			std::array<std::byte*, 0x2000> buffer; // 00000
			std::byte** currentBuffer;			   // 10000
			CommandBufferPassesData* next;		   // 10008
			std::uint32_t frame;				   // 10010
			std::uint32_t ownerIndex;			   // 10014
		};
		static_assert(sizeof(CommandBufferPassesData) == 0x10018);

		class CommandBufferPassesDataEntry
		{
		public:
			// members
			CommandBufferPassesData* data; // 00
			std::uint64_t groupAndPass;	   // 08
		};
		static_assert(sizeof(CommandBufferPassesDataEntry) == 0x10);

		class GeometryGroup
		{
		public:
			// members
			BSBatchRenderer* batchRenderer; // 00
			PersistentPassList passList;	// 08
			REX::Float32 depth;				// 18
			std::uint32_t count;			// 1C
			std::uint8_t flags;				// 20
			std::int8_t group;				// 21
		};
		static_assert(sizeof(GeometryGroup) == 0x28);

		class PassGroup
		{
		public:
			// members
			BSRenderPass* passHead;			   // 00
			std::uint32_t passEnum;			   // 08
			std::uint16_t nextPassGroup;	   // 0C
			std::uint16_t commandBufferPasses; // 0E
		};
		static_assert(sizeof(PassGroup) == 0x10);

		virtual ~BSBatchRenderer(); // 00

		std::array<BSTArray<PassGroup>, 13> renderPasses;																	  // 008
		std::array<BSTSmallIndexScatterTable<BSTArray<PassGroup>, RenderPassMapAccess>, 13> renderPassMap;					  // 140
		std::array<std::array<std::uint32_t, 13>, 2> activePassIndexLists;													  // 2E0
		std::uint32_t currentFirstPass;																						  // 348
		std::uint32_t currentLastPass;																						  // 34C
		bool autoClearPasses;																								  // 350
		std::array<GeometryGroup*, std::to_underlying(GEOMETRY_GROUP_ENUM::kTotal)> geometryGroups;							  // 358
		GeometryGroup* alphaGroup;																							  // 410
		std::uint32_t groupingAlphasGroupCount;																				  // 418
		GeometryGroup* groupingAlphasGroup;																					  // 420
		BSTArray<CommandBufferPassesDataEntry> commandBufferPasses;															  // 428
		BSTSmallIndexScatterTable<BSTArray<CommandBufferPassesDataEntry>, CommandBufferPassesMapAccess> commandBufferPassMap; // 440
		CommandBufferPassesData* bufferPassesCurr;																			  // 460
		CommandBufferPassesData* bufferPassesHead;																			  // 468
		CommandBufferPassesData** bufferPassesTail;																			  // 470
		std::uint32_t bufferPassesCurrAllocFrame;																			  // 478
	};
	static_assert(sizeof(BSBatchRenderer) == 0x480);
}
