#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/T/TBO_InstanceData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraInstanceData : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraInstanceData;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraInstanceData;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::InstanceData;

		ExtraInstanceData() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraInstanceData() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		TESBoundObject* base{nullptr};			// 0x18
		BSTSmartPointer<TBO_InstanceData> data; // 0x20
	};

	static_assert(sizeof(ExtraInstanceData) == 0x28);
}
