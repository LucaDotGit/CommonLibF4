#include "RE/B/BSScript_Internal_VDescTable.hpp"

namespace RE::BSScript::Internal
{
	VDescTable::VDescTable(size_type a_paramCount, size_type a_localCount) :
		_paramCount(a_paramCount),
		_totalEntryCount(a_paramCount + a_localCount)
	{
		if (_totalEntryCount == 0) {
			return;
		}

		_entries = new value_type[_totalEntryCount];

		const auto getEntryName =
			// NOLINTNEXTLINE(cppcoreguidelines-missing-std-forward)
			[]<class... Args>(REX::FormatString<Args...> a_format, Args&&... a_args) -> BSFixedString
			requires((REX::formattable<Args, char> && ...))
		{
			auto formatStorage = std::array<char, 0x20>();
			auto formatRessource = std::pmr::monotonic_buffer_resource{formatStorage.data(), formatStorage.size()};
			auto formatBuffer = std::pmr::string(std::addressof(formatRessource));

			REX::FormatTo(std::back_inserter(formatBuffer), a_format, std::forward<Args>(a_args)...);
			return BSFixedString(formatBuffer);
		};

		for (auto i = static_cast<size_type>(0); i < _paramCount; i++) {
			_entries[i].first = getEntryName("param{}"sv, i);
		}

		for (auto i = _paramCount; i < _totalEntryCount; i++) {
			_entries[i].first = getEntryName("local{}"sv, i - _paramCount);
		}
	}

	VDescTable::~VDescTable() noexcept
	{
		delete[] _entries;
	}

	VDescTable::VDescTable(const VDescTable& a_rhs) :
		_paramCount(a_rhs._paramCount),
		_totalEntryCount(a_rhs._totalEntryCount)
	{
		if (_totalEntryCount == 0) {
			return;
		}

		_entries = new value_type[_totalEntryCount];
		std::copy(a_rhs._entries, a_rhs._entries + _totalEntryCount, _entries);
	}

	VDescTable::VDescTable(VDescTable&& a_rhs) noexcept :
		_entries(std::exchange(a_rhs._entries, nullptr)),
		_paramCount(std::exchange(a_rhs._paramCount, static_cast<size_type>(0))),
		_totalEntryCount(std::exchange(a_rhs._totalEntryCount, static_cast<size_type>(0)))
	{
	}

