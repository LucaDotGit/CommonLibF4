#pragma once

#include "RE/B/BGSTypedFormValuePair.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BSTTuple.hpp"
#include "RE/B/BaseFormComponent.hpp"
#include "RE/F/FormType.hpp"
#include "RE/S/SimpleArray.hpp"

namespace RE::BSContainer
{
	enum class ForEachResult : std::int32_t;
}

namespace RE
{
	class CALCED_OBJECT;
	class ContainerItemExtra;
	class LEVELED_OBJECT;
	class INSTANCE_FILTER;

	class __declspec(novtable) TESLeveledList : public BaseFormComponent // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESLeveledList;
		inline static constexpr const auto& VTABLE = VTABLE::TESLeveledList;

		inline static constexpr auto MAX_OBJECT_COUNT = std::numeric_limits<std::uint8_t>::max();

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				AddedObject = static_cast<std::uint32_t>(1) << 31
			};
		};

		using ChangeFlags = ChangeFlag::ChangeFlags;

		enum class Flags : std::uint8_t
		{
			None = 0,
			CalculateFromAllLevelsLTOrEqPCLevel = 1 << 0,
			CalculateForEachItemInCount = 1 << 1,
			UseAll = 1 << 2
		};

		enum class LeveledListAllBelowForce : std::int32_t
		{
			Never = -1,
			Default = 0,
			Always = 1,
			ShiftUp = 2
		};

		~TESLeveledList() override; // 0x00

		// override (BaseFormComponent)
		auto GetFormComponentType() const -> std::uint32_t override;			  // 0x01
		void InitializeDataComponent() override;								  // 0x02
		void ClearDataComponent() override;										  // 0x03
		void InitComponent() override;											  // 0x04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 0x05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 0x06

		// add
		virtual auto GetChanceNone() -> std::int8_t;							  // 0x07
		virtual auto GetMultCalc() -> bool;										  // 0x08
		virtual auto GetMaxLevelDifference() -> std::int32_t;					  // 0x09 - { return 0; }
		virtual auto GetOverrideName() -> const char*;							  // 0x0A - { return nullptr; }
		virtual auto GetCanContainFormsOfType(FormType a_type) const -> bool = 0; // 0x0B

		[[nodiscard]]
		static auto GetSpecialChanceGlobalMap() noexcept -> BSTHashMap<const TESLeveledList*, TESGlobal*>&;

		void CalculateCurrentFormList(
			std::uint16_t a_level,
			std::uint16_t a_count,
			BSScrapArray<CALCED_OBJECT>& a_outCalc,
			LeveledListAllBelowForce a_allBelowForce = LeveledListAllBelowForce::Default,
			bool a_clampToPlayer = false,
			INSTANCE_FILTER* a_instanceFilter = nullptr,
			const char* a_overrideName = nullptr);

		void CalculateCurrentFormListForRef(
			TESObjectREFR* a_ref,
			BSScrapArray<CALCED_OBJECT>& a_outCalc,
			bool a_legendary);

		[[nodiscard]]
		auto GetKeywordChances() const -> std::optional<BSTArray<std::pair<BGSKeyword*, std::uint32_t>>>;
		void SetKeywordChances(std::span<const std::pair<BGSKeyword*, std::uint32_t>> a_chances);

		[[nodiscard]]
		auto GetLevObjectCount() const noexcept -> std::uint8_t;
		[[nodiscard]]
		auto GetEditorLevObjectCount() const noexcept -> std::uint8_t;
		[[nodiscard]]
		auto GetScriptLevObjectCount() const noexcept -> std::uint8_t;

		[[nodiscard]]
		auto GetEditorLevObjects() noexcept -> std::span<LEVELED_OBJECT>;
		[[nodiscard]]
		auto GetEditorLevObjects() const noexcept -> std::span<LEVELED_OBJECT const>;
		void SetEditorLevObjects(std::span<LEVELED_OBJECT> a_objects);

		[[nodiscard]]
		auto GetScriptLevObjects() noexcept -> std::span<LEVELED_OBJECT*>;
		[[nodiscard]]
		auto GetScriptLevObjects() const noexcept -> std::span<LEVELED_OBJECT* const>;
		void SetScriptLevObjects(std::span<std::unique_ptr<LEVELED_OBJECT>> a_objects);

		[[nodiscard]]
		auto GetNthLevObject(std::uint8_t a_index) const -> LEVELED_OBJECT*;
		auto SetNthLevObject(std::uint8_t a_index, const LEVELED_OBJECT& a_object) -> bool;
		auto RemoveNthLevObject(std::uint8_t a_index) -> bool;

		[[nodiscard]]
		auto GetNthEditorLevObject(std::uint8_t a_index) const -> LEVELED_OBJECT*;
		auto SetNthEditorLevObject(std::uint8_t a_index, const LEVELED_OBJECT& a_object) -> bool;
		auto RemoveNthEditorLevObject(std::uint8_t a_index) -> bool;

		[[nodiscard]]
		auto GetNthScriptLevObject(std::uint8_t a_index) const -> LEVELED_OBJECT*;
		auto SetNthScriptLevObject(std::uint8_t a_index, std::unique_ptr<LEVELED_OBJECT> a_object) -> bool;
		auto RemoveNthScriptLevObject(std::uint8_t a_index) -> bool;

		auto AddEditorLevObject(LEVELED_OBJECT& a_object) -> bool;
		auto AddScriptLevObject(std::unique_ptr<LEVELED_OBJECT> a_object) -> bool;

		void AddEditorLevObjects(std::span<LEVELED_OBJECT> a_objects);
		void AddScriptLevObjects(std::span<std::unique_ptr<LEVELED_OBJECT>> a_objects);

		void ClearLevObjects();
		void ClearEditorLevObjects();
		void ClearScriptLevObjects();

		auto AddLevObjectsChange() -> bool;

		auto ForEachLevObject(
			const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(LEVELED_OBJECT*) const>>& a_predicate)
			const -> BSContainer::ForEachResult;
		auto ForEachEditorLevObject(
			const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(LEVELED_OBJECT*) const>>& a_predicate)
			const -> BSContainer::ForEachResult;
		auto ForEachScriptLevObject(
			const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(LEVELED_OBJECT*) const>>& a_predicate)
			const -> BSContainer::ForEachResult;

		// members
		TESGlobal* chanceGlobal;													   // 0x08
		BSTArray<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>>* keywordChances; // 0x10
		SimpleArray<LEVELED_OBJECT> leveledLists;									   // 0x18
		SimpleArray<LEVELED_OBJECT*> scriptAddedLists;								   // 0x20
		std::uint8_t scriptListCount;												   // 0x28
		std::uint8_t baseListCount;													   // 0x29
		std::uint8_t chanceNone;													   // 0x2A
		REX::EnumSet<Flags, std::uint8_t> llFlags;									   // 0x2B
		std::uint8_t maxUseAllCount;												   // 0x2C
	};

	static_assert(sizeof(TESLeveledList) == 0x30);
}
