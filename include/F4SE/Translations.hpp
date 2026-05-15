#pragma once

#include "RE/B/BSFixedString.hpp"

#include "REX/Error.hpp"
#include "REX/NotNull.hpp"

#include "Scaleform/P/Ptr.hpp"

namespace RE
{
	class BSScaleformTranslator;
}

namespace F4SE::Translations
{
	// These functions should only be used after the game data is ready; they are not thread-safe.

	class Translator final
	{
	public:
		Translator();
		~Translator() noexcept;

		Translator(const Translator&) = delete;
		Translator(Translator&&) = delete;

		Translator& operator=(const Translator&) = delete;
		Translator& operator=(Translator&&) = delete;

		[[nodiscard]] auto GetLanguageCode() const noexcept
			-> std::string_view;
		[[nodiscard]] auto GetGameTranslator() const noexcept
			-> REX::NotNull<::Scaleform::Ptr<RE::BSScaleformTranslator>>;

		[[nodiscard]] std::uint32_t GetSize() const noexcept;
		[[nodiscard]] std::uint32_t GetCapacity() const noexcept;
		[[nodiscard]] std::uint32_t GetMaxSize() const noexcept;

		[[nodiscard]] bool IsEmpty() const noexcept;

		[[nodiscard]] bool Contains(std::string_view a_key) const;
		[[nodiscard]] bool Contains(std::wstring_view a_key) const;
		[[nodiscard]] bool Contains(const RE::BSFixedStringCS& a_key) const;
		[[nodiscard]] bool Contains(const RE::BSFixedStringWCS& a_key) const;

		[[nodiscard]] auto GetValue(std::string_view a_key) const
			-> std::optional<std::string>;
		[[nodiscard]] auto GetValue(std::wstring_view a_key) const
			-> std::optional<std::wstring>;
		[[nodiscard]] auto GetValue(const RE::BSFixedStringCS& a_key) const
			-> std::optional<RE::BSFixedStringCS>;
		[[nodiscard]] auto GetValue(const RE::BSFixedStringWCS& a_key) const
			-> std::optional<RE::BSFixedStringWCS>;

		bool SetValue(std::string_view a_key, std::string_view a_value);
		bool SetValue(std::wstring_view a_key, std::wstring_view a_value);
		bool SetValue(const RE::BSFixedStringCS& a_key, const RE::BSFixedStringCS& a_value);
		bool SetValue(const RE::BSFixedStringWCS& a_key, const RE::BSFixedStringWCS& a_value);

		void SetRange(std::span<const std::pair<std::string_view, std::string_view>> a_pairs);
		void SetRange(std::span<const std::pair<std::wstring_view, std::wstring_view>> a_pairs);
		void SetRange(std::span<const std::pair<RE::BSFixedStringCS, RE::BSFixedStringCS>> a_pairs);
		void SetRange(std::span<const std::pair<RE::BSFixedStringWCS, RE::BSFixedStringWCS>> a_pairs);

		auto GetOrAdd(std::string_view a_key, std::string_view a_value)
			-> std::optional<std::string>;
		auto GetOrAdd(std::wstring_view a_key, std::wstring_view a_value)
			-> std::optional<std::wstring>;
		auto GetOrAdd(const RE::BSFixedStringCS& a_key, const RE::BSFixedStringCS& a_value)
			-> std::optional<RE::BSFixedStringCS>;
		auto GetOrAdd(const RE::BSFixedStringWCS& a_key, const RE::BSFixedStringWCS& a_value)
			-> std::optional<RE::BSFixedStringWCS>;

		bool Add(std::string_view a_key, std::string_view a_value);
		bool Add(std::wstring_view a_key, std::wstring_view a_value);
		bool Add(const RE::BSFixedStringCS& a_key, const RE::BSFixedStringCS& a_value);
		bool Add(const RE::BSFixedStringWCS& a_key, const RE::BSFixedStringWCS& a_value);

		void AddRange(std::span<const std::pair<std::string_view, std::string_view>> a_pairs);
		void AddRange(std::span<const std::pair<std::wstring_view, std::wstring_view>> a_pairs);
		void AddRange(std::span<const std::pair<RE::BSFixedStringCS, RE::BSFixedStringCS>> a_pairs);
		void AddRange(std::span<const std::pair<RE::BSFixedStringWCS, RE::BSFixedStringWCS>> a_pairs);

		bool Remove(std::string_view a_key);
		bool Remove(std::wstring_view a_key);
		bool Remove(const RE::BSFixedStringCS& a_key);
		bool Remove(const RE::BSFixedStringWCS& a_key);

		void Reserve(std::uint32_t a_capacity);

		REX::SystemError LoadFromFile(std::string_view a_rawName);

	private:
		REX::SystemError LoadFromFileImpl(std::string_view a_rawName, std::string_view a_languageCode);

		std::string _languageCode;
		REX::NotNull<::Scaleform::Ptr<RE::BSScaleformTranslator>> _gameTranslator;
	};

	[[nodiscard]] auto GetTranslator()
		-> const REX::NotNull<std::unique_ptr<Translator>>&;
}

namespace F4SE::Translations::Impl
{
	[[nodiscard]] auto GetGameTranslator()
		-> ::Scaleform::Ptr<RE::BSScaleformTranslator>;
}
