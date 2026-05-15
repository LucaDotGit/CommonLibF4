#include "RE/B/BSScript_Internal_VDescTable.hpp"

namespace RE::BSScript::Internal
{
	VDescTable::VDescTable(size_type a_paramCount, size_type a_localCount)
		: _paramCount(a_paramCount),
		  _totalEntryCount(a_paramCount + a_localCount)
	{
		if (_totalEntryCount == 0) {
			return;
		}

		_entries = new value_type[_totalEntryCount];

		for (auto i = static_cast<size_type>(0); i < _paramCount; i++) {
			_entries[i].first = value_type::first_type(REX::Format("param{}"sv, i));
		}

		for (auto i = _paramCount; i < _totalEntryCount; i++) {
			_entries[i].first = value_type::first_type(REX::Format("local{}"sv, i - _paramCount));
		}
	}

	VDescTable::~VDescTable()
	{
		delete[] _entries;
	}

	VDescTable::VDescTable(const VDescTable& a_rhs)
		: _paramCount(a_rhs._paramCount),
		  _totalEntryCount(a_rhs._totalEntryCount)
	{
		if (_totalEntryCount == 0) {
			_entries = nullptr;
			return;
		}

		_entries = new value_type[_totalEntryCount];
		for (auto i = static_cast<size_type>(0); i < _totalEntryCount; i++) {
			_entries[i] = a_rhs._entries[i];
		}
	}

	VDescTable& VDescTable::operator=(const VDescTable& a_rhs)
	{
		if (this == std::addressof(a_rhs)) {
			return *this;
		}

		delete[] _entries;

		_paramCount = a_rhs._paramCount;
		_totalEntryCount = a_rhs._totalEntryCount;

		if (_totalEntryCount == 0) {
			_entries = nullptr;
			return *this;
		}

		_entries = new value_type[_totalEntryCount];
		for (auto i = static_cast<size_type>(0); i < _totalEntryCount; i++) {
			_entries[i] = a_rhs._entries[i];
		}

		return *this;
	}

	auto VDescTable::GetNthParamPair(size_type a_index) const
		-> std::optional<value_type>
	{
		if (a_index >= _paramCount) [[unlikely]] {
			REX::Assert(false);
			return std::nullopt;
		}

		REX::Assert(_entries != nullptr);
		return _entries[a_index];
	}

	auto VDescTable::GetNthLocalPair(size_type a_index) const
		-> std::optional<value_type>
	{
		if (a_index >= (_totalEntryCount - _paramCount)) [[unlikely]] {
			REX::Assert(false);
			return std::nullopt;
		}

		REX::Assert(_entries != nullptr);
		return _entries[_paramCount + a_index];
	}

	auto VDescTable::GetNthEntryPair(size_type a_index) const
		-> std::optional<value_type>
	{
		if (a_index >= _totalEntryCount) [[unlikely]] {
			REX::Assert(false);
			return std::nullopt;
		}

		REX::Assert(_entries != nullptr);
		return _entries[a_index];
	}

	auto VDescTable::GetNthParamName(size_type a_index) const
		-> std::optional<BSFixedString>
	{
		if (a_index >= _paramCount) [[unlikely]] {
			REX::Assert(false);
			return std::nullopt;
		}

		REX::Assert(_entries != nullptr);
		return _entries[a_index].first;
	}

	auto VDescTable::GetNthLocalName(size_type a_index) const
		-> std::optional<BSFixedString>
	{
		if (a_index >= (_totalEntryCount - _paramCount)) [[unlikely]] {
			REX::Assert(false);
			return std::nullopt;
		}

		REX::Assert(_entries != nullptr);
		return _entries[_paramCount + a_index].first;
	}

	auto VDescTable::GetNthEntryName(size_type a_index) const
		-> std::optional<BSFixedString>
	{
		if (a_index >= _totalEntryCount) [[unlikely]] {
			REX::Assert(false);
			return std::nullopt;
		}

		REX::Assert(_entries != nullptr);
		return _entries[a_index].first;
	}

	auto VDescTable::GetNthParamType(size_type a_index) const
		-> std::optional<TypeInfo>
	{
		if (a_index >= _paramCount) [[unlikely]] {
			REX::Assert(false);
			return std::nullopt;
		}

		REX::Assert(_entries != nullptr);
		return _entries[a_index].second;
	}

	auto VDescTable::GetNthLocalType(size_type a_index) const
		-> std::optional<TypeInfo>
	{
		if (a_index >= (_totalEntryCount - _paramCount)) [[unlikely]] {
			REX::Assert(false);
			return std::nullopt;
		}

		REX::Assert(_entries != nullptr);
		return _entries[_paramCount + a_index].second;
	}

	auto VDescTable::GetNthEntryType(size_type a_index) const
		-> std::optional<TypeInfo>
	{
		if (a_index >= _totalEntryCount) [[unlikely]] {
			REX::Assert(false);
			return std::nullopt;
		}

		REX::Assert(_entries != nullptr);
		return _entries[a_index].second;
	}

	// NOLINTBEGIN(readability-make-member-function-const)
	bool VDescTable::SetNthParamPair(size_type a_index, const value_type& a_pair)
	{
		if (a_index >= _paramCount) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		REX::Assert(_entries != nullptr);
		_entries[a_index] = a_pair;
		return true;
	}

	bool VDescTable::SetNthLocalPair(size_type a_index, const value_type& a_pair)
	{
		if (a_index >= (_totalEntryCount - _paramCount)) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		REX::Assert(_entries != nullptr);
		_entries[_paramCount + a_index] = a_pair;
		return true;
	}

	bool VDescTable::SetNthEntryPair(size_type a_index, const value_type& a_pair)
	{
		if (a_index >= _totalEntryCount) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		REX::Assert(_entries != nullptr);
		_entries[a_index] = a_pair;
		return true;
	}

	bool VDescTable::SetNthParamName(size_type a_index, std::string_view a_name)
	{
		if (a_index >= _paramCount) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		REX::Assert(_entries != nullptr);
		_entries[a_index].first = a_name;
		return true;
	}

	bool VDescTable::SetNthLocalName(size_type a_index, std::string_view a_name)
	{
		if (a_index >= (_totalEntryCount - _paramCount)) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		REX::Assert(_entries != nullptr);
		_entries[_paramCount + a_index].first = a_name;
		return true;
	}

	bool VDescTable::SetNthEntryName(size_type a_index, std::string_view a_name)
	{
		if (a_index >= _totalEntryCount) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		REX::Assert(_entries != nullptr);
		_entries[a_index].first = a_name;
		return true;
	}

	bool VDescTable::SetNthParamType(size_type a_index, const TypeInfo& a_type)
	{
		if (a_index >= _paramCount) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		REX::Assert(_entries != nullptr);
		_entries[a_index].second = a_type;
		return true;
	}

	bool VDescTable::SetNthLocalType(size_type a_index, const TypeInfo& a_type)
	{
		if (a_index >= (_totalEntryCount - _paramCount)) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		REX::Assert(_entries != nullptr);
		_entries[_paramCount + a_index].second = a_type;
		return true;
	}

	bool VDescTable::SetNthEntryType(size_type a_index, const TypeInfo& a_type)
	{
		if (a_index >= _totalEntryCount) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		REX::Assert(_entries != nullptr);
		_entries[a_index].second = a_type;
		return true;
	}
	// NOLINTEND(readability-make-member-function-const)
}
