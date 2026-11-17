#pragma once

#include "RE/H/hkProcess.hpp"
#include "RE/H/hkReferencedObject.hpp"
#include "RE/H/hknpBodyId.hpp"
#include "RE/H/hknpProcessContextListener.hpp"

namespace RE
{
	class hknpProcessContext;
	class hknpWorld;

	class __declspec(novtable) hknpViewer :
		public hkReferencedObject,		  // 0x00
		public hkProcess,				  // 0x10
		public hknpProcessContextListener // 0x40
	{
	public:
		~hknpViewer() override; // 0x00

		// add
		virtual void OnSetViewerSpecificBody(); // 0x04

		// members
		hknpProcessContext* context;		  // 0x48
		hknpBodyId selectedBody;			  // 0x50
		hknpWorld* worldForViewerSpecifcBody; // 0x58
	};

	static_assert(sizeof(hknpViewer) == 0x60);
}
