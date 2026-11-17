#pragma once

#include "RE/B/BSGeometry.hpp"

namespace RE
{
	class __declspec(novtable) BSTriShape : public BSGeometry // 0x000
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSTriShape;
		inline static constexpr const auto& VTABLE = VTABLE::BSTriShape;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::BSTriShape;

		~BSTriShape() override; // 0x00

		// override (BSGeometry)
		auto GetRTTI() const
			-> const NiRTTI* override; // 0x02 - { return *REL::Relocation<const NiRTTI**>{ BSTriShape::Ni_RTTI };}

		auto IsTriShape() -> BSTriShape* override // 0x0A
		{
			return this;
		}

		auto CreateClone(NiCloningProcess& a_cloneData) -> NiObject* override; // 0x1A
		void LoadBinary(NiStream& a_stream) override;						   // 0x1B
		void LinkObject(NiStream& a_stream) override; // 0x1C - { BSGeometry::LinkObject(a_stream); }
		auto RegisterStreamables(NiStream& a_stream)
			-> bool override;						  // 0x1D - { return BSGeometry::RegisterStreamables(a_stream); }
		void SaveBinary(NiStream& a_stream) override; // 0x1E
		auto IsEqual(NiObject* a_object) -> bool override; // 0x1F - { return false; }

		// members
		std::uint32_t numTriangles{0}; // 0x160
		std::uint16_t numVertices{0};  // 0x164
	};

	static_assert(sizeof(BSTriShape) == 0x170);
}
