#pragma once

namespace RE
{
	class hkSocket;
	class hkServerProcessHandler;

	class hkVisualDebuggerClient
	{
	public:
		// members
		hkSocket* socket;						// 00
		hkServerProcessHandler* processHandler; // 08
	};
	static_assert(sizeof(hkVisualDebuggerClient) == 0x10);
}
