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

	class __declspec(novtable) TESLeveledList
		: public BaseFormComponent // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESLeveledList };
		inline static constexpr auto VTABLE{ VTABLE::TESLeveledList };

		inline static constexpr auto MAX_OBJECT_COUNT = std::numeric_limits<std::uint8_t>::max();

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				kAddedObject = 1ui32 << 31
			};
		};
		using ChangeFlags = ChangeFlag::ChangeFlags;

		enum class Flags : std::uint8_t
		{
			kNone = 0,
			kCalculateFromAllLevelsLTOrEqPCLevel = 1 << 0,
			kCalculateForEachItemInCount = 1 << 1,
			kUseAll = 1 << 2
		};

		enum class LeveledListAllBelowForce : std::int32_t
		{
			kNever = -1,
			kDefault = 0,
			kAlways = 1,
			kShiftUp = 2
		};

		~TESLeveledList() override; // 00

		// override (BaseFormComponent)
		std::uint32_t GetFormComponentType() const override;					  // 01
		void InitializeDataComponent() override;								  // 02
		void ClearDataComponent() override;										  // 03
		void InitComponent() override;											  // 04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 06

		// add
		virtual std::int8_t GetChanceNone();							  // 07
		virtual bool GetMultCalc();										  // 08
		virtual std::int32_t GetMaxLevelDifference();					  // 09 - { return 0; }
		virtual const char* GetOverrideName();							  // 0A - { return nullptr; }
		virtual bool GetCanContainFormsOfType(FormType a_type) const = 0; // 0B

		[[nodiscard]] static auto GetSpecialChanceGlobalMap()
			-> BSTHashMap<const TESLeveledList*, TESGlobal*>&;

		void CalculateCurrentFormList(
			std::uint16_t a_level,
			std::uint16_t a_count,
			BSScrapArray<CALCED_OBJECT>& a_outCont,
			LeveledListAllBelowForce a_allBelowForce = LeveledListAllBelowForce::kDefault,
			bool a_clampToPlayer = false,
			INSTANCE_FILTER* a_instanceFilter = nullptr,
			const char* a_overrideName = nullptr);
		void CalculateCurrentFormListForRef(TESObjectREFR* a_ref, BSScrapArray<CALCED_OBJECT>& a_outCont, bool a_legendary);

		[[nodiscard]] auto GetKeywordChances() const
			-> std::optional<std::vector<std::pair<BGSKeyword*, std::int32_t>>>;
		void SetKeywordChances(std::span<const std::pair<BGSKeyword*, std::int32_t>> a_chances);

		[[nodiscard]] std::uint8_t GetLevObjectCount() const noexcept;
		[[nodiscard]] std::uint8_t GetEditorLevObjectCount() const noexcept;
		[[nodiscard]] std::uint8_t GetScriptLevObjectCount() const noexcept;

		[[nodiscard]] std::span<LEVELED_OBJECT> GetEditorLevObjects() noexcept;
		[[nodiscard]] std::span<LEVELED_OBJECT const> GetEditorLevObjects() const noexcept;
		void SetEditorLevObjects(std::span<LEVELED_OBJECT> a_objects);

		[[nodiscard]] std::span<LEVELED_OBJECT*> GetScriptLevObjects() noexcept;
		[[nodiscard]] std::span<LEVELED_OBJECT* const> GetScriptLevObjects() const noexcept;
		void SetScriptLevObjects(std::span<std::unique_ptr<LEVELED_OBJECT>> a_objects);

		[[nodiscard]] LEVELED_OBJECT* GetNthLevObject(std::uint8_t a_index) const;
		bool SetNthLevObject(std::uint8_t a_index, const LEVELED_OBJECT& a_object);
		bool RemoveNthLevObject(std::uint8_t a_index);

		[[nodiscard]] LEVELED_OBJECT* GetNthEditorLevObject(std::uint8_t a_index) const;
		bool SetNthEditorLevObject(std::uint8_t a_index, const LEVELED_OBJECT& a_object);
		bool RemoveNthEditorLevObject(std::uint8_t a_index);

		[[nodiscard]] LEVELED_OBJECT* GetNthScriptLevObject(std::uint8_t a_index) const;
		bool SetNthScriptLevObject(std::uint8_t a_index, std::unique_ptr<LEVELED_OBJECT> a_object);
		bool RemoveNthScriptLevObject(std::uint8_t a_index);

		bool AddEditorLevObject(LEVELED_OBJECT& a_object);
		bool AddScriptLevObject(std::unique_ptr<LEVELED_OBJECT> a_object);

		void AddEditorLevObjects(std::span<LEVELED_OBJECT> a_objects);
		void AddScriptLevObjects(std::span<std::unique_ptr<LEVELED_OBJECT>> a_objects);

		void ClearLevObjects();
		void ClearEditorLevObjects();
		void ClearScriptLevObjects();

		bool AddLevObjectsChange();

		BSContainer::ForEachResult ForEachLevObject(
			const REX::NotNull<std::function<BSContainer::ForEachResult(LEVELED_OBJECT*)>>& a_predicate) const;
		BSContainer::ForEachResult ForEachEditorLevObject(
			const REX::NotNull<std::function<BSContainer::ForEachResult(LEVELED_OBJECT*)>>& a_predicate) const;
		BSContainer::ForEachResult ForEachScriptLevObject(
			const REX::NotNull<std::function<BSContainer::ForEachResult(LEVELED_OBJECT*)>>& a_predicate) const;

		// members
		TESGlobal* chanceGlobal;													   // 08
		BSTArray<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>>* keywordChances; // 10
		SimpleArray<LEVELED_OBJECT> leveledLists;									   // 18
		SimpleArray<LEVELED_OBJECT*> scriptAddedLists;								   // 20
		std::uint8_t scriptListCount;												   // 28
		std::uint8_t baseListCount;													   // 29
		std::int8_t chanceNone;														   // 2A
		REX::EnumSet<Flags, std::uint8_t> llFlags;									   // 2B
		std::uint8_t maxUseAllCount;												   // 2C
	};
	static_assert(sizeof(TESLeveledList) == 0x30);
}
