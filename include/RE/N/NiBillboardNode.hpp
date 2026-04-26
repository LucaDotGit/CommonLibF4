#pragma once

#include "RE/N/NiNode.hpp"

namespace RE
{
	class __declspec(novtable) NiBillboardNode
		: public NiNode // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NiBillboardNode };
		inline static constexpr auto VTABLE{ VTABLE::NiBillboardNode };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::NiBillboardNode };

		~NiBillboardNode() override; // 00

		enum class Flags : std::uint32_t; // TODO

		enum class FaceMode : std::int32_t
		{
			kAlwaysFaceCamera = 0x0,
			kRotateAboutUp = 0x1,
			kRigidFaceCamera = 0x3,
			kAlwaysFaceCenter = 0x4,
			kBSRotateAboutUp = 0x5
		};

		// members
		REX::EnumSet<Flags, std::uint32_t> flags; // 140
	};
	static_assert(sizeof(NiBillboardNode) == 0x150);
}
