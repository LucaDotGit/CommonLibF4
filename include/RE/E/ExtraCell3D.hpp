#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/N/NiNode.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class __declspec(novtable) ExtraCell3D
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraCell3D };
		inline static constexpr auto VTABLE{ VTABLE::ExtraCell3D };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kCell3D };

		ExtraCell3D()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraCell3D() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		NiPointer<NiNode> cellNode; // 18
	};
	static_assert(sizeof(ExtraCell3D) == 0x20);
}
