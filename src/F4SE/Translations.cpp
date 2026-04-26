#include "F4SE/Translations.hpp"

#include "RE/B/BSScaleformManager.hpp"
#include "RE/B/BSScaleformTranslator.hpp"
#include "RE/B/BSTranslator.hpp"

#include "REX/Compare.hpp"
#include "REX/Contract.hpp"
#include "REX/Convert.hpp"
#include "REX/Translate.hpp"

namespace F4SE::Translations
{
	Translator::Translator()
		: _languageCode(RE::BSScaleformTranslator::GetLanguage()),
		  _gameTranslator(Impl::GetGameTranslator())
	{
	}

	Translator::~Translator() noexcept = default;

	auto Translator::GetLanguageCode() const noexcept -> std::string_view
	{
		return static_cast<std::string_view>(_languageCode);
	}

	auto Translator::GetGameTranslator() const noexcept -> REX::NotNull<::Scaleform::Ptr<RE::BSScaleformTranslator>>
	{
		return _gameTranslator;
	}

	std::uint32_t Translator::GetSize() const noexcept
	{
		return _gameTranslator->translator.translationMap.size();
	}

	std::uint32_t Translator::GetCapacity() const noexcept
	{
		return _gameTranslator->translator.translationMap.capacity();
	}

	std::uint32_t Translator::GetMaxSize() const noexcept
	{
		return _gameTranslator->translator.translationMap.max_size();
	}

	bool Translator::IsEmpty() const noexcept
	{
		return _gameTranslator->translator.translationMap.empty();
	}

