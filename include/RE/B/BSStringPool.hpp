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
			inline static constexpr auto SHALLOW_FLAG = 1ui32 << 14;
			inline static constexpr auto WIDE_FLAG = 1ui32 << 15;
			inline static constexpr auto REF_COUNT_MASK = 0x3FFFui32;

			Entry() noexcept = default;
			~Entry() noexcept = default;

			Entry(const Entry&) = delete;
			Entry(Entry&&) = delete;

			Entry& operator=(const Entry&) = delete;
			Entry& operator=(Entry&&) = delete;

			GAME_HEAP_REDEFINE_NEW(Entry);

			void Acquire() noexcept;
			static void Release(BSStringPool::Entry*& a_entry) noexcept;

			[[nodiscard]] bool shallow() const noexcept { return _flags & SHALLOW_FLAG; }
			[[nodiscard]] bool wide() const noexcept { return _flags & WIDE_FLAG; }
			[[nodiscard]] std::uint16_t ref_count() const noexcept { return _flags & REF_COUNT_MASK; }
			[[nodiscard]] std::uint16_t crc() const noexcept { return _crc; }

			template <class T>
			[[nodiscard]] const T* data() const noexcept;

			template <>
			[[nodiscard]] const char* data<char>() const noexcept;

			template <>
			[[nodiscard]] const wchar_t* data<wchar_t>() const noexcept;

			[[nodiscard]] const Entry* leaf() const noexcept;

			[[nodiscard]] std::uint32_t length() const noexcept;
			[[nodiscard]] std::uint32_t size() const noexcept;

		private:
			// members
			Entry* _left{ nullptr };			// 00
			volatile std::uint16_t _flags{ 0 }; // 08
			volatile std::uint16_t _crc{ 0 };	// 0A
			union
			{
				std::uint32_t _length;
				Entry* _right{ nullptr };
			}; // 10
		};
		static_assert(sizeof(Entry) == 0x18);
	};
	static_assert(std::is_empty_v<BSStringPool>);

	template <class T>
	bool FindEntry(BSStringPool::Entry*& a_outEntry, const T* a_string, std::uint16_t a_crc, bool a_caseSensitive);

	template <>
	bool FindEntry<char>(BSStringPool::Entry*& a_outEntry, const char* a_string, std::uint16_t a_crc, bool a_caseSensitive);

	template <>
	bool FindEntry<wchar_t>(BSStringPool::Entry*& a_outEntry, const wchar_t* a_string, std::uint16_t a_crc, bool a_caseSensitive);

	template <class T>
	void GetEntry(BSStringPool::Entry*& a_outEntry, const T* a_string, bool a_caseSensitive);

	template <>
	void GetEntry<char>(BSStringPool::Entry*& a_outEntry, const char* a_string, bool a_caseSensitive);

	template <>
	void GetEntry<wchar_t>(BSStringPool::Entry*& a_outEntry, const wchar_t* a_string, bool a_caseSensitive);
}
