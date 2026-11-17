#pragma once

#include "RE/B/BSInputEventUser.hpp"
#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/C/CameraStates.hpp"
#include "RE/M/MemoryManager.hpp"
#include "RE/N/NiQuaternion.hpp"

namespace RE
{
	class BGSLoadFormBuffer;
	class BGSSaveFormBuffer;
	class NiPoint3;
	class TESCamera;

	class __declspec(novtable) TESCameraState :
		public BSIntrusiveRefCounted, // 0x00
		public BSInputEventUser		  // 0x04
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESCameraState;
		inline static constexpr const auto& VTABLE = VTABLE::TESCameraState;

		~TESCameraState() override; // 0x00

		// add
		virtual void Begin();											   // 0x09 - { return; }
		virtual void End();												   // 0x0A - { return; }
		virtual void Update(BSTSmartPointer<TESCameraState>& a_nextState); // 0x0B
		virtual void GetRotation(NiQuaternion& a_rotation) const;		   // 0x0C
		virtual void GetTranslation(NiPoint3& a_translation) const;		   // 0x0D
		virtual void SaveGame(BGSSaveFormBuffer* a_saveGameBuffer);		   // 0x0E - { return; }
		virtual void LoadGame(BGSLoadFormBuffer* a_loadGameBuffer);		   // 0x0F - { return; }
		virtual void Revert(BGSLoadFormBuffer* a_loadGameBuffer);		   // 0x10 - { return; }

		GAME_HEAP_REDEFINE_NEW(TESCameraState);

		// members
		TESCamera* camera;						  // 0x18
		REX::Enum<CameraStates, std::int32_t> id; // 0x20
	};

	static_assert(sizeof(TESCameraState) == 0x28);
}
