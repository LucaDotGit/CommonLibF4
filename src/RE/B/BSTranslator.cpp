#include "RE/B/BSTranslator.hpp"

#include "RE/B/BSScaleformTranslator.hpp"

namespace RE
{
	auto BSTranslator::Contains(std::string_view a_key) const -> bool
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(a_key)) {
			return false;
		}

		const auto u16Key = REX::Utf8ToUtf16(a_key);
		if (!u16Key.has_value()) {
			return false;
		}

		return Contains(u16Key.value());
	}

	auto BSTranslator::Contains(std::wstring_view a_key) const -> bool
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(a_key)) {
			return false;
		}

		return Contains(RE::BSFixedStringWCS(a_key));
	}

	auto BSTranslator::Contains(const RE::BSFixedStringCS& a_key) const -> bool
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(std::string_view(a_key))) {
			return false;
		}

		const auto u16Key = REX::Utf8ToUtf16(a_key);
		if (!u16Key.has_value()) {
			return false;
		}

		return Contains(u16Key.value());
	}

	auto BSTranslator::Contains(const RE::BSFixedStringWCS& a_key) const noexcept -> bool
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(std::wstring_view(a_key))) {
			return false;
		}

		return translationMap.contains(a_key);
	}

	auto BSTranslator::GetValue(std::string_view a_key) const -> std::expected<std::string, REX::SystemError>
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(a_key)) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		const auto u16Key = REX::Utf8ToUtf16(a_key);
		if (!u16Key.has_value()) [[unlikely]] {
			return std::unexpected(u16Key.error());
		}

		const auto u16Value = GetValue(u16Key.value());
		if (!u16Value) [[unlikely]] {
			return std::unexpected(u16Value.error());
		}

		auto u8Value = REX::Utf16ToUtf8(u16Value.value());
		if (!u8Value) [[unlikely]] {
			return std::unexpected(u8Value.error());
		}

		return std::move(u8Value).value();
	}

	auto BSTranslator::GetValue(std::wstring_view a_key) const -> std::expected<std::wstring, REX::SystemError>
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(a_key)) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		const auto value = GetValue(RE::BSFixedStringWCS(a_key));
		if (!value.has_value()) [[unlikely]] {
			return std::unexpected(value.error());
		}

		return std::wstring(value.value());
	}

	auto BSTranslator::GetValue(const RE::BSFixedStringCS& a_key) const
		-> std::expected<RE::BSFixedStringCS, REX::SystemError>
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(std::string_view(a_key))) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		const auto u16Key = REX::Utf8ToUtf16(a_key);
		if (!u16Key.has_value()) [[unlikely]] {
			return std::unexpected(u16Key.error());
		}

		const auto u16Value = GetValue(u16Key.value());
		if (!u16Value.has_value()) [[unlikely]] {
			return std::unexpected(u16Value.error());
		}

		auto u8Value = REX::Utf16ToUtf8(u16Value.value());
		if (!u8Value.has_value()) [[unlikely]] {
			return std::unexpected(u8Value.error());
		}

		return RE::BSFixedStringCS(u8Value.value());
	}

	auto BSTranslator::GetValue(const RE::BSFixedStringWCS& a_key) const noexcept
		-> std::expected<RE::BSFixedStringWCS, REX::SystemError>
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(std::wstring_view(a_key))) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		const auto keyIt = translationMap.find(a_key);
		if (keyIt == translationMap.end()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		return keyIt->second;
	}

	auto BSTranslator::SetValue(std::string_view a_key, std::string_view a_value) -> bool
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(a_key)) {
			return false;
		}

		const auto u16Key = REX::Utf8ToUtf16(a_key);
		if (!u16Key.has_value()) {
			return false;
		}

		const auto u16Value = REX::Utf8ToUtf16(a_value);
		if (!u16Value.has_value()) {
			return false;
		}

		return SetValue(u16Key.value(), u16Value.value());
	}

	auto BSTranslator::SetValue(std::wstring_view a_key, std::wstring_view a_value) -> bool
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(a_key)) {
			return false;
		}

		return SetValue(RE::BSFixedStringWCS(a_key), RE::BSFixedStringWCS(a_value));
	}

	auto BSTranslator::SetValue(const RE::BSFixedStringCS& a_key, const RE::BSFixedStringCS& a_value) -> bool
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(std::string_view(a_key))) {
			return false;
		}

		const auto u16Key = REX::Utf8ToUtf16(a_key);
		if (!u16Key.has_value()) {
			return false;
		}

		const auto u16Value = REX::Utf8ToUtf16(a_value);
		if (!u16Value.has_value()) {
			return false;
		}

		return SetValue(u16Key.value(), u16Value.value());
	}

	auto BSTranslator::SetValue(const RE::BSFixedStringWCS& a_key, const RE::BSFixedStringWCS& a_value) -> bool
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(std::wstring_view(a_key))) {
			return false;
		}

		translationMap.insert_or_assign(a_key, a_value);
		return true;
	}

	void BSTranslator::SetRange(std::span<const std::pair<std::string_view, std::string_view>> a_pairs)
	{
		ReserveAdditional(static_cast<size_type>(a_pairs.size()));

		for (auto&& [key, value] : a_pairs) {
			SetValue(key, value);
		}
	}

	void BSTranslator::SetRange(std::span<const std::pair<std::wstring_view, std::wstring_view>> a_pairs)
	{
		ReserveAdditional(static_cast<size_type>(a_pairs.size()));

		for (auto&& [key, value] : a_pairs) {
			SetValue(key, value);
		}
	}

	void BSTranslator::SetRange(std::span<const std::pair<RE::BSFixedStringCS, RE::BSFixedStringCS>> a_pairs)
	{
		ReserveAdditional(static_cast<size_type>(a_pairs.size()));

		for (auto&& [key, value] : a_pairs) {
			SetValue(key, value);
		}
	}

	void BSTranslator::SetRange(std::span<const std::pair<RE::BSFixedStringWCS, RE::BSFixedStringWCS>> a_pairs)
	{
		ReserveAdditional(static_cast<size_type>(a_pairs.size()));

		for (auto&& [key, value] : a_pairs) {
			SetValue(key, value);
		}
	}

	auto BSTranslator::GetOrAdd(std::string_view a_key, std::string_view a_value)
		-> std::expected<std::string, REX::SystemError>
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(a_key)) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		const auto u16Key = REX::Utf8ToUtf16(a_key);
		if (!u16Key.has_value()) [[unlikely]] {
			return std::unexpected(u16Key.error());
		}

		const auto u16Value = REX::Utf8ToUtf16(a_value);
		if (!u16Value.has_value()) [[unlikely]] {
			return std::unexpected(u16Value.error());
		}

		const auto u16Result = GetOrAdd(u16Key.value(), u16Value.value());
		if (!u16Result.has_value()) [[unlikely]] {
			return std::unexpected(u16Result.error());
		}

		auto u8Result = REX::Utf16ToUtf8(u16Result.value());
		if (!u8Result.has_value()) [[unlikely]] {
			return std::unexpected(u8Result.error());
		}

		return std::move(u8Result).value();
	}

	auto BSTranslator::GetOrAdd(std::wstring_view a_key, std::wstring_view a_value)
		-> std::expected<std::wstring, REX::SystemError>
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(a_key)) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		const auto value = GetOrAdd(RE::BSFixedStringWCS(a_key), RE::BSFixedStringWCS(a_value));
		if (!value.has_value()) [[unlikely]] {
			return std::unexpected(value.error());
		}

		return std::wstring(value.value());
	}

	auto BSTranslator::GetOrAdd(const RE::BSFixedStringCS& a_key, const RE::BSFixedStringCS& a_value)
		-> std::expected<RE::BSFixedStringCS, REX::SystemError>
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(std::string_view(a_key))) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		const auto u16Key = REX::Utf8ToUtf16(a_key);
		if (!u16Key.has_value()) [[unlikely]] {
			return std::unexpected(u16Key.error());
		}

		const auto u16Value = REX::Utf8ToUtf16(a_value);
		if (!u16Value.has_value()) [[unlikely]] {
			return std::unexpected(u16Value.error());
		}

		const auto u16Result = GetOrAdd(u16Key.value(), u16Value.value());
		if (!u16Result.has_value()) [[unlikely]] {
			return std::unexpected(u16Result.error());
		}

		const auto u8Result = REX::Utf16ToUtf8(u16Result.value());
		if (!u8Result.has_value()) [[unlikely]] {
			return std::unexpected(u8Result.error());
		}

		return RE::BSFixedStringCS(u8Result.value());
	}

	auto BSTranslator::GetOrAdd(const RE::BSFixedStringWCS& a_key, const RE::BSFixedStringWCS& a_value)
		-> std::expected<RE::BSFixedStringWCS, REX::SystemError>
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(std::wstring_view(a_key))) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		const auto&& [keyIt, hasInserted] = translationMap.emplace(a_key, a_value);
		if (!hasInserted) {
			return keyIt->second;
		}

		return a_value;
	}

	auto BSTranslator::Add(std::string_view a_key, std::string_view a_value) -> bool
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(a_key)) {
			return false;
		}

		const auto u16Key = REX::Utf8ToUtf16(a_key);
		if (!u16Key.has_value()) {
			return false;
		}

		const auto u16Value = REX::Utf8ToUtf16(a_value);
		if (!u16Value.has_value()) {
			return false;
		}

		return Add(u16Key.value(), u16Value.value());
	}

	auto BSTranslator::Add(std::wstring_view a_key, std::wstring_view a_value) -> bool
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(a_key)) {
			return false;
		}

		return Add(RE::BSFixedStringWCS(a_key), RE::BSFixedStringWCS(a_value));
	}

	auto BSTranslator::Add(const RE::BSFixedStringCS& a_key, const RE::BSFixedStringCS& a_value) -> bool
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(std::string_view(a_key))) {
			return false;
		}

		const auto u16Key = REX::Utf8ToUtf16(a_key);
		if (!u16Key.has_value()) {
			return false;
		}

		const auto u16Value = REX::Utf8ToUtf16(a_value);
		if (!u16Value.has_value()) {
			return false;
		}

		return Add(u16Key.value(), u16Value.value());
	}

	auto BSTranslator::Add(const RE::BSFixedStringWCS& a_key, const RE::BSFixedStringWCS& a_value) -> bool
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(std::wstring_view(a_key))) {
			return false;
		}

		const auto&& [_, hasInserted] = translationMap.emplace(a_key, a_value);
		return hasInserted;
	}

	void BSTranslator::AddRange(std::span<const std::pair<std::string_view, std::string_view>> a_pairs)
	{
		ReserveAdditional(static_cast<size_type>(a_pairs.size()));

		for (auto&& [key, value] : a_pairs) {
			Add(key, value);
		}
	}

	void BSTranslator::AddRange(std::span<const std::pair<std::wstring_view, std::wstring_view>> a_pairs)
	{
		ReserveAdditional(static_cast<size_type>(a_pairs.size()));

		for (auto&& [key, value] : a_pairs) {
			Add(key, value);
		}
	}

	void BSTranslator::AddRange(std::span<const std::pair<RE::BSFixedStringCS, RE::BSFixedStringCS>> a_pairs)
	{
		ReserveAdditional(static_cast<size_type>(a_pairs.size()));

		for (auto&& [key, value] : a_pairs) {
			Add(key, value);
		}
	}

	void BSTranslator::AddRange(std::span<const std::pair<RE::BSFixedStringWCS, RE::BSFixedStringWCS>> a_pairs)
	{
		ReserveAdditional(static_cast<size_type>(a_pairs.size()));

		for (auto&& [key, value] : a_pairs) {
			Add(key, value);
		}
	}

	auto BSTranslator::Remove(std::string_view a_key) -> bool
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(a_key)) {
			return false;
		}

		const auto u16Key = REX::Utf8ToUtf16(a_key);
		if (!u16Key) {
			return false;
		}

		return Remove(u16Key.value());
	}

	auto BSTranslator::Remove(std::wstring_view a_key) -> bool
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(a_key)) {
			return false;
		}

		return Remove(RE::BSFixedStringWCS(a_key));
	}

	auto BSTranslator::Remove(const RE::BSFixedStringCS& a_key) -> bool
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(std::string_view(a_key))) {
			return false;
		}

		const auto u16Key = REX::Utf8ToUtf16(a_key);
		if (!u16Key.has_value()) {
			return false;
		}

		return Remove(u16Key.value());
	}

	auto BSTranslator::Remove(const RE::BSFixedStringWCS& a_key) noexcept -> bool
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(std::wstring_view(a_key))) {
			return false;
		}

		const auto keyIt = translationMap.find(a_key);
		if (keyIt == translationMap.end()) {
			return false;
		}

		translationMap.erase(keyIt);
		return true;
	}

	void BSTranslator::Reserve(size_type a_capacity)
	{
		translationMap.reserve(a_capacity);
	}

	void BSTranslator::ReserveAdditional(size_type a_additionalCapacity)
	{
		translationMap.reserve(translationMap.size() + a_additionalCapacity);
	}

	auto BSTranslator::LoadFromFile(std::string_view a_rawName, std::string_view a_languageCode) -> REX::SystemError
	{
		constexpr const auto& DEFAULT_LANGUAGE = RE::BSScaleformTranslator::DEFAULT_LANGUAGE;

		if (!REX::EqualsIgnoreCase(a_languageCode, DEFAULT_LANGUAGE)) {
			std::ignore = LoadFromFileImpl(a_rawName, DEFAULT_LANGUAGE);
		}

		return LoadFromFileImpl(a_rawName, a_languageCode);
	}

	auto BSTranslator::LoadFromFileImpl(std::string_view a_rawName, std::string_view a_languageCode) -> REX::SystemError
	{
		const auto translationFilePath = RE::BSScaleformTranslator::GetTranslationFilePath(a_rawName, a_languageCode);

		const auto translations = REX::ReadTranslationFile<wchar_t>(translationFilePath);
		if (!translations.has_value()) {
			return translations.error();
		}

		for (auto&& [key, value] : translations.value()) {
			translationMap.insert_or_assign(key, value);
		}

		return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
	}
}
