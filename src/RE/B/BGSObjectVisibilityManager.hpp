#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BSTTuple.hpp"
#include "RE/C/CombatMathUtilities_Box.hpp"
#include "RE/N/NiPoint3.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSObjectVisibilityManager : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSObjectVisibilityManager;
		inline static constexpr const auto& VTABLE = VTABLE::BGSObjectVisibilityManager;
		inline static constexpr auto FORM_TYPE = FormType::ObjectVisibilityManager;

		class ObjectVisibilityData
		{
		public:
			// members
			NiPoint3 minPoint; // 0x00
			NiPoint3 maxPoint; // 0x0C
		};

		static_assert(sizeof(ObjectVisibilityData) == 0x18);

		// members
		BSTHashMap<TESFormID, ObjectVisibilityData> objectVisiblityMap;										 // 0x20
		BSTHashMap<ObjectRefHandle, BSTPair<CombatMathUtilities::Box, REX::Float32>> referenceVisibilityMap; // 0x50
	};

	static_assert(sizeof(BGSObjectVisibilityManager) == 0x80);
}
