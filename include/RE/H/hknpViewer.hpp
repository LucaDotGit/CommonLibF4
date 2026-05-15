#pragma once

#include "RE/H/hkProcess.hpp"
#include "RE/H/hkReferencedObject.hpp"
#include "RE/H/hknpBodyId.hpp"
#include "RE/H/hknpProcessContextListener.hpp"

namespace RE
{
	class hknpProcessContext;
	class hknpWorld;

	class __declspec(novtable) hknpViewer
		: public hkReferencedObject,		// 00
		  public hkProcess,					// 10
		  public hknpProcessContextListener // 40
	{
	public:
		~hknpViewer() override; // 00

		// add
		virtual void OnSetViewerSpecificBody(); // 04

		// members
		hknpProcessContext* context;		  // 48
		hknpBodyId selectedBody;			  // 50
		hknpWorld* worldForViewerSpecifcBody; // 58
	};
	static_assert(sizeof(hknpViewer) == 0x60);
}
