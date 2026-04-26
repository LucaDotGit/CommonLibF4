#include "RE/B/BaseExtraList.hpp"

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	bool BaseExtraList::HasExtra(EXTRA_DATA_TYPE a_type) const noexcept
	{
		REX::Assert(a_type < EXTRA_DATA_TYPE::kTotal);
		const auto index = std::to_underlying(a_type) / 8;
		const auto flags = GetFlags();

		if (flags.empty() || std::cmp_greater_equal(index, flags.size())) {
			return false;
		}

		const auto pos = static_cast<std::uint8_t>(1 << (std::to_underlying(a_type) % 8));
		return (flags[index] & pos) != 0;
	}

	BSExtraData* BaseExtraList::GetExtra(EXTRA_DATA_TYPE a_type) const noexcept
	{
		if (!HasExtra(a_type)) {
			return nullptr;
		}

		for (auto* it = _head; it; it = it->next) {
			if (it->GetExtraType() == a_type) {
				return it;
			}
		}

		return nullptr;
	}

	void BaseExtraList::AddExtra(BSExtraData* a_extra) noexcept
	{
		REX::Assert(a_extra != nullptr);
		REX::Assert(a_extra->next == nullptr);

		const auto type = a_extra->GetExtraType();
		REX::Assert(!HasExtra(type));

		if (!_head || !IsHighUseExtra(type)) {
			REX::Assert(_tail != nullptr);
			*_tail = a_extra;
			_tail = std::addressof(a_extra->next);
		}
		else {
			a_extra->next = _head;
			_head = a_extra;
		}

		MarkType(type, true);
	}

	std::unique_ptr<BSExtraData> BaseExtraList::RemoveExtra(EXTRA_DATA_TYPE a_type) noexcept
	{
		if (!HasExtra(a_type)) {
			return nullptr;
		}

		auto* prev = static_cast<BSExtraData*>(nullptr);

		for (auto* it = _head; it; prev = it, it = it->next) {
			if (it->GetExtraType() == a_type) {
				if (prev) {
					prev->next = it->next;
				}
				else {
					_head = it->next;
				}

				if (!_tail || *_tail == it) {
					_tail = std::addressof(prev ? prev->next : _head);
				}

				MarkType(a_type, false);
				return std::unique_ptr<BSExtraData>{ it };
			}
		}

		return nullptr;
	}

	bool BaseExtraList::IsHighUseExtra(EXTRA_DATA_TYPE a_type) noexcept
	{
		return !((std::to_underlying(a_type) - 11) & ~0x22u) && a_type != EXTRA_DATA_TYPE::kLeveledCreature;
	}

	std::span<std::uint8_t> BaseExtraList::GetFlags() const noexcept
	{
		if (!_flags) {
			return {};
		}

		return { _flags, N };
	}

	std::span<std::uint8_t, BaseExtraList::N> BaseExtraList::GetOrCreateFlags() noexcept
	{
		if (!_flags) {
			CreateFlags();
		}

		return std::span{ reinterpret_cast<std::array<std::uint8_t, N>&>(*_flags) };
	}

	void BaseExtraList::CreateFlags() noexcept
	{
		_flags = calloc<std::uint8_t>(N);
	}

	void BaseExtraList::MarkType(EXTRA_DATA_TYPE a_type, bool a_set) noexcept
	{
		REX::Assert(a_type < EXTRA_DATA_TYPE::kTotal);

		const auto index = std::to_underlying(a_type) / 8;
		const auto pos = static_cast<std::uint8_t>(1 << (std::to_underlying(a_type) % 8));
		const auto flags = GetOrCreateFlags();

		if (a_set) {
			flags[index] |= pos;
		}
		else {
			flags[index] &= ~pos;
		}
	}
}
