#pragma once

#include "RE/B/BGSDecalNode.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSingleton.hpp"

namespace RE
{
	class BGSDecalEmitter;

	class BGSDecalManager
		: public BSTSingletonSDM<BGSDecalManager> // 00
	{
	public:
		enum class PendingSkinnedDecalState : std::int32_t
		{
			kInitialize = 0,
			kWaitForSkinning = 1,
			kFinalize = 2,
			kAbort = 3
		};

		class PendingSkinnedDecal
		{
		public:
			// members
			NiPointer<BSTempEffect> tempEffect;												 // 00
			NiPointer<BSTriShape> targetGeom;												 // 08
			REX::Enum<BGSDecalManager::PendingSkinnedDecalState, std::int32_t> pendingState; // 10
		};
		static_assert(sizeof(PendingSkinnedDecal) == 0x18);

		[[nodiscard]] static BGSDecalManager* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<BGSDecalManager**>{ ID::BGSDecalManager::Singleton };
			return *SINGLETON;
		}

		// members
		std::uint32_t decalsThisFrame;													   // 0004
		std::uint32_t skinnedDecalsThisFrame;											   // 0008
		std::uint32_t decalCount;														   // 000C
		std::uint32_t skinnedDecalCount;												   // 0010
		alignas(0x80) std::array<std::byte, 0x2180 - 0x80> pendingSkinnedDecalAttachQueue; // 0080 - TODO: BSTCommonStaticMessageQueue<PendingSkinnedDecal, 128>
		BSTArray<BGSDecalEmitter*> decalEmitters;										   // 2180
		BSTArray<NiPointer<BGSDecalNode>> decalNodes;									   // 2198
		std::uint32_t decalNodeARemoveIter;												   // 21B0
		BSTArray<NiPointer<BSTempEffect>> decals;										   // 21B8
		std::uint32_t nextDecalWriteIndex;												   // 21D0
		BSTArray<NiPointer<BSTempEffect>> permanentDecals;								   // 21D8
		std::array<std::uint32_t, 63> dynamicObjects;									   // 21F0
	};
	static_assert(sizeof(BGSDecalManager) == 0x2300);
}
