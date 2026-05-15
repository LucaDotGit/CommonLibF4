#pragma once

namespace RE
{
	class hknpWorld;
	class hkProcess;

	class __declspec(novtable) hknpProcessContextListener
	{
	public:
		virtual ~hknpProcessContextListener(); // 00

		// add
		virtual void WorldAddedCallback(hknpWorld* a_world) = 0;   // 01
		virtual void WorldRemovedCallback(hknpWorld* a_world) = 0; // 02
		virtual hkProcess* GetProcess();						   // 03 - { return nullptr; }
	};
	static_assert(sizeof(hknpProcessContextListener) == 0x08);
}