	auto VDescTable::operator=(const VDescTable& a_rhs) -> VDescTable&
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
		std::copy(a_rhs._entries, a_rhs._entries + _totalEntryCount, _entries);
		return *this;
	}

	auto VDescTable::operator=(VDescTable&& a_rhs) noexcept -> VDescTable&
	{
		if (this == std::addressof(a_rhs)) {
			return *this;
		}

		delete[] _entries;

		_entries = std::exchange(a_rhs._entries, nullptr);
		_paramCount = std::exchange(a_rhs._paramCount, static_cast<size_type>(0));
		_totalEntryCount = std::exchange(a_rhs._totalEntryCount, static_cast<size_type>(0));
		return *this;
	}

	auto VDescTable::GetParamCount() const noexcept -> VDescTable::size_type
	{
		return _paramCount;
	}

	auto VDescTable::GetLocalCount() const noexcept -> VDescTable::size_type
	{
		return _totalEntryCount - _paramCount;
	}

	auto VDescTable::GetTotalEntryCount() const noexcept -> VDescTable::size_type
	{
		return _totalEntryCount;
	}

	auto VDescTable::GetNthParamPair(size_type a_index) const -> std::optional<value_type>
	{
		if (a_index >= _paramCount) {
			return std::nullopt;
		}

		REX::Assert(_entries != nullptr);
		return _entries[a_index];
	}

	auto VDescTable::GetNthLocalPair(size_type a_index) const -> std::optional<value_type>
	{
		if (a_index >= (_totalEntryCount - _paramCount)) {
			return std::nullopt;
		}

		REX::Assert(_entries != nullptr);
		return _entries[_paramCount + a_index];
	}

	auto VDescTable::GetNthEntryPair(size_type a_index) const -> std::optional<value_type>
	{
		if (a_index >= _totalEntryCount) {
			return std::nullopt;
		}

		REX::Assert(_entries != nullptr);
		return _entries[a_index];
	}

	auto VDescTable::GetNthParamName(size_type a_index) const -> std::optional<BSFixedString>
	{
		if (a_index >= _paramCount) {
			return std::nullopt;
		}

		REX::Assert(_entries != nullptr);
		return _entries[a_index].first;
	}

	auto VDescTable::GetNthLocalName(size_type a_index) const -> std::optional<BSFixedString>
	{
		if (a_index >= (_totalEntryCount - _paramCount)) {
			return std::nullopt;
		}

		REX::Assert(_entries != nullptr);
		return _entries[_paramCount + a_index].first;
	}

	auto VDescTable::GetNthEntryName(size_type a_index) const -> std::optional<BSFixedString>
	{
		if (a_index >= _totalEntryCount) {
			return std::nullopt;
		}

		REX::Assert(_entries != nullptr);
		return _entries[a_index].first;
	}

	auto VDescTable::GetNthParamType(size_type a_index) const -> std::optional<TypeInfo>
	{
		if (a_index >= _paramCount) {
			return std::nullopt;
		}

		REX::Assert(_entries != nullptr);
		return _entries[a_index].second;
	}

	auto VDescTable::GetNthLocalType(size_type a_index) const -> std::optional<TypeInfo>
	{
		if (a_index >= (_totalEntryCount - _paramCount)) {
			return std::nullopt;
		}

		REX::Assert(_entries != nullptr);
		return _entries[_paramCount + a_index].second;
	}

	auto VDescTable::GetNthEntryType(size_type a_index) const -> std::optional<TypeInfo>
	{
		if (a_index >= _totalEntryCount) {
			return std::nullopt;
		}

		REX::Assert(_entries != nullptr);
		return _entries[a_index].second;
	}

	auto VDescTable::SetNthParamPair(size_type a_index, const value_type& a_pair) -> bool
	{
		if (a_index >= _paramCount) {
			return false;
		}

		REX::Assert(_entries != nullptr);
		_entries[a_index] = a_pair;
		return true;
	}

	auto VDescTable::SetNthLocalPair(size_type a_index, const value_type& a_pair) -> bool
	{
		if (a_index >= (_totalEntryCount - _paramCount)) {
			return false;
		}

		REX::Assert(_entries != nullptr);
		_entries[_paramCount + a_index] = a_pair;
		return true;
	}

	auto VDescTable::SetNthEntryPair(size_type a_index, const value_type& a_pair) -> bool
	{
		if (a_index >= _totalEntryCount) {
			return false;
		}

		REX::Assert(_entries != nullptr);
		_entries[a_index] = a_pair;
		return true;
	}

	auto VDescTable::SetNthParamName(size_type a_index, std::string_view a_name) -> bool
	{
		if (a_index >= _paramCount) {
			return false;
		}

		REX::Assert(_entries != nullptr);
		_entries[a_index].first = a_name;
		return true;
	}

	auto VDescTable::SetNthLocalName(size_type a_index, std::string_view a_name) -> bool
	{
		if (a_index >= (_totalEntryCount - _paramCount)) {
			return false;
		}

		REX::Assert(_entries != nullptr);
		_entries[_paramCount + a_index].first = a_name;
		return true;
	}

	auto VDescTable::SetNthEntryName(size_type a_index, std::string_view a_name) -> bool
	{
		if (a_index >= _totalEntryCount) {
			return false;
		}

		REX::Assert(_entries != nullptr);
		_entries[a_index].first = a_name;
		return true;
	}

	auto VDescTable::SetNthParamType(size_type a_index, const TypeInfo& a_type) -> bool
	{
		if (a_index >= _paramCount) {
			return false;
		}

		REX::Assert(_entries != nullptr);
		_entries[a_index].second = a_type;
		return true;
	}

	auto VDescTable::SetNthLocalType(size_type a_index, const TypeInfo& a_type) -> bool
	{
		if (a_index >= (_totalEntryCount - _paramCount)) {
			return false;
		}

		REX::Assert(_entries != nullptr);
		_entries[_paramCount + a_index].second = a_type;
		return true;
	}

	auto VDescTable::SetNthEntryType(size_type a_index, const TypeInfo& a_type) -> bool
	{
		if (a_index >= _totalEntryCount) {
			return false;
		}

		REX::Assert(_entries != nullptr);
		_entries[a_index].second = a_type;
		return true;
	}
}
