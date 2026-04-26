#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class ContainerItemExtra
	{
	public:
		union Conditional
		{
		public:
			Conditional() = default;

			Conditional(TESGlobal* a_global)
				: ownerGlobal(a_global)
			{
			}

			Conditional(std::int32_t a_rank)
				: ownerRank(a_rank)
			{
			}

			~Conditional() noexcept = default;

			Conditional(const Conditional&) = default;
			Conditional(Conditional&&) noexcept = default;

			Conditional& operator=(const Conditional&) noexcept = default;
			Conditional& operator=(Conditional&&) noexcept = default;

			// members
			TESGlobal* ownerGlobal;
			std::int32_t ownerRank;
			void* padding{ nullptr };
		};
		static_assert(sizeof(Conditional) == 0x08);

		ContainerItemExtra() = default;

		ContainerItemExtra(TESForm* a_ownerForm)
			: ownerForm(a_ownerForm)
		{
		}

		ContainerItemExtra(TESForm* a_ownerForm, TESGlobal* a_ownerGlobal)
			: ownerForm(a_ownerForm),
			  conditional(a_ownerGlobal)
		{
		}

		ContainerItemExtra(TESForm* a_ownerForm, std::int32_t a_ownerRank)
			: ownerForm(a_ownerForm),
			  conditional(a_ownerRank)
		{
		}

		~ContainerItemExtra() noexcept = default;

		ContainerItemExtra(const ContainerItemExtra&) = default;
		ContainerItemExtra(ContainerItemExtra&&) noexcept = default;

		ContainerItemExtra& operator=(const ContainerItemExtra&) = default;
		ContainerItemExtra& operator=(ContainerItemExtra&&) noexcept = default;

		GAME_HEAP_REDEFINE_NEW(ContainerItemExtra);

		// members
		TESForm* ownerForm{ nullptr };		  // 00
		Conditional conditional;			  // 08
		REX::Float32 healthMult{ 100.0_f32 }; // 10
	};
	static_assert(sizeof(ContainerItemExtra) == 0x18);
}
