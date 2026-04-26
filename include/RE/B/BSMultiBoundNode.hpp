#pragma once

#include "RE/B/BSCullingProcess.hpp"
#include "RE/B/BSMultiBoundShape.hpp"
#include "RE/B/BSNiNode.hpp"
#include "RE/N/NiBound.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BSMultiBound;
	class BSMultiBoundRoom;

	class __declspec(novtable) BSMultiBoundNode
		: public BSNiNode // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSMultiBoundNode };
		inline static constexpr auto VTABLE{ VTABLE::BSMultiBoundNode };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::BSMultiBoundNode };

		~BSMultiBoundNode() override; // 00

		// add
		virtual BSMultiBoundRoom* GetMultiBoundRoom();												  // 43
		virtual bool QPointWithin(const NiPoint3* a_point);											  // 44
		virtual BSMultiBoundShape::BSMBIntersectResult CheckBound(const BSMultiBound* a_targetbound); // 45
		virtual BSMultiBoundShape::BSMBIntersectResult CheckBound(const NiBound* a_targetbound);	  // 46

		// members
		NiPointer<BSMultiBound> multiBound;									// 140
		REX::Enum<BSCullingProcess::CullingType, std::int32_t> cullingMode; // 148
		REX::Float32 lastAccumTime;											// 14C
	};
	static_assert(sizeof(BSMultiBoundNode) == 0x150);
}
