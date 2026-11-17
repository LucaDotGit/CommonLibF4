#pragma once

namespace RE
{
	class hknpWorld;
	class hkProcess;

	class __declspec(novtable) hknpProcessContextListener
	{
	public:
		virtual ~hknpProcessContextListener(); // 0x00

		// add
		virtual void WorldAddedCallback(hknpWorld* a_world) = 0;   // 0x01
		virtual void WorldRemovedCallback(hknpWorld* a_world) = 0; // 0x02
		virtual auto GetProcess() -> hkProcess*;				   // 0x03 - { return nullptr; }
	};

	static_assert(sizeof(hknpProcessContextListener) == 0x08);
}
