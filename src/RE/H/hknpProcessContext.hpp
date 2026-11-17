#pragma once

#include "RE/H/hkProcessContext.hpp"
#include "RE/H/hkReferencedObject.hpp"
#include "RE/H/hknpDefaultViewerColorScheme.hpp"

namespace RE
{
	class hknpProcessContextListener;
	class hknpWorld;
	class hkTaskQueue;

	class __declspec(novtable) hknpProcessContext :
		public hkReferencedObject, // 0x00
		public hkProcessContext	   // 0x10
	{
	public:
		~hknpProcessContext() override; // 0x00

		// members
		hkArray<hknpWorld*> worlds;												// 0xA0
		hkArray<hknpProcessContextListener*> addListeners;						// 0xB0
		hknpViewerColorScheme* colorScheme{std::addressof(defaultColorScheme)}; // 0xC0
		hknpDefaultViewerColorScheme defaultColorScheme;						// 0xC8
		hkTaskQueue* taskQueue;													// 0xE8
	};

	static_assert(sizeof(hknpProcessContext) == 0xF0);
}
