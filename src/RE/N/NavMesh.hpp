#pragma once

#include "RE/B/BSNavmesh.hpp"
#include "RE/T/TESChildCell.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) NavMesh :
		public TESForm,		 // 0x00
		public TESChildCell, // 0x20
		public BSNavmesh	 // 0x28
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NavMesh;
		inline static constexpr const auto& VTABLE = VTABLE::NavMesh;
		inline static constexpr auto FORM_TYPE = FormType::NavMesh;

		~NavMesh() override; // 0x00

		// add
		virtual void Save();								 // 0x4A - { return; }
		virtual auto SavesBefore(FORM* a_groupFORM) -> bool; // 0x4B - { return false; }
		virtual auto SavesBefore(TESForm* a_form) -> bool;	 // 0x4C - { return false; }
		virtual auto ProcessBeforeSave() -> bool;			 // 0x4D - { return false; }
	};

	static_assert(sizeof(NavMesh) == 0x230);
}
