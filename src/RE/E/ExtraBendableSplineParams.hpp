#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class __declspec(novtable) ExtraBendableSplineParams : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraBendableSplineParams;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraBendableSplineParams;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::BendableSplineParams;

		ExtraBendableSplineParams() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraBendableSplineParams() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		class ParamData_Untilv13
		{
		public:
			// members
			REX::Float32 slack{static_cast<REX::Float32>(0.0)};		// 0x00
			REX::Float32 thickness{static_cast<REX::Float32>(0.0)}; // 0x04
			NiPoint3 halfExtents;									// 0x08
		};

		static_assert(sizeof(ParamData_Untilv13) == 0x14);

		class ParamData : public ParamData_Untilv13 // 0x00
		{
		public:
			// members
			bool endDetached{false}; // 0x14
		};

		static_assert(sizeof(ParamData) == 0x18);

		// members
		ParamData data; // 0x18
	};

	static_assert(sizeof(ExtraBendableSplineParams) == 0x30);
}
