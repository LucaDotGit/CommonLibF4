#pragma once

namespace RE
{
	class hkSocket;
	class hkServerProcessHandler;

	class hkVisualDebuggerClient
	{
	public:
		// members
		hkSocket* socket;						// 0x00
		hkServerProcessHandler* processHandler; // 0x08
	};

	static_assert(sizeof(hkVisualDebuggerClient) == 0x10);
}
