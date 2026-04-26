#include "RE/B/BSStringPool.hpp"

namespace RE
{
	void BSStringPool::Entry::Acquire() noexcept
	{
		auto atomicFlags = REX::AtomicRef(_flags);
		auto expectedFlags = 0ui16;

		do {
			expectedFlags = atomicFlags.load(std::memory_order_acquire);
			if ((expectedFlags & REF_COUNT_MASK) >= REF_COUNT_MASK) {
				break;
			}
		}
		while (!atomicFlags.compare_exchange_weak(expectedFlags, expectedFlags + 1,
			std::memory_order_acq_rel, std::memory_order_relaxed));
	}

	void BSStringPool::Entry::Release(BSStringPool::Entry*& a_entry) noexcept
	{
		try {
			using FuncType = decltype(&BSStringPool::Entry::Release);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BSStringPool::Entry::Release };
			FUNC(a_entry);
		}
		catch (...) {
			REX::QuickFail("Failed to release string pool entry."sv);
		}
	}

	template <>
	const char* BSStringPool::Entry::data<char>() const noexcept
	{
		const auto* entry = leaf();
		if (!entry) {
			return nullptr;
		}

		REX::Assert(!entry->wide());
		return reinterpret_cast<const char*>(entry + 1);
	}

	template <>
	const wchar_t* BSStringPool::Entry::data<wchar_t>() const noexcept
	{
		const auto* entry = leaf();
		if (!entry) {
			return nullptr;
		}

		REX::Assert(entry->wide());
		return reinterpret_cast<const wchar_t*>(entry + 1);
	}

	const BSStringPool::Entry* BSStringPool::Entry::leaf() const noexcept
	{
		const auto* it = this;
		while (it && it->shallow()) {
			it = it->_right;
		}

		return it;
	}

	std::uint32_t BSStringPool::Entry::length() const noexcept
	{
		const auto* entry = leaf();
		return entry ? entry->_length : 0;
	}

	std::uint32_t BSStringPool::Entry::size() const noexcept
	{
		return length();
	}

	template <>
	bool FindEntry<char>(BSStringPool::Entry*& a_outEntry, const char* a_string, std::uint16_t a_crc, bool a_caseSensitive)
	{
		using FuncType = decltype(&RE::FindEntry<char>);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BSStringPool::FindEntry_char };
		return std::invoke(FUNC, a_outEntry, a_string, a_crc, a_caseSensitive);
	}

	template <>
	bool FindEntry<wchar_t>(BSStringPool::Entry*& a_outEntry, const wchar_t* a_string, std::uint16_t a_crc, bool a_caseSensitive)
	{
		using FuncType = decltype(&RE::FindEntry<wchar_t>);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BSStringPool::FindEntry_wchar };
		return std::invoke(FUNC, a_outEntry, a_string, a_crc, a_caseSensitive);
	}

	template <>
	void GetEntry<char>(BSStringPool::Entry*& a_outEntry, const char* a_string, bool a_caseSensitive)
	{
		using FuncType = decltype(&RE::GetEntry<char>);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BSStringPool::GetEntry_char };
		FUNC(a_outEntry, a_string, a_caseSensitive);
	}

	template <>
	void GetEntry<wchar_t>(BSStringPool::Entry*& a_outEntry, const wchar_t* a_string, bool a_caseSensitive)
	{
		using FuncType = decltype(&RE::GetEntry<wchar_t>);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BSStringPool::GetEntry_wchar };
		FUNC(a_outEntry, a_string, a_caseSensitive);
	}
}
