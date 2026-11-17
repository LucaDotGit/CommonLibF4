#pragma once

#include "RE/N/NiPointer.hpp"

namespace RE
{
	class NiAVObject;
	class NiNode;
}

namespace RE::BSAttachTechniques
{
	class __declspec(novtable) AttachTechniqueInput
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSAttachTechniques__AttachTechniqueInput;
		inline static constexpr const auto& VTABLE = VTABLE::BSAttachTechniques__AttachTechniqueInput;

		virtual ~AttachTechniqueInput(); // 0x00

		// add
		virtual void Clear(); // 0x01

		// members
		NiPointer<NiNode> root;			 // 0x08
		NiPointer<NiAVObject> attaching; // 0x10
		std::uint32_t attachPoint;		 // 0x18
	};

	static_assert(sizeof(AttachTechniqueInput) == 0x20);
}