	bool Translator::Contains(std::string_view a_key) const
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(a_key)) {
			return false;
		}

		const auto u16Key = REX::Utf8ToUtf16(a_key);
		if (!u16Key) {
			return false;
		}

		return Contains(*u16Key);
	}

	bool Translator::Contains(std::wstring_view a_key) const
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(a_key)) {
			return false;
		}

		return Contains(RE::BSFixedStringWCS(a_key));
	}

	bool Translator::Contains(const RE::BSFixedStringCS& a_key) const
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(static_cast<std::string_view>(a_key))) {
			return false;
		}

		const auto u16Key = REX::Utf8ToUtf16(a_key);
		if (!u16Key) {
			return false;
		}

		return Contains(*u16Key);
	}

	bool Translator::Contains(const RE::BSFixedStringWCS& a_key) const
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(static_cast<std::wstring_view>(a_key))) {
			return false;
		}

		const auto& translationMap = _gameTranslator->translator.translationMap;
		return translationMap.contains(a_key);
	}

	auto Translator::GetValue(std::string_view a_key) const -> std::optional<std::string>
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(a_key)) {
			return std::nullopt;
		}

		const auto u16Key = REX::Utf8ToUtf16(a_key);
		if (!u16Key) {
			return std::nullopt;
		}

		const auto u16Value = GetValue(*u16Key);
		if (!u16Value) {
			return std::nullopt;
		}

		auto u8Value = REX::Utf16ToUtf8(*u16Value);
		if (!u8Value) {
			return std::nullopt;
		}

		return *std::move(u8Value);
	}

	auto Translator::GetValue(std::wstring_view a_key) const -> std::optional<std::wstring>
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(a_key)) {
			return std::nullopt;
		}

		const auto value = GetValue(RE::BSFixedStringWCS(a_key));
		if (!value) {
			return std::nullopt;
		}

		return std::wstring(*value);
	}

	auto Translator::GetValue(const RE::BSFixedStringCS& a_key) const -> std::optional<RE::BSFixedStringCS>
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(static_cast<std::string_view>(a_key))) {
			return std::nullopt;
		}

		const auto u16Key = REX::Utf8ToUtf16(a_key);
		if (!u16Key) {
			return std::nullopt;
		}

		const auto u16Value = GetValue(*u16Key);
		if (!u16Value) {
			return std::nullopt;
		}

		auto u8Value = REX::Utf16ToUtf8(*u16Value);
		if (!u8Value) {
			return std::nullopt;
		}

		return RE::BSFixedStringCS(*u8Value);
	}

	auto Translator::GetValue(const RE::BSFixedStringWCS& a_key) const -> std::optional<RE::BSFixedStringWCS>
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(static_cast<std::wstring_view>(a_key))) {
			return std::nullopt;
		}

		const auto& translationMap = _gameTranslator->translator.translationMap;

		const auto keyIt = translationMap.find(a_key);
		if (keyIt == translationMap.end()) {
			return std::nullopt;
		}

		return keyIt->second;
	}

	bool Translator::SetValue(std::string_view a_key, std::string_view a_value)
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(a_key)) {
			return false;
		}

		const auto u16Key = REX::Utf8ToUtf16(a_key);
		if (!u16Key) {
			return false;
		}

		const auto u16Value = REX::Utf8ToUtf16(a_value);
		if (!u16Value) {
			return false;
		}

		return SetValue(*u16Key, *u16Value);
	}

	bool Translator::SetValue(std::wstring_view a_key, std::wstring_view a_value)
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(a_key)) {
			return false;
		}

		return SetValue(RE::BSFixedStringWCS(a_key), RE::BSFixedStringWCS(a_value));
	}

	bool Translator::SetValue(const RE::BSFixedStringCS& a_key, const RE::BSFixedStringCS& a_value)
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(static_cast<std::string_view>(a_key))) {
			return false;
		}

		const auto u16Key = REX::Utf8ToUtf16(a_key);
		if (!u16Key) {
			return false;
		}

		const auto u16Value = REX::Utf8ToUtf16(a_value);
		if (!u16Value) {
			return false;
		}

		return SetValue(*u16Key, *u16Value);
	}

	bool Translator::SetValue(const RE::BSFixedStringWCS& a_key, const RE::BSFixedStringWCS& a_value)
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(static_cast<std::wstring_view>(a_key))) {
			return false;
		}

		auto& translationMap = _gameTranslator->translator.translationMap;
		translationMap.insert_or_assign(a_key, a_value);
		return true;
	}

	void Translator::SetRange(std::span<const std::pair<std::string_view, std::string_view>> a_pairs)
	{
		Reserve(static_cast<std::uint32_t>(a_pairs.size()));

		for (const auto& [key, value] : a_pairs) {
			SetValue(key, value);
		}
	}

	void Translator::SetRange(std::span<const std::pair<std::wstring_view, std::wstring_view>> a_pairs)
	{
		Reserve(static_cast<std::uint32_t>(a_pairs.size()));

		for (const auto& [key, value] : a_pairs) {
			SetValue(key, value);
		}
	}

	void Translator::SetRange(std::span<const std::pair<RE::BSFixedStringCS, RE::BSFixedStringCS>> a_pairs)
	{
		Reserve(static_cast<std::uint32_t>(a_pairs.size()));

		for (const auto& [key, value] : a_pairs) {
			SetValue(key, value);
		}
	}

	void Translator::SetRange(std::span<const std::pair<RE::BSFixedStringWCS, RE::BSFixedStringWCS>> a_pairs)
	{
		Reserve(static_cast<std::uint32_t>(a_pairs.size()));

		for (const auto& [key, value] : a_pairs) {
			SetValue(key, value);
		}
	}

	auto Translator::GetOrAdd(std::string_view a_key, std::string_view a_value) -> std::optional<std::string>
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(a_key)) {
			return std::nullopt;
		}

		const auto u16Key = REX::Utf8ToUtf16(a_key);
		if (!u16Key) {
			return std::nullopt;
		}

		const auto u16Value = REX::Utf8ToUtf16(a_value);
		if (!u16Value) {
			return std::nullopt;
		}

		const auto u16Result = GetOrAdd(*u16Key, *u16Value);
		if (!u16Result) {
			return std::nullopt;
		}

		auto u8Result = REX::Utf16ToUtf8(*u16Result);
		if (!u8Result) {
			return std::nullopt;
		}

		return *std::move(u8Result);
	}

	auto Translator::GetOrAdd(std::wstring_view a_key, std::wstring_view a_value) -> std::optional<std::wstring>
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(a_key)) {
			return std::nullopt;
		}

		const auto value = GetOrAdd(RE::BSFixedStringWCS(a_key), RE::BSFixedStringWCS(a_value));
		if (!value) {
			return std::nullopt;
		}

		return std::wstring(*value);
	}

	auto Translator::GetOrAdd(const RE::BSFixedStringCS& a_key, const RE::BSFixedStringCS& a_value) -> std::optional<RE::BSFixedStringCS>
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(static_cast<std::string_view>(a_key))) {
			return std::nullopt;
		}

		const auto u16Key = REX::Utf8ToUtf16(a_key);
		if (!u16Key) {
			return std::nullopt;
		}

		const auto u16Value = REX::Utf8ToUtf16(a_value);
		if (!u16Value) {
			return std::nullopt;
		}

		const auto u16Result = GetOrAdd(*u16Key, *u16Value);
		if (!u16Result) {
			return std::nullopt;
		}

		auto u8Result = REX::Utf16ToUtf8(*u16Result);
		if (!u8Result) {
			return std::nullopt;
		}

		return RE::BSFixedStringCS(*u8Result);
	}

	auto Translator::GetOrAdd(const RE::BSFixedStringWCS& a_key, const RE::BSFixedStringWCS& a_value) -> std::optional<RE::BSFixedStringWCS>
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(static_cast<std::wstring_view>(a_key))) {
			return std::nullopt;
		}

		auto& translationMap = _gameTranslator->translator.translationMap;

		const auto&& [keyIt, hasInserted] = translationMap.emplace(a_key, a_value);
		if (!hasInserted) {
			return keyIt->second;
		}

		return a_value;
	}

	bool Translator::Add(std::string_view a_key, std::string_view a_value)
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(a_key)) {
			return false;
		}

		const auto u16Key = REX::Utf8ToUtf16(a_key);
		if (!u16Key) {
			return false;
		}

		const auto u16Value = REX::Utf8ToUtf16(a_value);
		if (!u16Value) {
			return false;
		}

		return Add(*u16Key, *u16Value);
	}

	bool Translator::Add(std::wstring_view a_key, std::wstring_view a_value)
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(a_key)) {
			return false;
		}

		return Add(RE::BSFixedStringWCS(a_key), RE::BSFixedStringWCS(a_value));
	}

	bool Translator::Add(const RE::BSFixedStringCS& a_key, const RE::BSFixedStringCS& a_value)
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(static_cast<std::string_view>(a_key))) {
			return false;
		}

		const auto u16Key = REX::Utf8ToUtf16(a_key);
		if (!u16Key) {
			return false;
		}

		const auto u16Value = REX::Utf8ToUtf16(a_value);
		if (!u16Value) {
			return false;
		}

		return Add(*u16Key, *u16Value);
	}

	bool Translator::Add(const RE::BSFixedStringWCS& a_key, const RE::BSFixedStringWCS& a_value)
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(static_cast<std::wstring_view>(a_key))) {
			return false;
		}

		auto& translationMap = _gameTranslator->translator.translationMap;
		const auto&& [_, hasInserted] = translationMap.emplace(a_key, a_value);
		return hasInserted;
	}

	void Translator::AddRange(std::span<const std::pair<std::string_view, std::string_view>> a_pairs)
	{
		Reserve(GetSize() + static_cast<std::uint32_t>(a_pairs.size()));

		for (const auto& [key, value] : a_pairs) {
			Add(key, value);
		}
	}

	void Translator::AddRange(std::span<const std::pair<std::wstring_view, std::wstring_view>> a_pairs)
	{
		Reserve(GetSize() + static_cast<std::uint32_t>(a_pairs.size()));

		for (const auto& [key, value] : a_pairs) {
			Add(key, value);
		}
	}

	void Translator::AddRange(std::span<const std::pair<RE::BSFixedStringCS, RE::BSFixedStringCS>> a_pairs)
	{
		Reserve(GetSize() + static_cast<std::uint32_t>(a_pairs.size()));

		for (const auto& [key, value] : a_pairs) {
			Add(key, value);
		}
	}

	void Translator::AddRange(std::span<const std::pair<RE::BSFixedStringWCS, RE::BSFixedStringWCS>> a_pairs)
	{
		Reserve(GetSize() + static_cast<std::uint32_t>(a_pairs.size()));

		for (const auto& [key, value] : a_pairs) {
			Add(key, value);
		}
	}

	bool Translator::Remove(std::string_view a_key)
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(a_key)) {
			return false;
		}

		const auto u16Key = REX::Utf8ToUtf16(a_key);
		if (!u16Key) {
			return false;
		}

		return Remove(*u16Key);
	}

	bool Translator::Remove(std::wstring_view a_key)
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(a_key)) {
			return false;
		}

		return Remove(RE::BSFixedStringWCS(a_key));
	}

	bool Translator::Remove(const RE::BSFixedStringCS& a_key)
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(static_cast<std::string_view>(a_key))) {
			return false;
		}

		const auto u16Key = REX::Utf8ToUtf16(a_key);
		if (!u16Key) {
			return false;
		}

		return Remove(*u16Key);
	}

	bool Translator::Remove(const RE::BSFixedStringWCS& a_key)
	{
		if (!RE::BSScaleformTranslator::IsKeyValid(static_cast<std::wstring_view>(a_key))) {
			return false;
		}

		auto& translationMap = _gameTranslator->translator.translationMap;

		const auto keyIt = translationMap.find(a_key);
		if (keyIt == translationMap.end()) {
			return false;
		}

		translationMap.erase(keyIt);
		return true;
	}

	void Translator::Reserve(std::uint32_t a_capacity)
	{
		_gameTranslator->translator.translationMap.reserve(a_capacity);
	}

	REX::SystemError Translator::LoadFromFile(std::string_view a_rawName)
	{
		if (!REX::EqualsIgnoreCase(static_cast<std::string_view>(_languageCode), RE::BSScaleformTranslator::DEFAULT_LANGUAGE)) {
			std::ignore = LoadFromFileImpl(a_rawName, RE::BSScaleformTranslator::DEFAULT_LANGUAGE);
		}

		return LoadFromFileImpl(a_rawName, _languageCode);
	}

	REX::SystemError Translator::LoadFromFileImpl(std::string_view a_rawName, std::string_view a_languageCode)
	{
		const auto translationFilePath = RE::BSScaleformTranslator::GetTranslationFilePath(a_rawName, a_languageCode);

		auto translations = REX::ReadTranslationFile(translationFilePath);
		if (!translations) {
			return std::move(translations).error();
		}

		auto& translationMap = _gameTranslator->translator.translationMap;

		for (const auto& [key, value] : *translations) {
			translationMap.insert_or_assign(key, value);
		}

		return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
	}

	auto GetTranslator() -> const REX::NotNull<std::unique_ptr<Translator>>&
	{
		static const auto INSTANCE = REX::NotNull(std::make_unique<Translator>());
		return INSTANCE;
	}
}

namespace F4SE::Translations::Impl
{
	auto GetGameTranslator() -> ::Scaleform::Ptr<RE::BSScaleformTranslator>
	{
		auto* scaleformManager = RE::BSScaleformManager::GetSingleton();
		if (!scaleformManager) [[unlikely]] {
			REX::Assert(false);
			return nullptr;
		}

		return scaleformManager->GetTranslator();
	}
}
