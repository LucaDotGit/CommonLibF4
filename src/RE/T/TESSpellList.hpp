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
	class __declspec(novtable) TESSpellList : public BaseFormComponent // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESSpellList;
		inline static constexpr const auto& VTABLE = VTABLE::TESSpellList;

		class SpellData
		{
		public:
			GAME_HEAP_REDEFINE_NEW(SpellData);

			[[nodiscard]]
			auto GetSpellCount() const noexcept -> std::uint32_t;
			[[nodiscard]]
			auto GetLevSpellCount() const noexcept -> std::uint32_t;
			[[nodiscard]]
			auto GetShoutCount() const noexcept -> std::uint32_t;

			[[nodiscard]]
			auto GetSpells() noexcept -> std::span<SpellItem*>;
			[[nodiscard]]
			auto GetLevSpells() noexcept -> std::span<TESLevSpell*>;
			[[nodiscard]]
			auto GetShouts() noexcept -> std::span<TESShout*>;

			[[nodiscard]]
			auto GetSpells() const noexcept -> std::span<SpellItem* const>;
			[[nodiscard]]
			auto GetLevSpells() const noexcept -> std::span<TESLevSpell* const>;
			[[nodiscard]]
			auto GetShouts() const noexcept -> std::span<TESShout* const>;

			void SetSpells(std::span<SpellItem*> a_spells);
			void SetLevSpells(std::span<TESLevSpell*> a_levSpells);
			void SetShouts(std::span<TESShout*> a_shouts);

			void ClearSpells();
			void ClearLevSpells();
			void ClearShouts();

			auto ForEachSpell(
				const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(SpellItem*) const>>& a_predicate)
				const -> BSContainer::ForEachResult;
			auto ForEachLevSpell(
				const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(TESLevSpell*) const>>&
					a_predicate) const -> BSContainer::ForEachResult;
			auto ForEachShout(
				const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(TESShout*) const>>& a_predicate)
				const -> BSContainer::ForEachResult;

			// members
			SimpleArray<SpellItem*> spells;		 // 0x00
			SimpleArray<TESLevSpell*> levSpells; // 0x08
			SimpleArray<TESShout*> shouts;		 // 0x10
			std::uint32_t numSpells;			 // 0x18
			std::uint32_t numLevSpells;			 // 0x1C
			std::uint32_t numShouts;			 // 0x20
		};

		static_assert(sizeof(SpellData) == 0x28);

		~TESSpellList() override; // 0x00

		// override (BaseFormComponent)
		auto GetFormComponentType() const -> std::uint32_t override;			  // 0x01
		void InitializeDataComponent() override;								  // 0x02
		void ClearDataComponent() override;										  // 0x03
		void InitComponent() override;											  // 0x04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 0x05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 0x06

		// members
		SpellData* spellData; // 0x08
	};

	static_assert(sizeof(TESSpellList) == 0x10);
}
