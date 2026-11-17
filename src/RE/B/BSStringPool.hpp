#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class BSStringPool
	{
	public:
		class Entry
		{
		public:
			inline static constexpr auto SHALLOW_FLAG = static_cast<std::uint32_t>(1) << 14;
			inline static constexpr auto WIDE_FLAG = static_cast<std::uint32_t>(1) << 15;
			inline static constexpr auto REF_COUNT_MASK = static_cast<std::uint32_t>(0x3FFF);

			Entry() noexcept = default;
			~Entry() noexcept = default;

			Entry(const Entry&) = delete;
			Entry(Entry&&) = delete;

			auto operator=(const Entry&) -> Entry& = delete;
			auto operator=(Entry&&) -> Entry& = delete;

			GAME_HEAP_REDEFINE_NEW(Entry);

			void Acquire() noexcept;
			static void Release(BSStringPool::Entry*& a_entry) noexcept;

			[[nodiscard]]
			auto shallow() const noexcept -> bool
			{
				return _flags & SHALLOW_FLAG;
			}

			[[nodiscard]]
			auto wide() const noexcept -> bool
			{
				return _flags & WIDE_FLAG;
			}

			[[nodiscard]]
			auto ref_count() const noexcept -> std::uint16_t
			{
				return _flags & REF_COUNT_MASK;
			}

			[[nodiscard]]
			auto crc() const noexcept -> std::uint16_t
			{
				return _crc;
			}

			template <class T>
			[[nodiscard]]
			auto data() const noexcept -> const T*;

			template <>
			[[nodiscard]]
			auto data<char>() const noexcept -> const char*;

			template <>
			[[nodiscard]]
			auto data<wchar_t>() const noexcept -> const wchar_t*;

			[[nodiscard]]
			auto leaf() const noexcept -> const Entry*;

			[[nodiscard]]
			auto length() const noexcept -> std::uint32_t;
			[[nodiscard]]
			auto size() const noexcept -> std::uint32_t;

		private:
			// members
			Entry* _left{nullptr};			  // 0x00
			volatile std::uint16_t _flags{0}; // 0x08
			volatile std::uint16_t _crc{0};	  // 0x0A

			union
			{
			public:
				std::uint32_t length;
				Entry* right{nullptr};
			} _self; // 0x10
		};

		static_assert(sizeof(Entry) == 0x18);
	};

	static_assert(std::is_empty_v<BSStringPool>);

	template <REX::win32_character T>
	auto FindEntry(BSStringPool::Entry*& a_outEntry, const T* a_string, std::uint16_t a_crc, bool a_caseSensitive)
		-> bool;

	template <>
	auto FindEntry<char>(
		BSStringPool::Entry*& a_outEntry,
		const char* a_string,
		std::uint16_t a_crc,
		bool a_caseSensitive) -> bool;

	template <>
	auto FindEntry<wchar_t>(
		BSStringPool::Entry*& a_outEntry,
		const wchar_t* a_string,
		std::uint16_t a_crc,
		bool a_caseSensitive) -> bool;

	template <REX::win32_character T>
	void GetEntry(BSStringPool::Entry*& a_outEntry, const T* a_string, bool a_caseSensitive);

	template <>
	void GetEntry<char>(BSStringPool::Entry*& a_outEntry, const char* a_string, bool a_caseSensitive);

	template <>
	void GetEntry<wchar_t>(BSStringPool::Entry*& a_outEntry, const wchar_t* a_string, bool a_caseSensitive);
}
