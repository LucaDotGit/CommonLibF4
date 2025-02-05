#pragma once

#include "RE/Bethesda/BSFixedString.hpp"
#include "RE/Bethesda/BSLock.hpp"
#include "RE/Bethesda/BSTArray.hpp"
#include "RE/NetImmerse/NiExtraData.hpp"
#include "RE/NetImmerse/NiObject.hpp"
#include "RE/NetImmerse/NiSmartPointer.hpp"

namespace RE
{
	class NiExtraDataContainer
		: public BSTArray<NiExtraData*>
	{
	public:
		BSAutoLock<BSSpinLock, BSAutoLockDefaultPolicy> lock;
	};
	class NiTimeController;

	class __declspec(novtable) NiObjectNET
		: public NiObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NiObjectNET };
		inline static constexpr auto VTABLE{ VTABLE::NiObjectNET };
		inline static constexpr auto Ni_RTTI{ Ni_RTTI::NiObjectNET };

		NiObjectNET();
		virtual ~NiObjectNET(); // NOLINT(modernize-use-override) 00

		F4_HEAP_REDEFINE_NEW(NiObjectNET);

		[[nodiscard]] std::string_view GetName() const { return name; }

		[[nodiscard]] NiExtraData* GetExtraData(BSFixedString a_key) const noexcept;

		// members
		BSFixedString name{ "" };				 // 10
		NiPointer<NiTimeController> controllers; // 18
		NiExtraDataContainer* extra{ nullptr };	 // 20
	};
	static_assert(sizeof(NiObjectNET) == 0x28);
}
