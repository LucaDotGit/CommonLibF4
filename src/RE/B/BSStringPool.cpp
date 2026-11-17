#include "RE/B/BSStringPool.hpp"

namespace RE
{
	void BSStringPool::Entry::Acquire() noexcept
	{
		const auto atomicFlags = REX::AtomicRef(_flags);
		auto expectedFlags = static_cast<std::uint16_t>(0);

		do {
			expectedFlags = atomicFlags.load(std::memory_order_acquire);
			if ((expectedFlags & REF_COUNT_MASK) >= REF_COUNT_MASK) {
				break;
			}
		}
		while (!atomicFlags.compare_exchange_weak(
			expectedFlags,
			expectedFlags + 1,
			std::memory_order_acq_rel,
			std::memory_order_relaxed));
	}

	void BSStringPool::Entry::Release(BSStringPool::Entry*& a_entry) noexcept
	{
		try {
			using FuncType = decltype(&BSStringPool::Entry::Release);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSStringPool::Entry::Release);
			std::invoke(FUNC, a_entry);
		}
		catch (...) {
			REX::Fail("Failed to release object."sv);
		}
	}

	template <>
	auto BSStringPool::Entry::data<char>() const noexcept -> const char*
	{
		const auto* entry = leaf();
		if (!entry) {
			return nullptr;
		}

		REX::Assert(!entry->wide());
		return reinterpret_cast<const char*>(entry + 1);
	}

	template <>
	auto BSStringPool::Entry::data<wchar_t>() const noexcept -> const wchar_t*
	{
		const auto* entry = leaf();
		if (!entry) {
			return nullptr;
		}

		REX::Assert(entry->wide());
		return reinterpret_cast<const wchar_t*>(entry + 1);
	}

	auto BSStringPool::Entry::leaf() const noexcept -> const BSStringPool::Entry*
	{
		const auto* it = this;
		while (it && it->shallow()) {
			it = it->_self.right;
		}

		return it;
	}

	auto BSStringPool::Entry::length() const noexcept -> std::uint32_t
	{
		const auto* entry = leaf();
		return entry ? entry->_self.length : 0;
	}

	auto BSStringPool::Entry::size() const noexcept -> std::uint32_t
	{
		return length();
	}

	template <>
	auto FindEntry<char>(
		BSStringPool::Entry*& a_outEntry,
		const char* a_string,
		std::uint16_t a_crc,
		bool a_caseSensitive) -> bool
	{
		using FuncType = decltype(&RE::FindEntry<char>);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BSStringPool::FindEntry_char);
		return std::invoke(FUNC, a_outEntry, a_string, a_crc, a_caseSensitive);
	}

	template <>
	auto FindEntry<wchar_t>(
		BSStringPool::Entry*& a_outEntry,
		const wchar_t* a_string,
		std::uint16_t a_crc,
		bool a_caseSensitive) -> bool
	{
		using FuncType = decltype(&RE::FindEntry<wchar_t>);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BSStringPool::FindEntry_wchar);
		return std::invoke(FUNC, a_outEntry, a_string, a_crc, a_caseSensitive);
	}

	template <>
	void GetEntry<char>(BSStringPool::Entry*& a_outEntry, const char* a_string, bool a_caseSensitive)
	{
		using FuncType = decltype(&RE::GetEntry<char>);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BSStringPool::GetEntry_char);
		std::invoke(FUNC, a_outEntry, a_string, a_caseSensitive);
	}

	template <>
	void GetEntry<wchar_t>(BSStringPool::Entry*& a_outEntry, const wchar_t* a_string, bool a_caseSensitive)
	{
		using FuncType = decltype(&RE::GetEntry<wchar_t>);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BSStringPool::GetEntry_wchar);
		std::invoke(FUNC, a_outEntry, a_string, a_caseSensitive);
	}
}
