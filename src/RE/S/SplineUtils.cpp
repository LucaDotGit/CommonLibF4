#include "RE/S/SplineUtils.hpp"

namespace RE::SplineUtils
{
	void DisconnectSpline(TESObjectREFR& a_spline)
	{
		using FuncType = decltype(&SplineUtils::DisconnectSpline);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::SplineUtils::DisconnectSpline };
		FUNC(a_spline);
	}

	void ConnectSpline(TESObjectREFR* akEndpoint1, int32_t linkType1, TESObjectREFR* akEndpoint2, int32_t linkType2, TESObjectREFR* akWireRef)
	{
		using FuncType = decltype(&SplineUtils::ConnectSpline);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::SplineUtils::ConnectSpline };
		FUNC(akEndpoint1, linkType1, akEndpoint2, linkType2, akWireRef);
	}
}
