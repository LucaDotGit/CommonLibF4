#pragma once

#include "RE/B/BGSDecalNode.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSingleton.hpp"

namespace RE
{
	class BGSDecalEmitter;

	class BGSDecalManager : public BSTSingletonSDM<BGSDecalManager> // 0x00
	{
	public:
		enum class PendingSkinnedDecalState : std::int32_t
		{
			Initialize = 0,
			WaitForSkinning = 1,
			Finalize = 2,
			Abort = 3
		};

		class PendingSkinnedDecal
		{
		public:
			// members
			NiPointer<BSTempEffect> tempEffect;												 // 0x00
			NiPointer<BSTriShape> targetGeom;												 // 0x08
			REX::Enum<BGSDecalManager::PendingSkinnedDecalState, std::int32_t> pendingState; // 0x10
		};

		static_assert(sizeof(PendingSkinnedDecal) == 0x18);

		[[nodiscard]]
		static auto GetSingleton() noexcept -> BGSDecalManager*
		{
			static const auto SINGLETON = REL::Relocation<BGSDecalManager**>(ID::BGSDecalManager::Singleton);
			return *SINGLETON;
		}

		// members
		std::uint32_t decalsThisFrame;		  // 0x0004
		std::uint32_t skinnedDecalsThisFrame; // 0x0008
		std::uint32_t decalCount;			  // 0x000C
		std::uint32_t skinnedDecalCount;	  // 0x0010
		alignas(0x80) std::array<
			std::byte,
			0x2180 - 0x80> pendingSkinnedDecalAttachQueue; // 0x0080 - To-Do:
														   // BSTCommonStaticMessageQueue<PendingSkinnedDecal,
														   // 128>
		BSTArray<BGSDecalEmitter*> decalEmitters;		   // 0x2180
		BSTArray<NiPointer<BGSDecalNode>> decalNodes;	   // 0x2198
		std::uint32_t decalNodeARemoveIter;				   // 0x21B0
		BSTArray<NiPointer<BSTempEffect>> decals;		   // 0x21B8
		std::uint32_t nextDecalWriteIndex;				   // 0x21D0
		BSTArray<NiPointer<BSTempEffect>> permanentDecals; // 0x21D8
		std::array<std::uint32_t, 63> dynamicObjects;	   // 0x21F0
	};

	static_assert(sizeof(BGSDecalManager) == 0x2300);
}
