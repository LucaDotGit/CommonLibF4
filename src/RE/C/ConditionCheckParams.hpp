#pragma once

namespace RE::BGSMod::Template
{
	class Item;
}

namespace RE
{
	class BGSPackageDataList;
	class BGSStoryEvent;

	class ConditionCheckParams
	{
	public:
		// members
		TESObjectREFR* actionRef{nullptr};					 // 0x00
		TESObjectREFR* targetRef{nullptr};					 // 0x08
		TESQuest* scopeQuest{nullptr};						 // 0x10
		BGSStoryEvent* scopeEvent{nullptr};					 // 0x18
		Actor* scopeActor{nullptr};							 // 0x20
		BGSPackageDataList* runningPackageData{nullptr};	 // 0x28
		BGSMod::Template::Item* objectTemplateItem{nullptr}; // 0x30
		std::array<const TESForm*, 5> extraForms{nullptr};	 // 0x38
		std::uint32_t extraFormCount{0};					 // 0x60
		bool outDispFailure{false};							 // 0x64
	};

	static_assert(sizeof(ConditionCheckParams) == 0x68);
}
