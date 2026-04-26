#include "RE/B/BGSCreatedObjectManager.hpp"

#include "RE/A/AlchemyItem.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	template class BGSCreatedObjectManager::BSTCreatedObjectSmartPointerPolicy<AlchemyItem>;
	static_assert(std::is_empty_v<BGSCreatedObjectManager::BSTCreatedObjectSmartPointerPolicy<AlchemyItem>>);

	template class BGSCreatedObjectManager::BSTCreatedObjectSmartPointerPolicy<TESForm>;
	static_assert(std::is_empty_v<BGSCreatedObjectManager::BSTCreatedObjectSmartPointerPolicy<TESForm>>);
}
