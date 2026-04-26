#include "RE/B/BGSObjectInstanceExtra.hpp"

#include "RE/B/BGSMod_ObjectIndexData.hpp"
#include "RE/T/TESBoundObject.hpp"

namespace RE
{
	BGSObjectInstanceExtra::BGSObjectInstanceExtra()
		: BSExtraData(EXTRA_TYPE)
	{
		REL::EmplaceVtable(this);
	}

	BGSObjectInstanceExtra::BGSObjectInstanceExtra(const BGSMod::Template::Item* a_item, TESForm* a_parentForm, const INSTANCE_FILTER* a_filter)
	{
		using FuncType = void (BGSObjectInstanceExtra::*)(const BGSMod::Template::Item*, TESForm*, const INSTANCE_FILTER*);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSObjectInstanceExtra::ctor };
		FUNC(this, a_item, a_parentForm, a_filter);
	}

	void BGSObjectInstanceExtra::AddMod(const BGSMod::Attachment::Mod& a_newMod, std::uint8_t a_attachIndex, std::uint8_t a_rank, bool a_removeInvalidMods)
	{
		using FuncType = decltype(&BGSObjectInstanceExtra::AddMod);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSObjectInstanceExtra::AddMod };
		FUNC(this, a_newMod, a_attachIndex, a_rank, a_removeInvalidMods);
	}

	bool BGSObjectInstanceExtra::AttachModToReference(TESObjectREFR& a_ref, BGSMod::Attachment::Mod& a_mod, std::uint8_t a_attachIndex, std::uint8_t a_rank)
	{
		using FuncType = decltype(&BGSObjectInstanceExtra::AttachModToReference);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSObjectInstanceExtra::AttachModToReference };
		return std::invoke(FUNC, a_ref, a_mod, a_attachIndex, a_rank);
	}

	void BGSObjectInstanceExtra::CreateBaseInstanceData(const TESBoundObject& a_object, BSTSmartPointer<TBO_InstanceData>& a_instanceData) const
	{
		if (values && itemIndex != std::numeric_limits<std::uint16_t>::max()) {
			a_object.ApplyMods(a_instanceData, this);
		}
	}

	std::uint32_t BGSObjectInstanceExtra::GetNumMods(bool a_ignoreCollections) const
	{
		using FuncType = decltype(&BGSObjectInstanceExtra::GetNumMods);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSObjectInstanceExtra::GetNumMods };
		return std::invoke(FUNC, this, a_ignoreCollections);
	}

	std::span<BGSMod::ObjectIndexData> BGSObjectInstanceExtra::GetIndexData() const noexcept
	{
		return values->get_buffer<BGSMod::ObjectIndexData>(0);
	}

	bool BGSObjectInstanceExtra::HasMod(const BGSMod::Attachment::Mod& a_mod) const
	{
		using FuncType = decltype(&BGSObjectInstanceExtra::HasMod);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSObjectInstanceExtra::HasMod };
		return std::invoke(FUNC, this, a_mod);
	}

	std::uint32_t BGSObjectInstanceExtra::RemoveInvalidMods(const BGSAttachParentArray* a_baseObjectParents)
	{
		using FuncType = decltype(&BGSObjectInstanceExtra::RemoveInvalidMods);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSObjectInstanceExtra::RemoveInvalidMods };
		return std::invoke(FUNC, this, a_baseObjectParents);
	}

	std::uint32_t BGSObjectInstanceExtra::RemoveMod(const BGSMod::Attachment::Mod* a_mod, std::uint8_t a_attachIndex)
	{
		using FuncType = decltype(&BGSObjectInstanceExtra::RemoveMod);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSObjectInstanceExtra::RemoveMod };
		return std::invoke(FUNC, this, a_mod, a_attachIndex);
	}
}
