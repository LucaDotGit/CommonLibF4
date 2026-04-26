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

	class __declspec(novtable) BSCullingProcess
		: public NiCullingProcess // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSCullingProcess };
		inline static constexpr auto VTABLE{ VTABLE::BSCullingProcess };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::BSCullingProcess };

		enum class CullingType : std::int32_t
		{
			kNormal = 0,
			kAllPass = 1,
			kAllFail = 2,
			kIgnoreMultiBounds = 3,
			kForceMultiBoundsNoUpdate = 4
		};

		~BSCullingProcess() override; // 00

		// add
		virtual void AppendNonAccum(NiAVObject*);					// 1C
		virtual void TestBaseVisibility(BSMultiBound* a_bound);		// 1D
		virtual void TestBaseVisibility(BSOcclusionPlane* a_plane); // 1E
		virtual void TestBaseVisibility(const NiBound* a_bound);	// 1F

		// members
		BSTHashMap<NiAVObject*, bool> roomSharedMap; // 120
		BSPortalGraphEntry* portalGraphEntry;		 // 150
		CullingType cullMode;						 // 158
		std::array<CullingType, 10> typeStack;		 // 15C
		std::uint32_t ctStackIndex;					 // 184
		BSCompoundFrustum* compoundFrustum;			 // 188
		NiPointer<NiAccumulator> accumulator;		 // 190
		bool recurseToGeometry;						 // 198
	};
	static_assert(sizeof(BSCullingProcess) == 0x1A0);
}
