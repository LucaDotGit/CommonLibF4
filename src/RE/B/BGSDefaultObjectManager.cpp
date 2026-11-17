#include "RE/B/BGSDefaultObjectManager.hpp"

namespace RE
{
	auto BGSDefaultObjectManager::GetDefaultObjects() noexcept -> std::span<TESForm*>
	{
		constexpr auto OBJECT_COUNT_NG = static_cast<std::size_t>(std::to_underlying(DEFAULT_OBJECT::_Count_NG));
		constexpr auto OBJECT_COUNT_OG = static_cast<std::size_t>(std::to_underlying(DEFAULT_OBJECT::_Count_OG));

		if (F4SE::IsRuntimeAtLeastNG()) {
			return std::span{objectArray.data(), OBJECT_COUNT_NG};
		}

		return std::span{objectArray.data(), OBJECT_COUNT_OG};
	}

	auto BGSDefaultObjectManager::GetDefaultObjects() const noexcept -> std::span<TESForm* const>
	{
		constexpr auto OBJECT_COUNT_NG = static_cast<std::size_t>(std::to_underlying(DEFAULT_OBJECT::_Count_NG));
		constexpr auto OBJECT_COUNT_OG = static_cast<std::size_t>(std::to_underlying(DEFAULT_OBJECT::_Count_OG));

		if (F4SE::IsRuntimeAtLeastNG()) {
			return std::span{objectArray.data(), OBJECT_COUNT_NG};
		}

		return std::span{objectArray.data(), OBJECT_COUNT_OG};
	}

	auto BGSDefaultObjectManager::GetDefaultObject(DEFAULT_OBJECT a_objectType) const noexcept -> TESForm*
	{
		REX::Assert(a_objectType < DEFAULT_OBJECT::_Count);
		return objectInitArray[REX::ToUnsigned(std::to_underlying(a_objectType))] ?
				   objectArray[REX::ToUnsigned(std::to_underlying(a_objectType))] :
				   nullptr;
	}
}
