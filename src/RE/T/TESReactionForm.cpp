#include "RE/T/TESReactionForm.hpp"

#include "RE/G/GROUP_REACTION.hpp"
#include "RE/T/TESFaction.hpp"

namespace RE
{
	void TESReactionForm::SetReactions(std::span<std::unique_ptr<GROUP_REACTION>> a_reactions)
	{
		ClearReactions();

		for (auto& reaction : a_reactions) {
			if (!reaction) {
				continue;
			}

			reactionList.push_back(reaction.release());
		}

		AddReactionChange();
	}

	void TESReactionForm::ClearReactions()
	{
		for (auto*& reaction : reactionList) {
			if (!reaction) {
				continue;
			}

			delete reaction;
			reaction = nullptr;
		}

		reactionList.clear();
	}

	bool TESReactionForm::AddReactionChange()
	{
		auto* faction = DynamicCast<TESFaction*>(this);
		if (!faction) {
			return false;
		}

		faction->AddChange(TESFaction::ChangeFlags::kReactions);
		return true;
	}
}
