#pragma once

#include "RE/N/NiObject.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class NiObjectNET;
	class NiUpdateData;

	class __declspec(novtable) NiTimeController
		: public NiObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NiTimeController };
		inline static constexpr auto VTABLE{ VTABLE::NiTimeController };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::NiTimeController };

		enum class Flags : std::uint16_t; // TODO

		// add
		virtual void Start(REX::Float32 a_time);					 // 28
		virtual void Stop();										 // 28
		virtual void Update(NiUpdateData& a_updateData) = 0;		 // 29
		virtual void SetTarget(NiObjectNET* a_target);				 // 2A
		virtual bool IsTransformController() const;					 // 2B - { return false; }
		virtual bool IsVertexController() const;					 // 2C - { return false; }
		virtual REX::Float32 ComputeScaledTime(REX::Float32 a_time); // 2D
		virtual void OnPreDisplay();								 // 2E - { return; }
		virtual bool IsStreamable() const;							 // 2F - { return true; }
		virtual void Start() = 0;									 // 30

		// members
		REX::EnumSet<Flags, std::uint16_t> flags; // 10
		REX::Float32 frequency;					  // 14
		REX::Float32 phase;						  // 18
		REX::Float32 lowKeyTime;				  // 1C
		REX::Float32 highKeyTime;				  // 20
		REX::Float32 startTime;					  // 24
		REX::Float32 lastTime;					  // 28
		REX::Float32 weightedLastTime;			  // 2C
		REX::Float32 scaledTime;				  // 30
		NiObjectNET* target;					  // 38
		NiPointer<NiTimeController> next;		  // 40
	};
	static_assert(sizeof(NiTimeController) == 0x48);
}
