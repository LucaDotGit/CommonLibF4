#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/N/NiExtraData.hpp"
#include "RE/N/NiExtraDataContainer.hpp"
#include "RE/N/NiObject.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/N/NiTimeController.hpp"

namespace RE
{
	class __declspec(novtable) NiObjectNET
		: public NiObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NiObjectNET };
		inline static constexpr auto VTABLE{ VTABLE::NiObjectNET };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::NiObjectNET };

		enum class CopyType : std::int32_t
		{
			kNone = 0x0,
			kExact = 0x1,
			kUnique = 0x2
		};

		NiObjectNET();

		~NiObjectNET() override; // 00

		[[nodiscard]] NiPointer<NiExtraData> GetExtraData(const BSFixedString& a_key) const noexcept;

		// members
		BSFixedString name;						 // 10
		NiPointer<NiTimeController> controllers; // 18
		NiExtraDataContainer* extra{ nullptr };	 // 20
	};
	static_assert(sizeof(NiObjectNET) == 0x28);
}
