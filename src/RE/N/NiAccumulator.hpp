#pragma once

#include "RE/N/NiObject.hpp"

namespace RE
{
	class BSGeometry;
	class NiBound;
	class NiCamera;
	class NiVisibleArray;

	class __declspec(novtable) NiAccumulator : public NiObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NiAccumulator;
		inline static constexpr const auto& VTABLE = VTABLE::NiAccumulator;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::NiAccumulator;

		~NiAccumulator() override; // 0x00

		// add
		virtual void StartAccumulating(const NiCamera* a_camera);				// 0x28
		virtual void FinishAccumulating();										// 0x29
		virtual void RegisterObjectArray(NiVisibleArray* a_array);				// 0x2A
		virtual void StartGroupingAlphas(const NiBound* a_unk00, bool a_unk01); // 0x2B
		virtual void StopGroupingAlphas();										// 0x2C
		virtual void RegisterObject(BSGeometry* a_object);						// 0x2D

		// members
		NiCamera* camera; // 0x10
	};

	static_assert(sizeof(NiAccumulator) == 0x18);
}
