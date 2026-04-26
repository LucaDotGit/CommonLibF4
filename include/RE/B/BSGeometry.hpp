#pragma once

#include "RE/B/BSGraphics_VertexDesc.hpp"
#include "RE/N/NiAVObject.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE::BSGraphics
{
	class IndexBuffer;
}

namespace RE::BSSkin
{
	class Instance;
}

namespace RE
{
	class BSCombinedTriShape;
	class BSGeometrySegmentData;
	class BSMergeInstancedTriShape;
	class BSMultiIndexTriShape;
	class NiProperty;

	class __declspec(novtable) BSGeometry
		: public NiAVObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSGeometry };
		inline static constexpr auto VTABLE{ VTABLE::BSGeometry };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::BSGeometry };

		~BSGeometry() override; // 00

		// add
		virtual void UpdatePropertyControllers(NiUpdateData& a_data);	  // 3A
		virtual BSGeometrySegmentData* GetSegmentData();				  // 3B
		virtual void SetSegmentData(BSGeometrySegmentData* a_data);		  // 3C
		virtual BSGraphics::IndexBuffer* GetCustomIndexBuffer();		  // 3D
		virtual BSCombinedTriShape* IsBSCombinedTriShape();				  // 3E
		virtual BSMergeInstancedTriShape* IsBSMergeInstancedTriShape();	  // 3F
		virtual BSMultiIndexTriShape* IsMultiIndexTriShape();			  // 40
		virtual std::uint32_t GetRenderableTris(std::uint32_t a_LODMode); // 40

		// members
		NiBound modelBound;								 // 120
		std::array<NiPointer<NiProperty>, 2> properties; // 130
		NiPointer<BSSkin::Instance> skinInstance;		 // 140
		std::byte* rendererData{ nullptr };				 // 148
		BSGraphics::VertexDesc vertexDesc;				 // 150
		std::uint8_t type{ 0 };							 // 158
		bool registered{ false };						 // 159
	};
	static_assert(sizeof(BSGeometry) == 0x160);
}
