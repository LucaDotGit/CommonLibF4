#pragma once

#include "RE/C/ContainerItemExtra.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class ContainerObject
	{
	public:
		ContainerObject() = default;

		~ContainerObject()
		{
			if (itemExtra) {
				delete itemExtra;
				itemExtra = nullptr;
			}
		}

		ContainerObject(TESBoundObject* a_obj, std::int32_t a_count)
			: count(a_count),
			  obj(a_obj)
		{
		}

		ContainerObject(TESBoundObject* a_obj, std::int32_t a_count, TESForm* a_ownerForm)
			: count(a_count),
			  obj(a_obj),
			  itemExtra(new ContainerItemExtra(a_ownerForm))
		{
		}

		ContainerObject(TESBoundObject* a_obj, std::int32_t a_count, TESForm* a_ownerForm, TESGlobal* a_ownerGlobal)
			: count(a_count),
			  obj(a_obj),
			  itemExtra(new ContainerItemExtra(a_ownerForm, a_ownerGlobal))
		{
		}

		ContainerObject(TESBoundObject* a_obj, std::int32_t a_count, TESForm* a_ownerForm, std::int32_t a_ownerRank)
			: count(a_count),
			  obj(a_obj),
			  itemExtra(new ContainerItemExtra(a_ownerForm, a_ownerRank))
		{
		}

		ContainerObject(const ContainerObject&) = default;
		ContainerObject(ContainerObject&&) noexcept = default;

		ContainerObject& operator=(const ContainerObject&) = default;
		ContainerObject& operator=(ContainerObject&&) noexcept = default;

		GAME_HEAP_REDEFINE_NEW(ContainerObject);

		// members
		std::int32_t count{ 0 };				  // 00
		TESBoundObject* obj{ nullptr };			  // 08
		ContainerItemExtra* itemExtra{ nullptr }; // 10
	};
	static_assert(sizeof(ContainerObject) == 0x18);
}
