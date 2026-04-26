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
		TESObjectREFR* actionRef{ nullptr };				   // 00
		TESObjectREFR* targetRef{ nullptr };				   // 08
		TESQuest* scopeQuest{ nullptr };					   // 10
		BGSStoryEvent* scopeEvent{ nullptr };				   // 18
		Actor* scopeActor{ nullptr };						   // 20
		BGSPackageDataList* runningPackageData{ nullptr };	   // 28
		BGSMod::Template::Item* objectTemplateItem{ nullptr }; // 30
		std::array<const TESForm*, 5> extraForms{ nullptr };   // 38
		std::uint32_t extraFormCount{ 0 };					   // 60
		bool outDispFailure{ false };						   // 64
	};
	static_assert(sizeof(ConditionCheckParams) == 0x68);
}
