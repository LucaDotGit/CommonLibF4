#pragma once

#include "RE/N/NiObject.hpp"

namespace RE
{
	class NiAVObject;
	class NiUpdateData;

	class __declspec(novtable) NiCollisionObject : public NiObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NiCollisionObject;
		inline static constexpr const auto& VTABLE = VTABLE::NiCollisionObject;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::NiCollisionObject;

		// add
		virtual void SetSceneGraphObject(NiAVObject* a_sceneObject); // 0x28
		virtual void UpdateWorldData(NiUpdateData& a_updateData);	 // 0x29
		virtual void Initialize(void* a_data);						 // 0x2A - { return; }
		virtual void Convert(std::uint32_t a_version, void* a_data); // 0x2B - { return; }

		// members
		NiAVObject* sceneObject; // 0x10
	};

	static_assert(sizeof(NiCollisionObject) == 0x18);
}
