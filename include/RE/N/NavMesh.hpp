#pragma once

#include "RE/B/BSNavmesh.hpp"
#include "RE/T/TESChildCell.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) NavMesh
		: public TESForm,	   // 00
		  public TESChildCell, // 20
		  public BSNavmesh	   // 28
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NavMesh };
		inline static constexpr auto VTABLE{ VTABLE::NavMesh };
		inline static constexpr auto FORM_TYPE{ FormType::kNavMesh };

		~NavMesh() override; // 00

		// add
		virtual void Save();						 // 4A - { return; }
		virtual bool SavesBefore(FORM* a_groupFORM); // 4B - { return false; }
		virtual bool SavesBefore(TESForm* a_form);	 // 4C - { return false; }
		virtual bool ProcessBeforeSave();			 // 4D - { return false; }
	};
	static_assert(sizeof(NavMesh) == 0x230);
}
