#pragma once

#include "RE/N/NiObject.hpp"

namespace RE
{
	class BSGeometry;
	class NiBound;
	class NiCamera;
	class NiVisibleArray;

	class __declspec(novtable) NiAccumulator
		: public NiObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NiAccumulator };
		inline static constexpr auto VTABLE{ VTABLE::NiAccumulator };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::NiAccumulator };

		~NiAccumulator() override; // 00

		// add
		virtual void StartAccumulating(const NiCamera* a_camera);				// 28
		virtual void FinishAccumulating();										// 29
		virtual void RegisterObjectArray(NiVisibleArray* a_array);				// 2A
		virtual void StartGroupingAlphas(const NiBound* a_unk00, bool a_unk01); // 2B
		virtual void StopGroupingAlphas();										// 2C
		virtual void RegisterObject(BSGeometry* a_object);						// 2D

		// members
		NiCamera* camera; // 10
	};
	static_assert(sizeof(NiAccumulator) == 0x18);
}
