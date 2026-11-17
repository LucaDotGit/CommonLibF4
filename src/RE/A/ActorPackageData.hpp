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
		inline static constexpr const auto& RTTI = RTTI::ActorPackageData;
		inline static constexpr const auto& VTABLE = VTABLE::ActorPackageData;

		virtual ~ActorPackageData(); // 0x00

		// add
		virtual auto GetPackageType() -> PTYPE = 0;										   // 0x01
		virtual auto GetProcedureExecState() -> IProcedureTreeExecState*;				   // 0x02 - { return nullptr; }
		virtual void SetProcedureExecState(IProcedureTreeExecState& a_procedureExecState); // 0x03 - { return; }
		virtual void ClearProcedureExecState();											   // 0x04 - { return; }
		virtual void SaveGame(BGSSaveFormBuffer* a_saveGameBuffer) = 0;					   // 0x05
		virtual void LoadGame(ActorPackageLoadFormBuffer* a_loadGameBuffer) = 0;		   // 0x06
		virtual void InitLoadGame(ActorPackageLoadFormBuffer* a_loadGameBuffer);		   // 0x07 - { return; }
		virtual void ResetPackData(TESPackage* a_pack);									   // 0x08 - { return; }
	};

	static_assert(sizeof(ActorPackageData) == 0x08);
}
