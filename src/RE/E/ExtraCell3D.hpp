#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/N/NiNode.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class __declspec(novtable) ExtraCell3D : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraCell3D;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraCell3D;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::Cell3D;

		ExtraCell3D() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraCell3D() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		NiPointer<NiNode> cellNode; // 0x18
	};

	static_assert(sizeof(ExtraCell3D) == 0x20);
}
