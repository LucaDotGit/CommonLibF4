#pragma once

#include "RE/H/hknpViewerColorScheme.hpp"

namespace RE
{
	class __declspec(novtable) hknpDefaultViewerColorScheme
		: public hknpViewerColorScheme // 00
	{
	public:
		~hknpDefaultViewerColorScheme() override; // 00

		// override (hknpViewerColorScheme)
		std::uint32_t GetBodyColor(const hknpWorld* a_world, hknpBodyId a_bodyId, hknpViewer* a_viewer) override; // 01
		bool IsBodyVisible(const hknpWorld* a_world, hknpBodyId a_bodyId, hknpViewer* a_viewer) override;		  // 02

		// members
		std::uint32_t staticBodyColor{ 0xFF999999 };	// 08
		std::uint32_t dynamicBodyColor{ 0xFFFFB300 };	// 0C
		std::uint32_t keyframedBodyColor{ 0xFF800080 }; // 10
		std::uint32_t triggerColor{ 0x4400FF00 };		// 14
		std::uint32_t dontCollideColor{ 0x66FFFF00 };	// 18
	};
	static_assert(sizeof(hknpDefaultViewerColorScheme) == 0x20);
}
