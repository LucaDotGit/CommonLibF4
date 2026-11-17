#pragma once

#include "RE/N/NiPointer.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class NiAVObject;

	class __declspec(novtable) TESObject : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESObject;
		inline static constexpr const auto& VTABLE = VTABLE::TESObject;
		inline static constexpr auto FORM_TYPE = FormType::None;

		~TESObject() override; // 0x00

		// add
		virtual auto IsBoundAnimObject() -> bool;			// 0x4A - { return false; }
		virtual auto GetWaterType() const -> TESWaterForm*; // 0x4B - { return nullptr; }
		virtual auto IsAutoCalc() const -> bool;			// 0x4C - { return false; }
		virtual void SetAutoCalc(bool a_set);				// 0x4D - { return; }
		virtual void Clone3D(TESObjectREFR* a_ref, NiPointer<NiAVObject>& a_result, bool a_unk01); // 0x4E - { return; }
		virtual void UnClone3D(TESObjectREFR* a_requester);										   // 0x4F
		virtual auto IsMarker() -> bool;														   // 0x50
		virtual auto IsOcclusionMarker() -> bool;												   // 0x51
		virtual auto ReplaceModel() -> bool;													   // 0x52
		virtual auto IncRef() -> std::uint32_t;							// 0x53 - { return 0; }
		virtual auto DecRef() -> std::uint32_t;							// 0x54 - { return 0; }
		virtual auto LoadGraphics(TESObjectREFR* a_ref) -> NiAVObject*; // 0x55
	};

	static_assert(sizeof(TESObject) == 0x20);
}
