#pragma once

#include "RE/A/ACTOR_BASE_DATA.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BaseFormComponent.hpp"
#include "RE/S/SimpleArray.hpp"

namespace RE
{
	class FACTION_RANK;

	class __declspec(novtable) TESActorBaseData : public BaseFormComponent // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESActorBaseData;
		inline static constexpr const auto& VTABLE = VTABLE::TESActorBaseData;

		enum class ALIGNMENT : std::int32_t
		{
			Good = 0,
			Neutral = 1,
			Evil = 2,
			VeryGood = 3,
			VeryEvil = 4
		};

		~TESActorBaseData() override; // 0x00

		// override (BaseFormComponent)
		auto GetFormComponentType() const -> std::uint32_t override;			  // 0x01
		void InitializeDataComponent() override;								  // 0x02
		void ClearDataComponent() override;										  // 0x03
		void InitComponent() override;											  // 0x04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 0x05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 0x06

		// add
		virtual void CopyFromTemplateForms(TESActorBase** a_forceTemplates); // 0x07
		virtual auto GetIsGhost() const -> bool;							 // 0x08
		virtual auto GetInvulnerable() const -> bool;						 // 0x09

		[[nodiscard]]
		auto GetTemplates() noexcept -> std::span<TESForm*>;
		[[nodiscard]]
		auto GetTemplates() const noexcept -> std::span<TESForm* const>;
		void SetTemplates(std::span<TESForm*> a_templates);

		[[nodiscard]]
		auto GetTemplate(ACTOR_BASE_DATA::TEMPLATE_USE_FLAG a_flag) const -> TESForm*;
		void SetTemplate(ACTOR_BASE_DATA::TEMPLATE_USE_FLAG a_flag, TESForm* a_template);

		[[nodiscard]]
		auto GetLevel() const -> std::uint16_t
		{
			using FuncType = decltype(&TESActorBaseData::GetLevel);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESActorBaseData::GetLevel);
			return std::invoke(FUNC, this);
		}

		// members
		ACTOR_BASE_DATA actorData;			 // 0x08
		std::uint32_t changeFlags;			 // 0x1C
		TESLevItem* deathItem;				 // 0x20
		BGSVoiceType* voiceType;			 // 0x28
		TESForm* baseTemplateForm;			 // 0x30
		SimpleArray<TESForm*> templateForms; // 0x38
		TESGlobal* legendaryChance;			 // 0x40
		TESForm* legendaryTemplate;			 // 0x48
		BSTArray<FACTION_RANK> factions;	 // 0x50
	};

	static_assert(sizeof(TESActorBaseData) == 0x68);
}
