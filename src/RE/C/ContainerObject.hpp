#pragma once

#include "RE/C/ContainerItemExtra.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class ContainerObject
	{
	public:
		ContainerObject() noexcept = default;

		~ContainerObject() noexcept
		{
			if (itemExtra) {
				delete itemExtra;
				itemExtra = nullptr;
			}
		}

		ContainerObject(TESBoundObject* a_obj, std::int32_t a_count) noexcept :
			count(a_count),
			obj(a_obj)
		{
		}

		ContainerObject(TESBoundObject* a_obj, std::int32_t a_count, TESForm* a_ownerForm) :
			count(a_count),
			obj(a_obj),
			itemExtra(new ContainerItemExtra(a_ownerForm))
		{
		}

		ContainerObject(TESBoundObject* a_obj, std::int32_t a_count, TESForm* a_ownerForm, TESGlobal* a_ownerGlobal) :
			count(a_count),
			obj(a_obj),
			itemExtra(new ContainerItemExtra(a_ownerForm, a_ownerGlobal))
		{
		}

		ContainerObject(TESBoundObject* a_obj, std::int32_t a_count, TESForm* a_ownerForm, std::int32_t a_ownerRank) :
			count(a_count),
			obj(a_obj),
			itemExtra(new ContainerItemExtra(a_ownerForm, a_ownerRank))
		{
		}

		ContainerObject(const ContainerObject&) noexcept = default;
		ContainerObject(ContainerObject&&) noexcept = default;

		auto operator=(const ContainerObject&) noexcept -> ContainerObject& = default;
		auto operator=(ContainerObject&&) noexcept -> ContainerObject& = default;

		GAME_HEAP_REDEFINE_NEW(ContainerObject);

		// members
		std::int32_t count{0};					// 0x00
		TESBoundObject* obj{nullptr};			// 0x08
		ContainerItemExtra* itemExtra{nullptr}; // 0x10
	};

	static_assert(sizeof(ContainerObject) == 0x18);
}
