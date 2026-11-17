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

			Conditional(TESGlobal* a_global) :
				ownerGlobal(a_global)
			{
			}

			Conditional(std::int32_t a_rank) :
				ownerRank(a_rank)
			{
			}

			~Conditional() noexcept = default;

			Conditional(const Conditional&) = default;
			Conditional(Conditional&&) noexcept = default;

			auto operator=(const Conditional&) noexcept -> Conditional& = default;
			auto operator=(Conditional&&) noexcept -> Conditional& = default;

			// members
			TESGlobal* ownerGlobal;
			std::int32_t ownerRank;
			void* padding{nullptr};
		};

		static_assert(sizeof(Conditional) == 0x08);

		ContainerItemExtra() = default;

		ContainerItemExtra(TESForm* a_ownerForm) :
			ownerForm(a_ownerForm)
		{
		}

		ContainerItemExtra(TESForm* a_ownerForm, TESGlobal* a_ownerGlobal) :
			ownerForm(a_ownerForm),
			conditional(a_ownerGlobal)
		{
		}

		ContainerItemExtra(TESForm* a_ownerForm, std::int32_t a_ownerRank) :
			ownerForm(a_ownerForm),
			conditional(a_ownerRank)
		{
		}

		~ContainerItemExtra() noexcept = default;

		ContainerItemExtra(const ContainerItemExtra&) = default;
		ContainerItemExtra(ContainerItemExtra&&) noexcept = default;

		auto operator=(const ContainerItemExtra&) -> ContainerItemExtra& = default;
		auto operator=(ContainerItemExtra&&) noexcept -> ContainerItemExtra& = default;

		GAME_HEAP_REDEFINE_NEW(ContainerItemExtra);

		// members
		TESForm* ownerForm{nullptr};							   // 0x00
		Conditional conditional;								   // 0x08
		REX::Float32 healthMult{static_cast<REX::Float32>(100.0)}; // 0x10
	};

	static_assert(sizeof(ContainerItemExtra) == 0x18);
}
