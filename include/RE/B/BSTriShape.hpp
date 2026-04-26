#pragma once

#include "RE/B/BSGeometry.hpp"

namespace RE
{
	class __declspec(novtable) BSTriShape
		: public BSGeometry // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSTriShape };
		inline static constexpr auto VTABLE{ VTABLE::BSTriShape };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::BSTriShape };

		~BSTriShape() override; // 00

		// override (BSGeometry)
		const NiRTTI* GetRTTI() const override;						   // 02 - { return *REL::Relocation<const NiRTTI**>{ BSTriShape::Ni_RTTI };}
		BSTriShape* AsTriShape() override { return this; }			   // 0A
		NiObject* CreateClone(NiCloningProcess& a_cloneData) override; // 1A
		void LoadBinary(NiStream& a_stream) override;				   // 1B
		void LinkObject(NiStream& a_stream) override;				   // 1C - { BSGeometry::LinkObject(a_stream); }
		bool RegisterStreamables(NiStream& a_stream) override;		   // 1D - { return BSGeometry::RegisterStreamables(a_stream); }
		void SaveBinary(NiStream& a_stream) override;				   // 1E
		bool IsEqual(NiObject* a_object) override;					   // 1F - { return false; }

		// members
		std::uint32_t numTriangles{ 0 }; // 160
		std::uint16_t numVertices{ 0 };	 // 164
	};
	static_assert(sizeof(BSTriShape) == 0x170);
}
