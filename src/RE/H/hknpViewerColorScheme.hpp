#pragma once

#include "RE/H/hknpBodyId.hpp"

namespace RE
{
	class hknpWorld;
	class hknpViewer;

	class __declspec(novtable) hknpViewerColorScheme
	{
	public:
		virtual ~hknpViewerColorScheme(); // 0x00

		// add
		virtual auto GetBodyColor(
			const hknpWorld* a_world,
			hknpBodyId a_bodyId,
			hknpViewer* a_viewer) -> std::uint32_t = 0; // 0x01
		virtual auto IsBodyVisible(const hknpWorld* a_world, hknpBodyId a_bodyId, hknpViewer* a_viewer)
			-> bool = 0; // 0x02
	};

	static_assert(sizeof(hknpViewerColorScheme) == 0x08);
}
