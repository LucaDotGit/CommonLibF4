#pragma once

#include "RE/B/BaseFormComponent.hpp"
#include "RE/M/MemoryManager.hpp"
#include "RE/S/SimpleArray.hpp"

namespace RE::BSContainer
{
	enum class ForEachResult : std::int32_t;
}

namespace RE
{
	class __declspec(novtable) TESSpellList
		: public BaseFormComponent // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESSpellList };
		inline static constexpr auto VTABLE{ VTABLE::TESSpellList };

		class SpellData
		{
		public:
			GAME_HEAP_REDEFINE_NEW(SpellData);

			[[nodiscard]] std::uint32_t GetSpellCount() const noexcept;
			[[nodiscard]] std::uint32_t GetLevSpellCount() const noexcept;
			[[nodiscard]] std::uint32_t GetShoutCount() const noexcept;

			[[nodiscard]] std::span<SpellItem*> GetSpells() noexcept;
			[[nodiscard]] std::span<TESLevSpell*> GetLevSpells() noexcept;
			[[nodiscard]] std::span<TESShout*> GetShouts() noexcept;

			[[nodiscard]] std::span<SpellItem* const> GetSpells() const noexcept;
			[[nodiscard]] std::span<TESLevSpell* const> GetLevSpells() const noexcept;
			[[nodiscard]] std::span<TESShout* const> GetShouts() const noexcept;

			void SetSpells(std::span<SpellItem*> a_spells);
			void SetLevSpells(std::span<TESLevSpell*> a_levSpells);
			void SetShouts(std::span<TESShout*> a_shouts);

			void ClearSpells();
			void ClearLevSpells();
			void ClearShouts();

			BSContainer::ForEachResult ForEachSpell(
				const REX::NotNull<std::function<BSContainer::ForEachResult(SpellItem*)>>& a_predicate) const;
			BSContainer::ForEachResult ForEachLevSpell(
				const REX::NotNull<std::function<BSContainer::ForEachResult(TESLevSpell*)>>& a_predicate) const;
			BSContainer::ForEachResult ForEachShout(
				const REX::NotNull<std::function<BSContainer::ForEachResult(TESShout*)>>& a_predicate) const;

			// members
			SimpleArray<SpellItem*> spells;		 // 00
			SimpleArray<TESLevSpell*> levSpells; // 08
			SimpleArray<TESShout*> shouts;		 // 10
			std::uint32_t numSpells;			 // 18
			std::uint32_t numLevSpells;			 // 1C
			std::uint32_t numShouts;			 // 20
		};
		static_assert(sizeof(SpellData) == 0x28);

		~TESSpellList() override; // 00

		// override (BaseFormComponent)
		std::uint32_t GetFormComponentType() const override;					  // 01
		void InitializeDataComponent() override;								  // 02
		void ClearDataComponent() override;										  // 03
		void InitComponent() override;											  // 04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 06

		// members
		SpellData* spellData; // 08
	};
	static_assert(sizeof(TESSpellList) == 0x10);
}
