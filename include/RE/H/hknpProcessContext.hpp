#pragma once

#include "RE/H/hkProcessContext.hpp"
#include "RE/H/hkReferencedObject.hpp"
#include "RE/H/hknpDefaultViewerColorScheme.hpp"

namespace RE
{
	class hknpProcessContextListener;
	class hknpWorld;
	class hkTaskQueue;

	class __declspec(novtable) hknpProcessContext
		: public hkReferencedObject, // 00
		  public hkProcessContext	 // 10
	{
	public:
		~hknpProcessContext() override; // 00

		// members
		hkArray<hknpWorld*> worlds;												  // A0
		hkArray<hknpProcessContextListener*> addListeners;						  // B0
		hknpViewerColorScheme* colorScheme{ std::addressof(defaultColorScheme) }; // C0
		hknpDefaultViewerColorScheme defaultColorScheme;						  // C8
		hkTaskQueue* taskQueue;													  // E8
	};
	static_assert(sizeof(hknpProcessContext) == 0xF0);
}
