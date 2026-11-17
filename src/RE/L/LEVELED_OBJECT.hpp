#pragma once

#include "RE/C/ContainerItemExtra.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class ContainerItemExtra;

	class LEVELED_OBJECT
	{
	public:
		LEVELED_OBJECT() noexcept = default;

		LEVELED_OBJECT(TESForm* a_form, std::uint16_t a_level, std::uint16_t a_count, std::uint8_t a_chanceNone)
			noexcept :
			form(a_form),
			itemExtra(),
			count(a_count),
			level(a_level),
			chanceNone(a_chanceNone)
		{
		}

		LEVELED_OBJECT(
			TESForm* a_form,
			std::uint16_t a_level,
			std::uint16_t a_count,
			std::uint8_t a_chanceNone,
			TESForm* a_owner) :
			form(a_form),
			itemExtra(new ContainerItemExtra(a_owner)),
			count(a_count),
			level(a_level),
			chanceNone(a_chanceNone)
		{
		}

		~LEVELED_OBJECT() noexcept
		{
			if (itemExtra) {
				delete itemExtra;
				itemExtra = nullptr;
			}
		}

		LEVELED_OBJECT(const LEVELED_OBJECT&) noexcept = default;
		LEVELED_OBJECT(LEVELED_OBJECT&&) noexcept = default;

		auto operator=(const LEVELED_OBJECT&) noexcept -> LEVELED_OBJECT& = default;
		auto operator=(LEVELED_OBJECT&&) noexcept -> LEVELED_OBJECT& = default;

		GAME_HEAP_REDEFINE_NEW(LEVELED_OBJECT);

		// members
		TESForm* form;				   // 0x00
		ContainerItemExtra* itemExtra; // 0x08
		std::uint16_t count;		   // 0x10
		std::uint16_t level;		   // 0x12
		std::uint8_t chanceNone;	   // 0x14
	};

	static_assert(sizeof(LEVELED_OBJECT) == 0x18);
}
