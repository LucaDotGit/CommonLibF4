#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/N/NiNode.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/N/NiTransform.hpp"

namespace RE
{
	class __declspec(novtable) BSFlattenedBoneTree : public NiNode // 0x000
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSFlattenedBoneTree;
		inline static constexpr const auto& VTABLE = VTABLE::BSFlattenedBoneTree;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::BSFlattenedBoneTree;

		class FlattenedBone
		{
		public:
			// members
			NiTransform local;		  // 0x00
			NiTransform world;		  // 0x40
			std::int16_t parent;	  // 0x80
			std::int16_t child;		  // 0x82
			std::uint16_t childCount; // 0x84
			std::int16_t sibling;	  // 0x86
			NiPointer<NiNode> node;	  // 0x88
			BSFixedString name;		  // 0x90
			bool deferredAttach;	  // 0x98
		};

		static_assert(sizeof(FlattenedBone) == 0xA0);

		BSFlattenedBoneTree() :
			NiNode(0)
		{
			REL::EmplaceVtable(this);
		}

		explicit BSFlattenedBoneTree(std::uint32_t a_numChildren) :
			NiNode(a_numChildren)
		{
			REL::EmplaceVtable(this);
		}

		~BSFlattenedBoneTree() override; // 0x00

		GAME_HEAP_REDEFINE_ALIGNED_NEW(BSFlattenedBoneTree);

		// members
		std::int32_t boneCount{0};						 // 0x140
		std::int32_t boneCountExpanded{0};				 // 0x144
		FlattenedBone* bone{nullptr};					 // 0x148
		BSTHashMap<BSFixedString, std::int32_t> boneMap; // 0x150
	};

#if (COMMONLIB_RUNTIME_VR == 0)
	static_assert(sizeof(BSFlattenedBoneTree) == 0x180);
#else
	static_assert(sizeof(BSFlattenedBoneTree) == 0x160);
#endif
}
