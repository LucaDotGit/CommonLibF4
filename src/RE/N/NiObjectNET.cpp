#include "RE/N/NiObjectNET.hpp"

#include "RE/B/BSContainer_ForEachResult.hpp"
#include "RE/B/BSReadWriteLock.hpp"
#include "RE/N/NiExtraDataContainer.hpp"

namespace RE
{
	NiObjectNET::NiObjectNET()
	{
		REL::EmplaceVtable(this);
	}

	NiObjectNET::~NiObjectNET()
	{
		if (!extra) {
			return;
		}

		{
			const auto extraLock = BSAutoWriteLock(extra->lock);
			extra->dataArray.clear();
		}

		delete extra;
		extra = nullptr;
	}

	auto NiObjectNET::FormatExtraDataName(const NiExtraData& a_extraData, std::uint32_t a_extraDataSize)
		-> std::optional<BSFixedString>
	{
		const auto* extraType = a_extraData.GetRTTI();
		if (!extraType) [[unlikely]] {
			REX::Assert(false);
			return std::nullopt;
		}

		const auto* extraTypeName = extraType->GetName();
		if (REX::IsNullOrEmpty(extraTypeName)) [[unlikely]] {
			REX::Assert(false);
			return std::nullopt;
		}

		if (a_extraDataSize > 999) {
			return std::nullopt;
		}

		const auto extraPrefix = std::string_view(extraTypeName);
		const auto extraPrefixEndPos = extraPrefix.find("ExtraData"sv);
		const auto extraPrefixTrimmed = extraPrefix.substr(0, extraPrefixEndPos);

		if (REX::IsNullOrEmpty(extraPrefixTrimmed)) [[unlikely]] {
			REX::Assert(false);
			return std::nullopt;
		}

		auto extraBufferStorage = std::array<char, 0x100>();
		auto extraBufferRessource =
			std::pmr::monotonic_buffer_resource{extraBufferStorage.data(), extraBufferStorage.size()};
		auto extraBuffer = std::pmr::string(std::addressof(extraBufferRessource));

		extraBuffer.append(extraPrefixTrimmed);
		REX::FormatTo(std::back_inserter(extraBuffer), "ED{:03d}"sv, a_extraDataSize);

		return BSFixedString(extraBuffer);
	}

	auto NiObjectNET::HasExtraData(const BSFixedString& a_key) const noexcept -> bool
	{
		return GetExtraData(a_key) != nullptr;
	}

	auto NiObjectNET::GetExtraData(const BSFixedString& a_key) const noexcept -> NiPointer<NiExtraData>
	{
		if (!extra) {
			return nullptr;
		}

		const auto extraLock = BSAutoReadLock(extra->lock);

		for (const auto& extraData : extra->dataArray) {
			if (extraData && extraData->GetName() == a_key) {
				return extraData;
			}
		}

		return nullptr;
	}

	auto NiObjectNET::AddExtraData(NiPointer<NiExtraData> a_extraData) -> bool
	{
		if (!a_extraData) {
			return false;
		}

		if (a_extraData->GetName().empty()) {
			auto newExtraDataName = FormatExtraDataName(*a_extraData, extra ? extra->dataArray.size() : 0);
			if (!newExtraDataName.has_value()) {
				return false;
			}

			a_extraData->SetName(std::move(newExtraDataName).value());
		}

		return InsertExtraData(std::move(a_extraData));
	}

	auto NiObjectNET::InsertExtraData(NiPointer<NiExtraData> a_extraData) -> bool
	{
		if (!a_extraData) {
			return false;
		}

		if (!extra) {
			extra = new NiExtraDataContainer();
		}

		const auto extraLock = BSAutoWriteLock(extra->lock);

		extra->dataArray.push_back(std::move(a_extraData));
		return true;
	}

	auto NiObjectNET::RemoveExtraData(const BSFixedString& a_key) const -> bool
	{
		if (!extra) {
			return false;
		}

		const auto extraLock = BSAutoWriteLock(extra->lock);

		auto& extraDataArray = extra->dataArray;

		const auto* extraIt =
			std::ranges::find_if(extraDataArray, [&a_key](const NiPointer<NiExtraData>& a_extraData) noexcept -> bool {
				return a_extraData && a_extraData->GetName() == a_key;
			});

		if (extraIt == extraDataArray.end()) {
			return false;
		}

		extraDataArray.erase(extraIt);
		return true;
	}

	auto NiObjectNET::ForEachExtraData(
		const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(const NiPointer<NiExtraData>&) const>>&
			a_predicate) const -> BSContainer::ForEachResult
	{
		if (!extra) {
			return BSContainer::ForEachResult::Continue;
		}

		const auto extraLock = BSAutoReadLock(extra->lock);

		for (auto& extraData : extra->dataArray) {
			if (std::invoke(a_predicate.get(), extraData) == BSContainer::ForEachResult::Stop) {
				return BSContainer::ForEachResult::Stop;
			}
		}

		return BSContainer::ForEachResult::Continue;
	}
}
