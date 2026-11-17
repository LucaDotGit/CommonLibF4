#pragma once

#include "RE/B/BSBatchRenderer.hpp"
#include "RE/B/BSEventFlag.hpp"
#include "RE/B/BSTArray.hpp"

namespace RE
{
	class BSGeometry;
	class BSRenderPass;
}

namespace RE::BSMTAManager
{
	enum class MODE : std::int32_t
	{
		Idle = 0,
		Collecting = 1,
		Executing = 2
	};

	class CalculateBoneMatricesTask
	{
	public:
		// members
		BSGeometry* geometry; // 0x00
	};

	static_assert(sizeof(CalculateBoneMatricesTask) == 0x08);

	class RegisterBatchRendererPassTask
	{
	public:
		// members
		BSBatchRenderer* batchRenderer; // 0x00
		BSRenderPass* renderPass;		// 0x08
	};

	static_assert(sizeof(RegisterBatchRendererPassTask) == 0x10);

	class RegisterGeometryGroupPassTask
	{
	public:
		// members
		BSBatchRenderer* batchRenderer;										 // 0x00
		BSRenderPass* renderPass;											 // 0x08
		BSBatchRenderer::GeometryGroup* geometryGroup;						 // 0x10
		REX::Enum<BSBatchRenderer::GEOMETRY_GROUP_ENUM, std::int32_t> group; // 0x18
		bool addToFront;													 // 0x1C
	};

	static_assert(sizeof(RegisterGeometryGroupPassTask) == 0x20);

	class JobData
	{
	public:
		// members
		BSTArray<RegisterBatchRendererPassTask> registerBatchRendererPasses; // 0x00
		BSTArray<RegisterGeometryGroupPassTask> registerGeometryGroupPasses; // 0x18
		BSEventFlag finishedEvent;											 // 0x30
	};

	static_assert(sizeof(JobData) == 0x38);

	class RegisterObjectTask
	{
	public:
		// members
		BSGeometry* geometry;							   // 0x00
		std::int32_t groupingAlphas;					   // 0x08
		BSBatchRenderer::GeometryGroup* currentAlphaGroup; // 0x10
		bool alphaGroupZPrePass;						   // 0x18
		JobData* owner;									   // 0x20
		std::uint32_t registerBatchRendererPassIndex;	   // 0x28
		std::uint32_t registerBatchRendererPassCount;	   // 0x2C
		std::uint32_t registerGeometryGroupPassIndex;	   // 0x30
		std::uint32_t registerGeometryGroupPassCount;	   // 0x34
	};

	static_assert(sizeof(RegisterObjectTask) == 0x38);
}
