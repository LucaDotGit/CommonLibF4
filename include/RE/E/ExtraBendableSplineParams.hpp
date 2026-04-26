#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/N/NiPoint.hpp"

namespace RE
{
	class __declspec(novtable) ExtraBendableSplineParams
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraBendableSplineParams };
		inline static constexpr auto VTABLE{ VTABLE::ExtraBendableSplineParams };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kBendableSplineParams };

		ExtraBendableSplineParams()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraBendableSplineParams() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		class ParamData_Untilv13
		{
		public:
			// members
			REX::Float32 slack{ 0.0_f32 };	   // 00
			REX::Float32 thickness{ 0.0_f32 }; // 04
			NiPoint3 halfExtents;			   // 08
		};
		static_assert(sizeof(ParamData_Untilv13) == 0x14);

		class ParamData
			: public ParamData_Untilv13 // 00
		{
		public:
			// members
			bool endDetached{ false }; // 14
		};
		static_assert(sizeof(ParamData) == 0x18);

		// members
		ParamData data; // 18
	};
	static_assert(sizeof(ExtraBendableSplineParams) == 0x30);
}
