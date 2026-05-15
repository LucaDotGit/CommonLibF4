#pragma once

#include "RE/H/hkArray.hpp"
#include "RE/H/hkReferencedObject.hpp"
#include "RE/H/hkStopwatch.hpp"

namespace RE
{
	class hkClass;
	class hkProcessContext;
	class hkSocket;
	class hkStringPtr;
	class hkVisualDebuggerClient;
	class hkVisualDebuggerTrackedObject;
	class hkVtableClassRegistry;

	class __declspec(novtable) hkVisualDebugger
		: public hkReferencedObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::hkVisualDebugger };
		inline static constexpr auto VTABLE{ VTABLE::hkVisualDebugger };

		using TrackCallback = void (*)(void*, const hkClass*, bool, std::uint64_t, void*);

		hkVisualDebugger(const hkArray<hkProcessContext*>& a_contexts, const hkVtableClassRegistry* a_classReg = nullptr);
		~hkVisualDebugger() override; // 00

		// add
		virtual void Step([[maybe_unused]] REX::Float32 a_frameTime); // 04 - { return; }
		virtual void PollForNewClients();							  // 05 - { return; }

		void AddContext(hkProcessContext* a_context);
		void AddDefaultProcess(const char* a_name);
		void Serve(std::uint32_t a_port = 25001);
		void Shutdown();

		// members
		hkSocket* server;									   // 10
		bool suppressPollForNewClients;						   // 18
		hkArray<hkVisualDebuggerClient> clients;			   // 20
		hkArray<hkProcessContext*> contexts;				   // 30
		hkArray<hkVisualDebuggerTrackedObject> trackedObjects; // 40
		hkArray<TrackCallback> trackCallbacks;				   // 50
		hkArray<void*> trackCallbackHandles;				   // 60
		hkVtableClassRegistry* classReg;					   // 70
		hkArray<hkStringPtr> defaultProcesses;				   // 78
		hkArray<hkStringPtr> requiredProcesses;				   // 88
		bool timingFrame;									   // 98
		hkStopwatch frameTimer;								   // A0
		bool overrideFrameTimeIfZero;						   // D0
	};
	static_assert(sizeof(hkVisualDebugger) == 0xD8);
}
