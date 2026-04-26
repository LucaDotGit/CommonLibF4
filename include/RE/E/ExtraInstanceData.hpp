#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/T/TBO_InstanceData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraInstanceData
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraInstanceData };
		inline static constexpr auto VTABLE{ VTABLE::ExtraInstanceData };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kInstanceData };

		ExtraInstanceData()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraInstanceData() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		TESBoundObject* base{ nullptr };		// 18
		BSTSmartPointer<TBO_InstanceData> data; // 20
	};
	static_assert(sizeof(ExtraInstanceData) == 0x28);
}
