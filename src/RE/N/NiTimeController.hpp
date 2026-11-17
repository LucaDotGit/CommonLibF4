#pragma once

#include "RE/N/NiObject.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class NiObjectNET;
	class NiUpdateData;

	class __declspec(novtable) NiTimeController : public NiObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NiTimeController;
		inline static constexpr const auto& VTABLE = VTABLE::NiTimeController;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::NiTimeController;

		enum class Flags : std::uint16_t; // To-Do

		// add
		virtual void Start(REX::Float32 a_time);							 // 0x28
		virtual void Stop();												 // 0x28
		virtual void Update(NiUpdateData& a_updateData) = 0;				 // 0x29
		virtual void SetTarget(NiObjectNET* a_target);						 // 0x2A
		virtual auto IsTransformController() const -> bool;					 // 0x2B - { return false; }
		virtual auto IsVertexController() const -> bool;					 // 0x2C - { return false; }
		virtual auto ComputeScaledTime(REX::Float32 a_time) -> REX::Float32; // 0x2D
		virtual void OnPreDisplay();										 // 0x2E - { return; }
		virtual auto IsStreamable() const -> bool;							 // 0x2F - { return true; }
		virtual void Start() = 0;											 // 0x30

		// members
		REX::EnumSet<Flags, std::uint16_t> flags; // 0x10
		REX::Float32 frequency;					  // 0x14
		REX::Float32 phase;						  // 0x18
		REX::Float32 lowKeyTime;				  // 0x1C
		REX::Float32 highKeyTime;				  // 0x20
		REX::Float32 startTime;					  // 0x24
		REX::Float32 lastTime;					  // 0x28
		REX::Float32 weightedLastTime;			  // 0x2C
		REX::Float32 scaledTime;				  // 0x30
		NiObjectNET* target;					  // 0x38
		NiPointer<NiTimeController> next;		  // 0x40
	};

	static_assert(sizeof(NiTimeController) == 0x48);
}
