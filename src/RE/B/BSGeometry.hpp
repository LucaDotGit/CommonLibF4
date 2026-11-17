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
	class NiProperty;
}

namespace RE::Impl
{
	template <class T>
	concept NiPropertyConstraint = std::derived_from<T, NiProperty> && !REX::pointer<T> && !REX::reference<T>;
}

namespace RE
{
	class BSCombinedTriShape;
	class BSGeometrySegmentData;
	class BSMergeInstancedTriShape;
	class BSMultiIndexTriShape;

	class __declspec(novtable) BSGeometry : public NiAVObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSGeometry;
		inline static constexpr const auto& VTABLE = VTABLE::BSGeometry;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::BSGeometry;

		~BSGeometry() override; // 0x00

		// add
		virtual void UpdatePropertyControllers(NiUpdateData& a_data);			  // 0x3A
		virtual auto GetSegmentData() -> BSGeometrySegmentData*;				  // 0x3B
		virtual void SetSegmentData(BSGeometrySegmentData* a_data);				  // 0x3C
		virtual auto GetCustomIndexBuffer() -> BSGraphics::IndexBuffer*;		  // 0x3D
		virtual auto IsBSCombinedTriShape() -> BSCombinedTriShape*;				  // 0x3E
		virtual auto IsBSMergeInstancedTriShape() -> BSMergeInstancedTriShape*;	  // 0x3F
		virtual auto IsMultiIndexTriShape() -> BSMultiIndexTriShape*;			  // 0x40
		virtual auto GetRenderableTris(std::uint32_t a_lodMode) -> std::uint32_t; // 0x40

		template <Impl::NiPropertyConstraint T>
		[[nodiscard]]
		auto GetPropertyByType() const noexcept -> NiPointer<T>
			requires(requires { dynamic_ni_pointer_cast<T>(std::declval<NiPointer<NiProperty>>()); })
		{
			for (const auto& property : properties) {
				auto result = dynamic_ni_pointer_cast<T>(property);
				if (result) {
					return result;
				}
			}

			return nullptr;
		}

		// members
		NiBound modelBound;								 // 0x120
		std::array<NiPointer<NiProperty>, 2> properties; // 0x130
		NiPointer<BSSkin::Instance> skinInstance;		 // 0x140
		std::byte* rendererData{nullptr};				 // 0x148
		BSGraphics::VertexDesc vertexDesc;				 // 0x150
		std::uint8_t type{0};							 // 0x158
		bool registered{false};							 // 0x159
	};

	static_assert(sizeof(BSGeometry) == 0x160);
}
