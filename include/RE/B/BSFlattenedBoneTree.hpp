#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/N/NiNode.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/N/NiTransform.hpp"

namespace RE
{
	class __declspec(novtable) BSFlattenedBoneTree
		: public NiNode // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSFlattenedBoneTree };
		inline static constexpr auto VTABLE{ VTABLE::BSFlattenedBoneTree };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::BSFlattenedBoneTree };

		class FlattenedBone
		{
		public:
			// members
			NiTransform local;		  // 00
			NiTransform world;		  // 40
			std::int16_t parent;	  // 80
			std::int16_t child;		  // 82
			std::uint16_t childCount; // 84
			std::int16_t sibling;	  // 86
			NiPointer<NiNode> node;	  // 88
			BSFixedString name;		  // 90
			bool deferredAttach;	  // 98
		};
		static_assert(sizeof(FlattenedBone) == 0xA0);

		BSFlattenedBoneTree()
			: NiNode(0)
		{
			REL::EmplaceVtable(this);
		}

		explicit BSFlattenedBoneTree(std::uint32_t a_numChildren)
			: NiNode(a_numChildren)
		{
			REL::EmplaceVtable(this);
		}

		~BSFlattenedBoneTree() override; // 00

		GAME_HEAP_REDEFINE_ALIGNED_NEW(BSFlattenedBoneTree);

		// members
		std::int32_t boneCount{ 0 };					 // 140
		std::int32_t boneCountExpanded{ 0 };			 // 144
		FlattenedBone* bone{ nullptr };					 // 148
		BSTHashMap<BSFixedString, std::int32_t> boneMap; // 150
	};
	static_assert(sizeof(BSFlattenedBoneTree) == 0x180);
}
