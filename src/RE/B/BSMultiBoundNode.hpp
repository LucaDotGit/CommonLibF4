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

	class __declspec(novtable) BSMultiBoundNode : public BSNiNode // 0x000
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSMultiBoundNode;
		inline static constexpr const auto& VTABLE = VTABLE::BSMultiBoundNode;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::BSMultiBoundNode;

		~BSMultiBoundNode() override; // 0x00

		// add
		virtual auto GetMultiBoundRoom() -> BSMultiBoundRoom*;												  // 0x43
		virtual auto QPointWithin(const NiPoint3* a_point) -> bool;											  // 0x44
		virtual auto CheckBound(const BSMultiBound* a_targetbound) -> BSMultiBoundShape::BSMBIntersectResult; // 0x45
		virtual auto CheckBound(const NiBound* a_targetbound) -> BSMultiBoundShape::BSMBIntersectResult;	  // 0x46

		// members
		NiPointer<BSMultiBound> multiBound;									// 0x140
		REX::Enum<BSCullingProcess::CullingType, std::int32_t> cullingMode; // 0x148
		REX::Float32 lastAccumTime;											// 0x14C
	};

#if (COMMONLIB_RUNTIME_VR == 0)
	static_assert(sizeof(BSMultiBoundNode) == 0x150);
#else
	static_assert(sizeof(BSMultiBoundNode) == 0x130);
#endif
}
