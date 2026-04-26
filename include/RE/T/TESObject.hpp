#pragma once

#include "RE/N/NiPointer.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class NiAVObject;

	class __declspec(novtable) TESObject
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESObject };
		inline static constexpr auto VTABLE{ VTABLE::TESObject };
		inline static constexpr auto FORM_TYPE{ FormType::kNone };

		// add
		virtual bool IsBoundAnimObject();														   // 4A - { return false; }
		virtual TESWaterForm* GetWaterType() const;												   // 4B - { return nullptr; }
		virtual bool IsAutoCalc() const;														   // 4C - { return false; }
		virtual void SetAutoCalc(bool a_set);													   // 4D - { return; }
		virtual void Clone3D(TESObjectREFR* a_ref, NiPointer<NiAVObject>& a_result, bool a_unk01); // 4E - { return; }
		virtual void UnClone3D(TESObjectREFR* a_requester);										   // 4F
		virtual bool IsMarker();																   // 50
		virtual bool IsOcclusionMarker();														   // 51
		virtual bool ReplaceModel();															   // 52
		virtual std::uint32_t IncRef();															   // 53 - { return 0; }
		virtual std::uint32_t DecRef();															   // 54 - { return 0; }
		virtual NiAVObject* LoadGraphics(TESObjectREFR* a_ref);									   // 55
	};
	static_assert(sizeof(TESObject) == 0x20);
}
