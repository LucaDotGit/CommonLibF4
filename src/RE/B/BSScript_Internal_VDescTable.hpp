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

		VDescTable(size_type a_paramCount, size_type a_localCount);
		~VDescTable() noexcept;

		VDescTable(const VDescTable& a_rhs);
		VDescTable(VDescTable&& a_rhs) noexcept;

		auto operator=(const VDescTable& a_rhs) -> VDescTable&;
		auto operator=(VDescTable&& a_rhs) noexcept -> VDescTable&;

		[[nodiscard]]
		auto GetParamCount() const noexcept -> size_type;
		[[nodiscard]]
		auto GetLocalCount() const noexcept -> size_type;
		[[nodiscard]]
		auto GetTotalEntryCount() const noexcept -> size_type;

		[[nodiscard]]
		auto GetNthParamPair(size_type a_index) const -> std::optional<value_type>;
		[[nodiscard]]
		auto GetNthLocalPair(size_type a_index) const -> std::optional<value_type>;
		[[nodiscard]]
		auto GetNthEntryPair(size_type a_index) const -> std::optional<value_type>;

		[[nodiscard]]
		auto GetNthParamName(size_type a_index) const -> std::optional<BSFixedString>;
		[[nodiscard]]
		auto GetNthLocalName(size_type a_index) const -> std::optional<BSFixedString>;
		[[nodiscard]]
		auto GetNthEntryName(size_type a_index) const -> std::optional<BSFixedString>;

		[[nodiscard]]
		auto GetNthParamType(size_type a_index) const -> std::optional<TypeInfo>;
		[[nodiscard]]
		auto GetNthLocalType(size_type a_index) const -> std::optional<TypeInfo>;
		[[nodiscard]]
		auto GetNthEntryType(size_type a_index) const -> std::optional<TypeInfo>;

		auto SetNthParamPair(size_type a_index, const value_type& a_pair) -> bool;
		auto SetNthLocalPair(size_type a_index, const value_type& a_pair) -> bool;
		auto SetNthEntryPair(size_type a_index, const value_type& a_pair) -> bool;

		auto SetNthParamName(size_type a_index, std::string_view a_name) -> bool;
		auto SetNthLocalName(size_type a_index, std::string_view a_name) -> bool;
		auto SetNthEntryName(size_type a_index, std::string_view a_name) -> bool;

		auto SetNthParamType(size_type a_index, const TypeInfo& a_type) -> bool;
		auto SetNthLocalType(size_type a_index, const TypeInfo& a_type) -> bool;
		auto SetNthEntryType(size_type a_index, const TypeInfo& a_type) -> bool;

	private:
		// members
		value_type* _entries{nullptr}; // 0x00
		size_type _paramCount{0};	   // 0x08
		size_type _totalEntryCount{0}; // 0x0A
	};

	static_assert(sizeof(VDescTable) == 0x10);
}
