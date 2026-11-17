#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTHashMap.hpp"

namespace RE
{
	class BSTranslator
	{
	public:
		using size_type = std::uint32_t;
		using difference_type = std::int32_t;

		BSTranslator() = default;
		~BSTranslator() noexcept = default;

		BSTranslator(const BSTranslator&) = default;
		BSTranslator(BSTranslator&&) noexcept = default;

		auto operator=(const BSTranslator&) -> BSTranslator& = default;
		auto operator=(BSTranslator&&) noexcept -> BSTranslator& = default;

		[[nodiscard]]
		auto GetTranslationMap() noexcept -> auto&
		{
			return translationMap;
		}

		[[nodiscard]]
		auto GetTranslationMap() const noexcept -> const auto&
		{
			return translationMap;
		}

		[[nodiscard]]
		auto Contains(std::string_view a_key) const -> bool;
		[[nodiscard]]
		auto Contains(std::wstring_view a_key) const -> bool;
		[[nodiscard]]
		auto Contains(const RE::BSFixedStringCS& a_key) const -> bool;
		[[nodiscard]]
		auto Contains(const RE::BSFixedStringWCS& a_key) const noexcept -> bool;

		[[nodiscard]]
		auto GetValue(std::string_view a_key) const -> std::expected<std::string, REX::SystemError>;
		[[nodiscard]]
		auto GetValue(std::wstring_view a_key) const -> std::expected<std::wstring, REX::SystemError>;
		[[nodiscard]]
		auto GetValue(const RE::BSFixedStringCS& a_key) const -> std::expected<RE::BSFixedStringCS, REX::SystemError>;
		[[nodiscard]]
		auto GetValue(const RE::BSFixedStringWCS& a_key) const noexcept
			-> std::expected<RE::BSFixedStringWCS, REX::SystemError>;

		auto SetValue(std::string_view a_key, std::string_view a_value) -> bool;
		auto SetValue(std::wstring_view a_key, std::wstring_view a_value) -> bool;
		auto SetValue(const RE::BSFixedStringCS& a_key, const RE::BSFixedStringCS& a_value) -> bool;
		auto SetValue(const RE::BSFixedStringWCS& a_key, const RE::BSFixedStringWCS& a_value) -> bool;

		void SetRange(std::span<const std::pair<std::string_view, std::string_view>> a_pairs);
		void SetRange(std::span<const std::pair<std::wstring_view, std::wstring_view>> a_pairs);
		void SetRange(std::span<const std::pair<RE::BSFixedStringCS, RE::BSFixedStringCS>> a_pairs);
		void SetRange(std::span<const std::pair<RE::BSFixedStringWCS, RE::BSFixedStringWCS>> a_pairs);

		auto GetOrAdd(std::string_view a_key, std::string_view a_value) -> std::expected<std::string, REX::SystemError>;
		auto GetOrAdd(std::wstring_view a_key, std::wstring_view a_value)
			-> std::expected<std::wstring, REX::SystemError>;
		auto GetOrAdd(const RE::BSFixedStringCS& a_key, const RE::BSFixedStringCS& a_value)
			-> std::expected<RE::BSFixedStringCS, REX::SystemError>;
		auto GetOrAdd(const RE::BSFixedStringWCS& a_key, const RE::BSFixedStringWCS& a_value)
			-> std::expected<RE::BSFixedStringWCS, REX::SystemError>;

		auto Add(std::string_view a_key, std::string_view a_value) -> bool;
		auto Add(std::wstring_view a_key, std::wstring_view a_value) -> bool;
		auto Add(const RE::BSFixedStringCS& a_key, const RE::BSFixedStringCS& a_value) -> bool;
		auto Add(const RE::BSFixedStringWCS& a_key, const RE::BSFixedStringWCS& a_value) -> bool;

		void AddRange(std::span<const std::pair<std::string_view, std::string_view>> a_pairs);
		void AddRange(std::span<const std::pair<std::wstring_view, std::wstring_view>> a_pairs);
		void AddRange(std::span<const std::pair<RE::BSFixedStringCS, RE::BSFixedStringCS>> a_pairs);
		void AddRange(std::span<const std::pair<RE::BSFixedStringWCS, RE::BSFixedStringWCS>> a_pairs);

		auto Remove(std::string_view a_key) -> bool;
		auto Remove(std::wstring_view a_key) -> bool;
		auto Remove(const RE::BSFixedStringCS& a_key) -> bool;
		auto Remove(const RE::BSFixedStringWCS& a_key) noexcept -> bool;

		void Reserve(size_type a_capacity);
		void ReserveAdditional(size_type a_additionalCapacity);

		auto LoadFromFile(std::string_view a_rawName, std::string_view a_languageCode) -> REX::SystemError;

	private:
		auto LoadFromFileImpl(std::string_view a_rawName, std::string_view a_languageCode) -> REX::SystemError;

	public:
		// members
		BSTHashMap<BSFixedStringWCS, BSFixedStringWCS> translationMap; // 0x00
	};

	static_assert(sizeof(BSTranslator) == 0x30);
}
