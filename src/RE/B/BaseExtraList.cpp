#include "RE/B/BaseExtraList.hpp"

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	auto BaseExtraList::HasExtra(EXTRA_DATA_TYPE a_extraType) const noexcept -> bool
	{
		REX::Assert(a_extraType >= EXTRA_DATA_TYPE::_Min && a_extraType <= EXTRA_DATA_TYPE::_Max);

		const auto index = static_cast<std::uint8_t>(std::to_underlying(a_extraType) / 8);
		const auto flags = GetFlags();

		if (flags.empty() || std::cmp_greater_equal(index, flags.size())) {
			return false;
		}

		const auto position = static_cast<std::uint8_t>(1 << (std::to_underlying(a_extraType) % 8));
		return (flags[index] & position) != 0;
	}

	auto BaseExtraList::GetExtra(EXTRA_DATA_TYPE a_extraType) const noexcept -> BSExtraData*
	{
		if (!HasExtra(a_extraType)) {
			return nullptr;
		}

		for (auto* it = _head; it; it = it->next) {
			if (it->GetExtraType() == a_extraType) {
				return it;
			}
		}

		return nullptr;
	}

	auto BaseExtraList::AddExtra(std::unique_ptr<BSExtraData> a_extraData) noexcept -> BSExtraData*
	{
		REX::Assert(a_extraData != nullptr);
		REX::Assert(a_extraData->next == nullptr);

		const auto extraType = a_extraData->GetExtraType();
		REX::Assert(!HasExtra(extraType));

		auto* newExtraData = a_extraData.release();

		if (!_head || !IsHighUseExtra(extraType)) {
			REX::Assert(_tail != nullptr);

			*_tail = newExtraData;
			_tail = std::addressof(newExtraData->next);
		}
		else {
			newExtraData->next = _head;
			_head = newExtraData;
		}

		MarkType(extraType, true);
		return newExtraData;
	}

	auto BaseExtraList::RemoveExtra(EXTRA_DATA_TYPE a_extraType) noexcept -> std::unique_ptr<BSExtraData>
	{
		if (!HasExtra(a_extraType)) {
			return nullptr;
		}

		auto* prev = static_cast<BSExtraData*>(nullptr);

		for (auto* it = _head; it; prev = it, it = it->next) {
			if (it->GetExtraType() == a_extraType) {
				if (prev) {
					prev->next = it->next;
				}
				else {
					_head = it->next;
				}

				if (!_tail || *_tail == it) {
					_tail = std::addressof(prev ? prev->next : _head);
				}

				MarkType(a_extraType, false);
				return std::unique_ptr<BSExtraData>(it);
			}
		}

		return nullptr;
	}

	auto BaseExtraList::IsHighUseExtra(EXTRA_DATA_TYPE a_extraType) noexcept -> bool
	{
		if (a_extraType == EXTRA_DATA_TYPE::LeveledCreature) {
			return false;
		}

		return ((REX::ToUnsigned(std::to_underlying(a_extraType)) - 11) & ~0x22u) == 0;
	}

	auto BaseExtraList::GetFlags() const noexcept -> std::span<std::uint8_t>
	{
		if (!_flags) {
			return {};
		}

		return {_flags, N};
	}

	auto BaseExtraList::GetOrCreateFlags() noexcept -> std::span<std::uint8_t, BaseExtraList::N>
	{
		if (!_flags) {
			CreateFlags();
		}

		return std::span{reinterpret_cast<std::span<std::uint8_t, N>&>(*_flags)};
	}

	void BaseExtraList::CreateFlags() noexcept
	{
		_flags = calloc<std::uint8_t>(N);
	}

	void BaseExtraList::MarkType(EXTRA_DATA_TYPE a_extraType, bool a_set) noexcept
	{
		REX::Assert(a_extraType >= EXTRA_DATA_TYPE::_Min && a_extraType <= EXTRA_DATA_TYPE::_Max);

		const auto index = static_cast<std::uint8_t>(std::to_underlying(a_extraType) / 8);
		const auto position = static_cast<std::uint8_t>(1 << (std::to_underlying(a_extraType) % 8));
		const auto flags = GetOrCreateFlags();

		if (a_set) {
			flags[index] |= position;
		}
		else {
			flags[index] &= ~position;
		}
	}
}
