#pragma once

#include "RE/N/NiObject.hpp"

namespace RE
{
	class NiAVObject;
	class NiUpdateData;

	class __declspec(novtable) NiCollisionObject
		: public NiObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NiCollisionObject };
		inline static constexpr auto VTABLE{ VTABLE::NiCollisionObject };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::NiCollisionObject };

		// add
		virtual void SetSceneGraphObject(NiAVObject* a_sceneObject); // 28
		virtual void UpdateWorldData(NiUpdateData& a_updateData);	 // 29
		virtual void Initialize(void* a_data);						 // 2A - { return; }
		virtual void Convert(std::uint32_t a_version, void* a_data); // 2B - { return; }

		// members
		NiAVObject* sceneObject; // 10
	};
	static_assert(sizeof(NiCollisionObject) == 0x18);
}
