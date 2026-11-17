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

	class __declspec(novtable) hkVisualDebugger : public hkReferencedObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::hkVisualDebugger;
		inline static constexpr const auto& VTABLE = VTABLE::hkVisualDebugger;

		using TrackCallback = void (*)(void*, const hkClass*, bool, std::uint64_t, void*);

		hkVisualDebugger(
			const hkArray<hkProcessContext*>& a_contexts,
			const hkVtableClassRegistry* a_classReg = nullptr);
		~hkVisualDebugger() override; // 0x00

		// add
		virtual void Step([[maybe_unused]] REX::Float32 a_frameTime); // 0x04 - { return; }
		virtual void PollForNewClients();							  // 0x05 - { return; }

		void AddContext(hkProcessContext* a_context);
		void AddDefaultProcess(const char* a_name);
		void Serve(std::uint32_t a_port = 25'001);
		void Shutdown();

		// members
		hkSocket* server;									   // 0x10
		bool suppressPollForNewClients;						   // 0x18
		hkArray<hkVisualDebuggerClient> clients;			   // 0x20
		hkArray<hkProcessContext*> contexts;				   // 0x30
		hkArray<hkVisualDebuggerTrackedObject> trackedObjects; // 0x40
		hkArray<TrackCallback> trackCallbacks;				   // 0x50
		hkArray<void*> trackCallbackHandles;				   // 0x60
		hkVtableClassRegistry* classReg;					   // 0x70
		hkArray<hkStringPtr> defaultProcesses;				   // 0x78
		hkArray<hkStringPtr> requiredProcesses;				   // 0x88
		bool timingFrame;									   // 0x98
		hkStopwatch frameTimer;								   // 0xA0
		bool overrideFrameTimeIfZero;						   // 0xD0
	};

	static_assert(sizeof(hkVisualDebugger) == 0xD8);
}
