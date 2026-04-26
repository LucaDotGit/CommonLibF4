#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/T/TrespassPackage.hpp"

namespace RE
{
	class __declspec(novtable) ExtraTresPassPackage
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraTresPassPackage };
		inline static constexpr auto VTABLE{ VTABLE::ExtraTresPassPackage };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kTresPassPackage };

		ExtraTresPassPackage()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraTresPassPackage() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		TrespassPackage* package{ nullptr }; // 18
	};
	static_assert(sizeof(ExtraTresPassPackage) == 0x20);
}
