#pragma once

#include "RE/P/PTYPE.hpp"

namespace RE
{
	class ActorPackageLoadFormBuffer;
	class BGSSaveFormBuffer;
	class IProcedureTreeExecState;

	class __declspec(novtable) ActorPackageData
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ActorPackageData };
		inline static constexpr auto VTABLE{ VTABLE::ActorPackageData };

		virtual ~ActorPackageData(); // 00

		// add
		virtual PTYPE GetPackageType() = 0;												   // 01
		virtual IProcedureTreeExecState* GetProcedureExecState();						   // 02 - { return nullptr; }
		virtual void SetProcedureExecState(IProcedureTreeExecState& a_procedureExecState); // 03 - { return; }
		virtual void ClearProcedureExecState();											   // 04 - { return; }
		virtual void SaveGame(BGSSaveFormBuffer* a_saveGameBuffer) = 0;					   // 05
		virtual void LoadGame(ActorPackageLoadFormBuffer* a_loadGameBuffer) = 0;		   // 06
		virtual void InitLoadGame(ActorPackageLoadFormBuffer* a_loadGameBuffer);		   // 07 - { return; }
		virtual void ResetPackData(TESPackage* a_pack);									   // 08 - { return; }
	};
	static_assert(sizeof(ActorPackageData) == 0x08);
}
