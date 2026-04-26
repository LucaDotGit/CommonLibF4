#pragma once

namespace RE::SplineUtils
{
	void DisconnectSpline(TESObjectREFR& a_spline);
	void ConnectSpline(TESObjectREFR* akEndpoint1, int32_t linkType1, TESObjectREFR* akEndpoint2, int32_t linkType2, TESObjectREFR* akWireRef);
}
