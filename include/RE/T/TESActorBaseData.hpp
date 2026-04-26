#pragma once

#include "RE/A/ACTOR_BASE_DATA.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BaseFormComponent.hpp"
#include "RE/S/SimpleArray.hpp"

namespace RE
{
	class FACTION_RANK;

	class __declspec(novtable) TESActorBaseData
		: public BaseFormComponent // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESActorBaseData };
		inline static constexpr auto VTABLE{ VTABLE::TESActorBaseData };

		enum class ALIGNMENT : std::int32_t
		{
			kGood = 0,
			kNeutral = 1,
			kEvil = 2,
			kVeryGood = 3,
			kVeryEvil = 4
		};

		~TESActorBaseData() override; // 00

		// override (BaseFormComponent)
		std::uint32_t GetFormComponentType() const override;					  // 01
		void InitializeDataComponent() override;								  // 02
		void ClearDataComponent() override;										  // 03
		void InitComponent() override;											  // 04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 06

		// add
		virtual void CopyFromTemplateForms(TESActorBase** a_forceTemplates); // 07
		virtual bool GetIsGhost() const;									 // 08
		virtual bool GetInvulnerable() const;								 // 09

		[[nodiscard]] std::span<TESForm*> GetTemplates() noexcept;
		[[nodiscard]] std::span<TESForm* const> GetTemplates() const noexcept;
		void SetTemplates(std::span<TESForm*> a_templates);

		[[nodiscard]] TESForm* GetTemplate(ACTOR_BASE_DATA::TEMPLATE_USE_FLAG a_flag) const;
		void SetTemplate(ACTOR_BASE_DATA::TEMPLATE_USE_FLAG a_flag, TESForm* a_template);

		[[nodiscard]] std::uint16_t GetLevel() const
		{
			using FuncType = decltype(&TESActorBaseData::GetLevel);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESActorBaseData::GetLevel };
			return std::invoke(FUNC, this);
		}

		// members
		ACTOR_BASE_DATA actorData;			 // 08
		std::uint32_t changeFlags;			 // 1C
		TESLevItem* deathItem;				 // 20
		BGSVoiceType* voiceType;			 // 28
		TESForm* baseTemplateForm;			 // 30
		SimpleArray<TESForm*> templateForms; // 38
		TESGlobal* legendaryChance;			 // 40
		TESForm* legendaryTemplate;			 // 48
		BSTArray<FACTION_RANK> factions;	 // 50
	};
	static_assert(sizeof(TESActorBaseData) == 0x68);
}
