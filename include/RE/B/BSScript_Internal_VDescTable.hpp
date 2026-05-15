#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSScript_TypeInfo.hpp"
#include "RE/B/BSTTuple.hpp"

namespace RE::BSScript::Internal
{
	class VDescTable
	{
	public:
		using value_type = BSTPair<BSFixedString, TypeInfo>;
		using size_type = std::uint16_t;
		using difference_type = std::int16_t;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;
		using iterator = value_type*;
		using const_iterator = const value_type*;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;

		VDescTable(size_type a_paramCount, size_type a_localCount);
		~VDescTable();

		VDescTable(const VDescTable& a_rhs);
		VDescTable(VDescTable&&) = delete;

		VDescTable& operator=(const VDescTable& a_rhs);
		VDescTable& operator=(VDescTable&&) = delete;

		[[nodiscard]] size_type GetParamCount() const noexcept { return _paramCount; }
		[[nodiscard]] size_type GetLocalCount() const noexcept { return _totalEntryCount - _paramCount; }
		[[nodiscard]] size_type GetTotalEntryCount() const noexcept { return _totalEntryCount; }

		[[nodiscard]] auto GetNthParamPair(size_type a_index) const
			-> std::optional<value_type>;
		[[nodiscard]] auto GetNthLocalPair(size_type a_index) const
			-> std::optional<value_type>;
		[[nodiscard]] auto GetNthEntryPair(size_type a_index) const
			-> std::optional<value_type>;

		[[nodiscard]] auto GetNthParamName(size_type a_index) const
			-> std::optional<BSFixedString>;
		[[nodiscard]] auto GetNthLocalName(size_type a_index) const
			-> std::optional<BSFixedString>;
		[[nodiscard]] auto GetNthEntryName(size_type a_index) const
			-> std::optional<BSFixedString>;

		[[nodiscard]] auto GetNthParamType(size_type a_index) const
			-> std::optional<TypeInfo>;
		[[nodiscard]] auto GetNthLocalType(size_type a_index) const
			-> std::optional<TypeInfo>;
		[[nodiscard]] auto GetNthEntryType(size_type a_index) const
			-> std::optional<TypeInfo>;

		bool SetNthParamPair(size_type a_index, const value_type& a_pair);
		bool SetNthLocalPair(size_type a_index, const value_type& a_pair);
		bool SetNthEntryPair(size_type a_index, const value_type& a_pair);

		bool SetNthParamName(size_type a_index, std::string_view a_name);
		bool SetNthLocalName(size_type a_index, std::string_view a_name);
		bool SetNthEntryName(size_type a_index, std::string_view a_name);

		bool SetNthParamType(size_type a_index, const TypeInfo& a_type);
		bool SetNthLocalType(size_type a_index, const TypeInfo& a_type);
		bool SetNthEntryType(size_type a_index, const TypeInfo& a_type);

	private:
		// members
		pointer _entries{ nullptr };	 // 00
		size_type _paramCount{ 0 };		 // 08
		size_type _totalEntryCount{ 0 }; // 0A
	};
	static_assert(sizeof(VDescTable) == 0x10);
}
