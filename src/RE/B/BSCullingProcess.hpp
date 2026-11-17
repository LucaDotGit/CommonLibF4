#pragma once

#include "RE/B/BSTHashMap.hpp"
#include "RE/N/NiCullingProcess.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BSCompoundFrustum;
	class BSMultiBound;
	class BSOcclusionPlane;
	class BSPortalGraphEntry;
	class NiAccumulator;
	class NiAVObject;
	class NiBound;

	class __declspec(novtable) BSCullingProcess : public NiCullingProcess // 0x000
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSCullingProcess;
		inline static constexpr const auto& VTABLE = VTABLE::BSCullingProcess;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::BSCullingProcess;

		enum class CullingType : std::int32_t
		{
			Normal = 0,
			AllPass = 1,
			AllFail = 2,
			IgnoreMultiBounds = 3,
			ForceMultiBoundsNoUpdate = 4
		};

		~BSCullingProcess() override; // 0x00

		// add
		virtual void AppendNonAccum(NiAVObject*);					// 0x1C
		virtual void TestBaseVisibility(BSMultiBound* a_bound);		// 0x1D
		virtual void TestBaseVisibility(BSOcclusionPlane* a_plane); // 0x1E
		virtual void TestBaseVisibility(const NiBound* a_bound);	// 0x1F

		// members
		BSTHashMap<NiAVObject*, bool> roomSharedMap; // 0x120
		BSPortalGraphEntry* portalGraphEntry;		 // 0x150
		CullingType cullMode;						 // 0x158
		std::array<CullingType, 10> typeStack;		 // 0x15C
		std::uint32_t ctStackIndex;					 // 0x184
		BSCompoundFrustum* compoundFrustum;			 // 0x188
		NiPointer<NiAccumulator> accumulator;		 // 0x190
		bool recurseToGeometry;						 // 0x198
	};

	static_assert(sizeof(BSCullingProcess) == 0x1A0);
}
