#pragma once

#include "RE/B/BSInputEventUser.hpp"
#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/C/CameraStates.hpp"
#include "RE/M/MemoryManager.hpp"
#include "RE/N/NiPoint.hpp"
#include "RE/N/NiQuaternion.hpp"

namespace RE
{
	class BGSLoadFormBuffer;
	class BGSSaveFormBuffer;
	class TESCamera;

	class __declspec(novtable) TESCameraState
		: public BSIntrusiveRefCounted, // 00
		  public BSInputEventUser		// 04
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESCameraState };
		inline static constexpr auto VTABLE{ VTABLE::TESCameraState };

		~TESCameraState() override; // 00

		// add
		virtual void Begin();											   // 09 - { return; }
		virtual void End();												   // 0A - { return; }
		virtual void Update(BSTSmartPointer<TESCameraState>& a_nextState); // 0B
		virtual void GetRotation(NiQuaternion& a_rotation) const;		   // 0C
		virtual void GetTranslation(NiPoint3& a_translation) const;		   // 0D
		virtual void SaveGame(BGSSaveFormBuffer* a_saveGameBuffer);		   // 0E - { return; }
		virtual void LoadGame(BGSLoadFormBuffer* a_loadGameBuffer);		   // 0F - { return; }
		virtual void Revert(BGSLoadFormBuffer* a_loadGameBuffer);		   // 10 - { return; }

		GAME_HEAP_REDEFINE_NEW(TESCameraState);

		// members
		TESCamera* camera;						  // 18
		REX::Enum<CameraStates, std::int32_t> id; // 20
	};
	static_assert(sizeof(TESCameraState) == 0x28);
}
