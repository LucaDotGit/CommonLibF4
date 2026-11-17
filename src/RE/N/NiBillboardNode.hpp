#pragma once

#include "RE/N/NiNode.hpp"

namespace RE
{
	class __declspec(novtable) NiBillboardNode : public NiNode // 0x000
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NiBillboardNode;
		inline static constexpr const auto& VTABLE = VTABLE::NiBillboardNode;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::NiBillboardNode;

		~NiBillboardNode() override; // 0x00

		enum class BillboardFlags : std::uint32_t; // To-Do

		enum class FaceMode : std::int32_t
		{
			AlwaysFaceCamera = 0,
			RotateAboutUp = 1,
			RigidFaceCamera = 3,
			AlwaysFaceCenter = 4,
			BSRotateAboutUp = 5
		};

		// members
		REX::EnumSet<BillboardFlags, std::uint32_t> billboardFlags; // 0x140
	};

#if (COMMONLIB_RUNTIME_VR == 0)
	static_assert(sizeof(NiBillboardNode) == 0x150);
#else
	static_assert(sizeof(NiBillboardNode) == 0x130);
#endif
}
