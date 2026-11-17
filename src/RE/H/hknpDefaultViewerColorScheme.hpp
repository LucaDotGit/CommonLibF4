#pragma once

#include "RE/H/hknpViewerColorScheme.hpp"

namespace RE
{
	class __declspec(novtable) hknpDefaultViewerColorScheme : public hknpViewerColorScheme // 0x00
	{
	public:
		~hknpDefaultViewerColorScheme() override; // 0x00

		// override (hknpViewerColorScheme)
		auto GetBodyColor(const hknpWorld* a_world, hknpBodyId a_bodyId, hknpViewer* a_viewer)
			-> std::uint32_t override; // 0x01
		auto IsBodyVisible(const hknpWorld* a_world, hknpBodyId a_bodyId, hknpViewer* a_viewer)
			-> bool override; // 0x02

		// members
		std::uint32_t staticBodyColor{0xFF99'9999};	   // 0x08
		std::uint32_t dynamicBodyColor{0xFFFF'B300};   // 0x0C
		std::uint32_t keyframedBodyColor{0xFF80'0080}; // 0x10
		std::uint32_t triggerColor{0x4400'FF00};	   // 0x14
		std::uint32_t dontCollideColor{0x66FF'FF00};   // 0x18
	};

	static_assert(sizeof(hknpDefaultViewerColorScheme) == 0x20);
}
